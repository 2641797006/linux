#ifndef _BPTREE_H_
#define _BPTREE_H_

#ifndef _GLIBCXX_QUEUE
#include <queue>
#endif

#define __tt(T1, T2)	template <typename T1, typename T2>

#ifndef MAX_T
#define MAX_T	4
#endif

#ifndef MIN_T
#define MIN_T	((MAX_T+1)/2)
#endif

namespace __tree{
using namespace std;

class bp_node{	//B+树结点类
  public:
	int		keynum;
	bp_node		*parent;
	void		*key[MAX_T];	//2种类型, 索引(index_t)和真实数据项(T)
	bp_node		*child[MAX_T+1];
	bp_node		*next;

	void clrc();
	bp_node(bp_node* p=NULL): keynum(0), parent(p), next(NULL) {clrc();}
};

inline void
bp_node::clrc()
{
	int i;
	for (i=0; i<MAX_T+1; i++)
		child[i] = NULL;
}

/* class bptree */	//具体B+树特性 请参照 baidu.com/s?wd=B%2B%E6%A0%91
__tt(index_t, T)	//索引(index_t)与数据项(T)可以相同: bptree<int,int>, bptree<string(文件名),fstream(文件)>
class bptree{
  public:
	T* find(T const& t);	//返回找到的数据项地址, 没有则返回NULL
	T* insert(T const& t);	//若调用了set_unique(), 则要插入的数据项已存在时不会插入,而返回已存在数据地址. 其他返回NULL
	int erase(T const& t);	//删除成功返回1, 不存在则返回0

	T* min();		//返回最小数据项的地址
	T* max();		//返回最大数据项的地址
	int traverse(int visit(T*));	//自定义visit函数, 从小到大遍历所有数据, 一旦visit返回非0值, 终止并返回该值

	int isunique(){return unique;}	//若设置了惟一性,返回1, 否则返回0
	void set_unique(){unique=1;}	//设置数据项的惟一性, 不允许"相等"的数据项存在
	void set_nounique(){unique=0;}	//取消数据项的惟一性, 允许"相等"的数据项存在
	bptree();
	~bptree();

  private:
	int unique;
	bp_node *_root;

	T* find_t(bp_node*& node, T const& t, int& i);
//	void split(bp_node* node, bp_node*& node_1, int leaf); //use once, inline for fast
};

__tt(index_t, T)
bptree<index_t, T>::bptree(): unique(0)
{
	_root = new bp_node;
}

__tt(index_t, T)
bptree<index_t, T>::~bptree()
{
	int i;
	bp_node *node;
	queue<bp_node*> q;

	q.push(_root);
	while (!q.empty()) {
		node = q.front();
		q.pop();
		if (node->child[0]) {
			for (i=0; i<=node->keynum; i++)
				q.push(node->child[i]);
			for (i=0; i<node->keynum; i++)
				delete (index_t*)node->key[i];
		}
		else
			for (i=0; i<node->keynum; i++)
				delete (T*)node->key[i];
		delete node;
	}
}

__tt(index_t, T)
inline T*
bptree<index_t, T>::find(T const& t)
{
	int i;
	bp_node *node=_root;
	return find_t(node, t, i);
}

__tt(index_t, T)
T*
bptree<index_t, T>::find_t(bp_node*& node, T const& t, int& i)
{
	if (!node)
		node = _root;
	for (;;) {
		if (node->child[0]) {
			for (i=0; i<node->keynum; i++)
				if (t<=*(index_t*)node->key[i])			// <=
					break;
			node = node->child[i];
		}
		else {
			for (i=0; i<node->keynum-1; i++)
				if (t<=*(T*)node->key[i])			// <=
					break;
			break;
		}
	}
	if (t==*(T*)node->key[i])
		return (T*)node->key[i];
	return NULL;
}

__tt(index_t, T)
int
bptree<index_t, T>::erase(T const& t)
{
	int i, cind, leaf;
	T *tp;
	bp_node *node=_root, *node_1, *node_p;

	tp = find_t(node, t, i);
	if (!tp)
		return 0;
	delete tp;
	while (++i<node->keynum)
		node->key[i-1] = node->key[i];
	leaf = 1;
	while (--node->keynum<MIN_T-1) {
		node_p = node->parent;
		if (!node_p) {
			if (_root->keynum)
				break;
			_root = _root->child[0];
			if (_root)
				_root->parent = NULL;
			else
				_root = new bp_node;
			delete node;
			break;
		}
		for (cind=0; cind<node_p->keynum; cind++)
			if (node_p->child[cind]==node)
				break;
		if (cind && (node_p->child[cind-1]->keynum>=MIN_T)) {
			i = node->keynum;
			node_1 = node_p->child[cind-1];
			if (!leaf) {
				node->child[i+1] = node->child[i];
				while (--i>=0) {
					node->key[i+1] = node->key[i];
					node->child[i+1] = node->child[i];
				}
				node->key[0] = node_p->key[cind-1];
				node->child[0] = node_1->child[node_1->keynum];
				node->child[0]->parent = node;
				node_p->key[cind-1] = node_1->key[node_1->keynum-1];
			}
			else {
				while (--i>=0)
					node->key[i+1] = node->key[i];
				node->key[0] = node_1->key[node_1->keynum-1];
				*(index_t*)node_p->key[cind-1] = *(T*)node_1->key[node_1->keynum-2];
			}
			node->keynum++, node_1->keynum--;
			return 1;
		}
		else if ((cind+1<=node_p->keynum) && (node_p->child[cind+1]->keynum>=MIN_T)) {
			node_1 = node_p->child[cind+1];
			if (!leaf) {
				node->key[node->keynum] = node_p->key[cind];
				node_p->key[cind] = node_1->key[0];
				node_1->child[0]->parent = node;
				node->child[node->keynum+1] = node_1->child[0];
				for (i=1; i<node_1->keynum; i++) {
					node_1->key[i-1] = node_1->key[i];
					node_1->child[i-1] = node_1->child[i];
				}
				node_1->child[i-1] = node_1->child[i];
			}
			else {
				node->key[node->keynum] = node_1->key[0];
				*(index_t*)node_p->key[cind] = *(T*)node_1->key[0];
				for (i=1; i<node_1->keynum; i++)
					node_1->key[i-1] = node_1->key[i];
			}
			node->keynum++, node_1->keynum--;
			return 1;
		}
		else {
			if (cind+1>node_p->keynum) {
				node_1 = node;
				cind--;
				node = node_p->child[cind];
			}
			else
				node_1 = node_p->child[cind+1];
			if (!leaf) {
				node->key[node->keynum] = node_p->key[cind];
				node->keynum++;
			}
			else
				delete (index_t*)node_p->key[cind];
			while (++cind<node_p->keynum) {
				node_p->key[cind-1] = node_p->key[cind];
				node_p->child[cind] = node_p->child[cind+1];
			}
			if (!leaf) {
				for (i=0; i<node_1->keynum; i++) {
					node->key[node->keynum+i] = node_1->key[i];
					node_1->child[i]->parent = node;
					node->child[node->keynum+i] = node_1->child[i];
				}
				node_1->child[i]->parent = node;
				node->child[node->keynum+i] = node_1->child[i];
			}
			else {
				for (i=0; i<node_1->keynum; i++)
					node->key[node->keynum+i] = node_1->key[i];
			}
			node->keynum += node_1->keynum;
			node = node_p;
			delete node_1;
		}
		leaf ? (leaf=0) : 0;
	}
	return 1;
}
/*
__tt(index_t, T)
void
bptree<index_t, T>::split(bp_node* node, bp_node*& node_1, int leaf)
{
	int i;
	node_1 = new bp_node(node->parent);

	if (!leaf) {
		for (i=MIN_T; i<MAX_T; i++) {
			node_1->key[i-MIN_T] = node->key[i];
			node->child[i]->parent = node_1;
			node_1->child[i-MIN_T] = node->child[i];
		}
		node->child[i]->parent = node_1;
		node_1->child[i-MIN_T] = node->child[i];
		node->keynum = MIN_T-1;
	}
	else {
		for (i=MIN_T; i<MAX_T; i++)
			node_1->key[i-MIN_T] = node->key[i];
		node_1->next = node->next;
		node->next = node_1;
		node->keynum = MIN_T;
	}
	node_1->keynum = MAX_T-MIN_T;
}
*/
__tt(index_t, T)
T*
bptree<index_t, T>::insert(T const& t)
{
	int i, j, leaf;
	bp_node *node=_root, *node_1, *node_p;

	for (;;)
		if (node->child[0]) {
			for (i=0; i<node->keynum; i++)
				if (t<=*(index_t*)node->key[i])
					break;
			node = node->child[i];
		}
		else {
			for (i=0; i<node->keynum; i++)
				if (t<=*(T*)node->key[i])
					break;
			break;
		}
	if (unique && (i<node->keynum) && (t==*(T*)node->key[i]))
		return (T*)node->key[i];
	for (j=node->keynum; j>i; j--)
		node->key[j] = node->key[j-1];
	node->key[i] = new T;
	*(T*)node->key[i] = t;
	leaf = 1;
	while (++node->keynum==MAX_T) {
//split start
		node_1 = new bp_node(node->parent);
		if (!leaf) {
			for (i=MIN_T; i<MAX_T; i++) {
				node_1->key[i-MIN_T] = node->key[i];
				node->child[i]->parent = node_1;
				node_1->child[i-MIN_T] = node->child[i];
			}
			node->child[i]->parent = node_1;
			node_1->child[i-MIN_T] = node->child[i];
			node->keynum = MIN_T-1;
		}
		else {
			for (i=MIN_T; i<MAX_T; i++)
				node_1->key[i-MIN_T] = node->key[i];
			node_1->next = node->next;
			node->next = node_1;
			node->keynum = MIN_T;
		}
		node_1->keynum = MAX_T-MIN_T;
//split end
//		split(node, node_1, leaf);
		node_p = node->parent;
		if (!node_p) {
			_root = new bp_node;
			_root->child[0] = node;
			node->parent = _root;
			node_1->parent = _root;
			node_p = _root;
		}
		for (i=0; i<node_p->keynum; i++)
			if (node_p->child[i]==node)
				break;
		for (j=node_p->keynum; j>i; j--) {
			node_p->key[j] = node_p->key[j-1];
			node_p->child[j+1] = node_p->child[j];
		}
		if (leaf) {
			node_p->key[i] = new index_t;
			*(index_t*)node_p->key[i] = *(T*)node->key[MIN_T-1];
		}
		else
			node_p->key[i] = node->key[MIN_T-1];
		node_p->child[i+1] = node_1;
		node = node_p;
		leaf ? (leaf=0) : 0;
	}
	return NULL;
}

__tt(index_t, T)
T*
bptree<index_t, T>::min()
{
	bp_node *node=_root;

	while(node->child[0])
		node = node->child[0];
	return (T*)node->key[0];
}

__tt(index_t, T)
T*
bptree<index_t, T>::max()
{
	bp_node *node=_root;

	while(node->child[0])
		node = node->child[node->keynum];
	return (T*)node->key[node->keynum-1];
}

__tt(index_t, T)
int
bptree<index_t, T>::traverse(int visit(T*))
{
	int i, ret;
	bp_node *node=_root;

	while (node->child[0])
		node = node->child[0];
	for (;;) {
		for (i=0; i<node->keynum; i++) {
			ret = visit((T*)node->key[i]);
			if (ret)
				return ret;
		}
		node = node->next;
		if (!node)
			break;
	}
	return 0;
}

}//namespace __tree

#undef __tt

#endif
