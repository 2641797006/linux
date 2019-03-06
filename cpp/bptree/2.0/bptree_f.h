#ifndef _BPTREE_F_H_
#define _BPTREE_F_H_

/******* offset *********/

/*
 * TODO: < print B+ tree >
 * 在include此文件前加上下面这一行
 * #define _24k_BPTREE_PRINT
 * 可以输出B+树
 * 对于 bptree<index_t, T> 中 index_t 与 T 需要支持cout标准输出
 *
 */

#ifndef _GLIBCXX_QUEUE
#include <queue>
#endif

#ifndef _ASSERT_H
#include <assert.h>
#endif

#define __tt(T1, T2)	template <typename T1, typename T2>

//TODO: OFF_NULL 0偏移
// 请确保alloc(size)成功时不返回 OFF_NULL
#define OFF_NULL		(0)

//#define bp_node_init(node, ...)	(((bp_node*)getptr(node))->init(__VA_ARGS__)) //对结点进行构造
//#define BP_NEW(off, T, ...)	(new(getptr(off)) T(__VA_ARGS__)) //在 off 偏移处对 T 类型进行构造
#define BPN(off)		((bp_node*)getptr(off)) //根据偏移获取<临时> bp_node 类型指针
#define DIFF(p)			((char*)(p) - (char*)baseptr()) //根据指针获取偏移

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
	ptrdiff_t	parent;
	ptrdiff_t	key[MAX_T];	//2种类型, 索引(index_t)和真实数据项(T)
	ptrdiff_t	child[MAX_T+1];
	ptrdiff_t	next;

	void clrc();
//	void init(ptrdiff_t p=OFF_NULL) {keynum=0, parent=p, next=OFF_NULL; clrc();} //相当于构造函数
	bp_node(ptrdiff_t p=OFF_NULL): keynum(0), parent(p), next(OFF_NULL) {clrc();}
};

#ifdef _24k_BPTREE_PRINT

__tt(index_t, T)
void
bp_node_print(bp_node *tmp_p)
{
	int i;

	cout<<'{';
	if (tmp_p->child[0]) {
		for (i=0; i<tmp_p->keynum-1; i++)
			cout<<*(index_t*)tmp_p->key[i]<<' ';
		if (tmp_p->keynum)	//or print '\b'
			cout<<*(index_t*)tmp_p->key[i];
	} else {
		for (i=0; i<tmp_p->keynum-1; i++)
			cout<<*(T*)tmp_p->key[i]<<' ';
		if (tmp_p->keynum)	// '\b'
			cout<<*(T*)tmp_p->key[i];
	}
	cout<<'}';
}

#endif

inline void
bp_node::clrc()
{
	int i;
	for (i=0; i<MAX_T+1; i++)
		child[i] = OFF_NULL;
}

/* class bptree */	//具体B+树特性 请参照 baidu.com/s?wd=B%2B%E6%A0%91
__tt(index_t, T)	//索引(index_t)与数据项(T)可以相同: bptree<int,int>, bptree<string(文件名),fstream(文件)>
class bptree{
  public:
	ptrdiff_t find(T const& t);	//返回找到的数据项地址, 没有则返回OFF_NULL
	ptrdiff_t insert(T const& t);	//若调用了set_unique(), 则要插入的数据项已存在时不会插入,而返回已存在数据地址. 其他返回OFF_NULL
	int erase(T const& t);	//删除成功返回1, 不存在则返回0

	ptrdiff_t min();		//返回最小数据项的地址
	ptrdiff_t max();		//返回最大数据项的地址
	int traverse(int visit(ptrdiff_t));	//自定义visit函数, 从小到大遍历所有数据, 一旦visit返回非0值, 终止并返回该值

	int isunique(){return unique;}	//若设置了惟一性,返回1, 否则返回0
	void set_unique(){unique=1;}	//设置数据项的惟一性, 不允许"相等"的数据项存在
	void set_nounique(){unique=0;}	//取消数据项的惟一性, 允许"相等"的数据项存在
	bptree();
	~bptree();

#ifdef _24k_BPTREE_PRINT
	void print();
#endif

/******** TODO: 修改 baseptr(), alloc(), free(), 以使用个性化偏移方式 ***************/
	void* baseptr() {return NULL;} //基址指针
	ptrdiff_t alloc(size_t size) {return (new char[size])-(char*)baseptr();}
	void free(ptrdiff_t off) {delete[] ((char*)baseptr()+off);}
/************************************************************************************/

	void* getptr(ptrdiff_t off) {return (void*)((char*)baseptr()+off);} //根据偏移获取<临时>指针

  private:
	int unique;
	ptrdiff_t _root;

	ptrdiff_t find_t(ptrdiff_t& node, T const& t, int& i);

#ifdef _24k_BPTREE_CHECK
  public:
	bp_node* root() {return BPN(_root);}

	int check_cind(ptrdiff_t node);
	int check_key(ptrdiff_t node);
	int check_child(ptrdiff_t node);
	int check_all(ptrdiff_t node);
	int check();
#endif
};

#ifdef _24k_BPTREE_CHECK
__tt(index_t, T)
int
bptree<index_t, T>::check_cind(ptrdiff_t node)
{
	int i;
	bp_node *tmp_p;

	assert(node);
	tmp_p = BPN(node);
	if (node == _root) {
		assert(!tmp_p->parent);
		return 0;
	}
	tmp_p = BPN(tmp_p->parent);
	for (i=0; i<tmp_p->keynum; i++)
		if (node == tmp_p->child[i])
			break;
	assert(node == tmp_p->child[i]);
	return 1;
}

__tt(index_t, T)
int
bptree<index_t, T>::check_key(ptrdiff_t node)
{
	int i;
	bp_node *tmp_p = BPN(node);

	if (node != _root)
		assert(tmp_p->keynum >= MIN_T-1);
	for (i=0; i<tmp_p->keynum; i++)
		assert(tmp_p->key[i]);
	return tmp_p->keynum;
}

__tt(index_t, T)
int
bptree<index_t, T>::check_child(ptrdiff_t node)
{
	int i;
	bp_node *tmp_p = BPN(node);

//	if (node==_root && !tmp_p->child[0])
//		return -1;
	if (!tmp_p->child[0])
		for (i=0; i<=MAX_T; i++)
			assert(!tmp_p->child[i]);
	else
		for (i=0; i<=tmp_p->keynum; i++)
			assert(tmp_p->child[i]), assert(node == BPN(tmp_p->child[i])->parent);
	return 1;
}

__tt(index_t, T)
int
bptree<index_t, T>::check_all(ptrdiff_t node)
{
	check_cind(node);
	check_key(node);
	check_child(node);
	return 1;
}

__tt(index_t, T)
int
bptree<index_t, T>::check()
{
	int i;
	ptrdiff_t node;
	bp_node *tmp_p;
	queue<ptrdiff_t> q;

	q.push(_root);
	while (!q.empty()) {
		node = q.front();
		q.pop();
		check_all(node);
		tmp_p = BPN(node);
		if (tmp_p->child[0])
			for (i=0; i<=tmp_p->keynum; i++)
				q.push(tmp_p->child[i]);
	}
	return 1;
}

#endif

__tt(index_t, T)
inline
bptree<index_t, T>::bptree(): unique(0)
{
	_root = alloc(sizeof(bp_node)), new(BPN(_root)) bp_node;
}

__tt(index_t, T)
bptree<index_t, T>::~bptree()
{
	int i;
	ptrdiff_t node;
	queue<ptrdiff_t> q;
	bp_node *tmp_p;

	q.push(_root);
	while (!q.empty()) {
		node = q.front();
		q.pop();
		tmp_p = BPN(node);
		if (tmp_p->child[0]) {
			for (i=0; i<=tmp_p->keynum; i++)
				q.push(tmp_p->child[i]);
			for (i=0; i<tmp_p->keynum; i++)
				free(tmp_p->key[i]); // delete index_t
		}
		else
			for (i=0; i<tmp_p->keynum; i++)
				free(tmp_p->key[i]); // delete T
		free(node);
	}
}

__tt(index_t, T)
inline ptrdiff_t
bptree<index_t, T>::find(T const& t)
{
	int i;
	ptrdiff_t node=_root;
	return find_t(node, t, i);
}

__tt(index_t, T)
ptrdiff_t
bptree<index_t, T>::find_t(ptrdiff_t& node, T const& t, int& i)
{
	bp_node *tmp_p;

	if (!node)
		node = _root;
	for (;;) {
		tmp_p = BPN(node);
		if (tmp_p->child[0]) {
			for (i=0; i<tmp_p->keynum; i++)
				if (t<=*(index_t*)getptr(tmp_p->key[i]))			// <=
					break;
			node = tmp_p->child[i];
		}
		else {
			for (i=0; i<tmp_p->keynum-1; i++)
				if (t<=*(T*)getptr(tmp_p->key[i]))			// <=
					break;
			break;
		}
	}
	if (t==*(T*)getptr(tmp_p->key[i]))
		return tmp_p->key[i];
	return OFF_NULL;
}

__tt(index_t, T)
int
bptree<index_t, T>::erase(T const& t)
{
	int i, cind, leaf;
	ptrdiff_t node=_root, node_p;
	bp_node *tmp_p, *tmp_p1, *tmp_pp;

	{
		ptrdiff_t tp;
		tp = find_t(node, t, i);
		if (!tp)
			return 0;
		free(tp);
	}
	tmp_p = BPN(node);
	while (++i<tmp_p->keynum)
		tmp_p->key[i-1] = tmp_p->key[i];
	leaf = 1;
	while (--tmp_p->keynum<MIN_T-1) {
		node_p = tmp_p->parent;
		if (!node_p) {
			tmp_pp = BPN(_root);
			if (tmp_pp->keynum)
				break;
			_root = tmp_pp->child[0];
			if (_root)
				BPN(_root)->parent = OFF_NULL;
			else
				_root = alloc(sizeof(bp_node)), new(BPN(_root)) bp_node;
			free(node);
			break;
		}
		tmp_pp = BPN(node_p);
		for (cind=0; cind<tmp_pp->keynum; cind++)
			if (tmp_pp->child[cind]==node)
				break;
		if (cind && (BPN(tmp_pp->child[cind-1])->keynum>=MIN_T)) {
			i = tmp_p->keynum;
			tmp_p1 = BPN(tmp_pp->child[cind-1]);
			if (!leaf) {
				tmp_p->child[i+1] = tmp_p->child[i];
				while (--i>=0) {
					tmp_p->key[i+1] = tmp_p->key[i];
					tmp_p->child[i+1] = tmp_p->child[i];
				}
				tmp_p->key[0] = tmp_pp->key[cind-1];
				tmp_p->child[0] = tmp_p1->child[tmp_p1->keynum];
				BPN(tmp_p->child[0])->parent = node;
				tmp_pp->key[cind-1] = tmp_p1->key[tmp_p1->keynum-1];
			}
			else {
				while (--i>=0)
					tmp_p->key[i+1] = tmp_p->key[i];
				tmp_p->key[0] = tmp_p1->key[tmp_p1->keynum-1];
				*(index_t*)getptr(tmp_pp->key[cind-1]) = *(T*)getptr(tmp_p1->key[tmp_p1->keynum-2]);
			}
			tmp_p->keynum++, tmp_p1->keynum--;
			return 1;
		}
		else if ((cind+1<=tmp_pp->keynum) && (BPN(tmp_pp->child[cind+1])->keynum>=MIN_T)) {
			tmp_p1 = BPN(tmp_pp->child[cind+1]);
			if (!leaf) {
				tmp_p->key[tmp_p->keynum] = tmp_pp->key[cind];
				tmp_pp->key[cind] = tmp_p1->key[0];
				BPN(tmp_p1->child[0])->parent = node;
				tmp_p->child[tmp_p->keynum+1] = tmp_p1->child[0];
				for (i=1; i<tmp_p1->keynum; i++) {
					tmp_p1->key[i-1] = tmp_p1->key[i];
					tmp_p1->child[i-1] = tmp_p1->child[i];
				}
				tmp_p1->child[i-1] = tmp_p1->child[i];
			}
			else {
				tmp_p->key[tmp_p->keynum] = tmp_p1->key[0];
				*(index_t*)getptr(tmp_pp->key[cind]) = *(T*)getptr(tmp_p1->key[0]);
				for (i=1; i<tmp_p1->keynum; i++)
					tmp_p1->key[i-1] = tmp_p1->key[i];
			}
			tmp_p->keynum++, tmp_p1->keynum--;
			return 1;
		}
		else {
			if (cind+1>tmp_pp->keynum) {
				tmp_p1 = tmp_p;
				node = tmp_pp->child[--cind];
				tmp_p = BPN(node);
			}
			else
				tmp_p1 = BPN(tmp_pp->child[cind+1]);
			if (!leaf) {
				tmp_p->key[tmp_p->keynum] = tmp_pp->key[cind];
				tmp_p->keynum++;
			}
			else
				free(tmp_pp->key[cind]);
			while (++cind<tmp_pp->keynum) {
				tmp_pp->key[cind-1] = tmp_pp->key[cind];
				tmp_pp->child[cind] = tmp_pp->child[cind+1];
			}
			if (!leaf) {
				for (i=0; i<tmp_p1->keynum; i++) {
					tmp_p->key[tmp_p->keynum+i] = tmp_p1->key[i];
					BPN(tmp_p1->child[i])->parent = node;
					tmp_p->child[tmp_p->keynum+i] = tmp_p1->child[i];
				}
				BPN(tmp_p1->child[i])->parent = node;
				tmp_p->child[tmp_p->keynum+i] = tmp_p1->child[i];
			}
			else {
				for (i=0; i<tmp_p1->keynum; i++)
					tmp_p->key[tmp_p->keynum+i] = tmp_p1->key[i];
			}
			tmp_p->keynum += tmp_p1->keynum;
			node = node_p;
			tmp_p = tmp_pp;	// ***
			free(DIFF(tmp_p1));
		}
		leaf ? (leaf=0) : 0;
	}
	return 1;
}

__tt(index_t, T)
ptrdiff_t
bptree<index_t, T>::insert(T const& t)
{
	int i, j, leaf;
	ptrdiff_t node, node_1, node_p;
	bp_node *tmp_p=BPN(_root), *tmp_p1, *tmp_pp;

	for (;;)
		if (tmp_p->child[0]) {
			for (i=0; i<tmp_p->keynum; i++)
				if (t<=*(index_t*)getptr(tmp_p->key[i]))
					break;
			tmp_p = BPN(tmp_p->child[i]);
		}
		else {
			for (i=0; i<tmp_p->keynum; i++)
				if (t<=*(T*)getptr(tmp_p->key[i]))
					break;
			break;
		}
	if (unique && (i<tmp_p->keynum) && (t==*(T*)getptr(tmp_p->key[i])))
		return tmp_p->key[i];
	for (j=tmp_p->keynum; j>i; j--)
		tmp_p->key[j] = tmp_p->key[j-1];
	tmp_p->key[i] = alloc(sizeof(T));//
	*(T*)getptr(tmp_p->key[i]) = t; //拷贝构造
	leaf = 1;
	node = DIFF(tmp_p);
	while (++tmp_p->keynum==MAX_T) {
//split start
		node_1 = alloc(sizeof(bp_node));
		tmp_p1 = BPN(node_1), new(tmp_p1) bp_node(tmp_p->parent);
		if (!leaf) {
			for (i=MIN_T; i<MAX_T; i++) {
				tmp_p1->key[i-MIN_T] = tmp_p->key[i];
				BPN(tmp_p->child[i])->parent = node_1;
				tmp_p1->child[i-MIN_T] = tmp_p->child[i];
			}
			BPN(tmp_p->child[i])->parent = node_1;
			tmp_p1->child[i-MIN_T] = tmp_p->child[i];
			tmp_p->keynum = MIN_T-1;
		}
		else {
			for (i=MIN_T; i<MAX_T; i++)
				tmp_p1->key[i-MIN_T] = tmp_p->key[i];
			tmp_p1->next = tmp_p->next;
			tmp_p->next = node_1;
			tmp_p->keynum = MIN_T;
		}
		tmp_p1->keynum = MAX_T-MIN_T;
//split end
//		split(node, node_1, leaf);
		node_p = tmp_p->parent;
		tmp_pp = BPN(node_p);
		if (!node_p) { // node_p == OFF_NULL
			_root = alloc(sizeof(bp_node)), new(BPN(_root)) bp_node;
			BPN(_root)->child[0] = node;
			tmp_p->parent = _root;
			tmp_p1->parent = _root;
			tmp_pp = BPN(_root);
		}
		for (i=0; i<tmp_pp->keynum; i++)
			if (tmp_pp->child[i]==node)
				break;
		for (j=tmp_pp->keynum; j>i; j--) {
			tmp_pp->key[j] = tmp_pp->key[j-1];
			tmp_pp->child[j+1] = tmp_pp->child[j];
		}
		if (leaf) {
			tmp_pp->key[i] = alloc(sizeof(index_t));//
			*(index_t*)getptr(tmp_pp->key[i]) = *(T*)getptr(tmp_p->key[MIN_T-1]);//提取索引
		}
		else
			tmp_pp->key[i] = tmp_p->key[MIN_T-1];
		tmp_pp->child[i+1] = node_1;
		node = node_p; //
		tmp_p = tmp_pp; // ***
		leaf ? (leaf=0) : 0;
	}
	return OFF_NULL;
}

__tt(index_t, T)
ptrdiff_t
bptree<index_t, T>::min()
{
	bp_node *tmp_p = BPN(_root);

	while(tmp_p->child[0])
		tmp_p = BPN(tmp_p->child[0]);
	return tmp_p->key[0];
}

__tt(index_t, T)
ptrdiff_t
bptree<index_t, T>::max()
{
	bp_node *tmp_p = BPN(_root);

	while(tmp_p->child[0])
		tmp_p = BPN(tmp_p->child[tmp_p->keynum]);
	return tmp_p->key[tmp_p->keynum-1];
}

__tt(index_t, T)
int
bptree<index_t, T>::traverse(int visit(ptrdiff_t))
{
	int i, ret;
	bp_node *tmp_p = BPN(_root);

	while (tmp_p->child[0])
		tmp_p = BPN(tmp_p->child[0]);
	for (;;) {
		for (i=0; i<tmp_p->keynum; i++) {
			ret = visit(tmp_p->key[i]);
			if (ret)
				return ret;
		}
		if (!tmp_p->next)
			break;
		tmp_p = BPN(tmp_p->next);
	}
	return 0;
}

#ifdef _24k_BPTREE_PRINT

__tt(index_t, T)
void
bptree<index_t, T>::print()
{
	const int fl=0x1, fc=0x2, f_lcr=0xf, f_child=0x10;
	int i, line, flag=0;
	ptrdiff_t node=_root;
	bp_node *tmp_p;
	queue<ptrdiff_t> q;

	cout<<'{';
	q.push(node);
	q.push(OFF_NULL);
	line = q.size();
	flag |= fl;
	while (!q.empty()) {
		node = q.front();
		q.pop();
		if (line)
			line--;
		else {
			cout<<'\n';
			line = q.size();
			if (! (flag & f_child))
				break;
			else
				flag &= ~f_child;
		}
		tmp_p = BPN(node);
		if (node) {
			if (flag & fc)
				cout<<' ';
			else
				flag |= fc;
			bp_node_print<index_t, T>(tmp_p);
		} else {
			if (flag & fl) {
				cout<<'}'<<' ';
				flag &= ~f_lcr;
			} else {
				cout<<'{';
				flag |= fl;
			}
			continue;
		}
		q.push(OFF_NULL);
		if (tmp_p->child[0])
			for (i=0; i<=tmp_p->keynum; i++) {
				q.push(tmp_p->child[i]);
				flag |= f_child;
			}
		q.push(OFF_NULL);
	}
	cout<<endl;
}

#endif

}//namespace __tree

#undef __tt
#undef OFF_NULL
//#undef bp_node_init
//#undef BP_NEW
#undef BPN
#undef DIFF

#endif //_BPTREE_F_H_
