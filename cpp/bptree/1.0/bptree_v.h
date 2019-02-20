#ifndef _BPTREE_H_
#define _BPTREE_H_

#ifndef _GLIBCXX_QUEUE
#include <queue>
#endif

#define __tt(T1, T2)	template <typename T1, typename T2>

#define MAX_T	4
#define MIN_T	((MAX_T+1)/2)

namespace __tree{
using namespace std;

class bp_node{
  public:
	int		keynum;
	bp_node		*parent;
	void		*key[MAX_T];
	bp_node		*child[MAX_T+1];
	bp_node		*next;

	void print();
	void printx();
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

void
bp_node::print()
{
	int i;
	cout<<'{';
	if (child[0]) {
		for (i=0; i<keynum-1; i++)
			cout<<*(int*)key[i]<<' ';
		if (keynum)
			cout<<*(int*)key[i];
	}
	else {
		for (i=0; i<keynum-1; i++)
			cout<<*(int*)key[i]<<' ';
		if (keynum)
			cout<<*(int*)key[i];
	}
	cout<<'}';
}

#define lw(x)	hex<<((long long)(x)&0xffff)<<dec
void
bp_node::printx()
{
	int i;
	cout<<'{';
	if (child[0]) {
		for (i=0; i<keynum-1; i++) {
			cout<<'#'<<lw(child[i])<<' ';
			cout<<*(int*)key[i]<<' ';
		}
		if (keynum) {
			cout<<'#'<<lw(child[i])<<' ';
			cout<<*(int*)key[i];
			cout<<' '<<'#'<<lw(child[i+1])<<'['<<lw(parent)<<','<<lw(this)<<']';
		}
	}
	else {
		for (i=0; i<keynum-1; i++) {
			cout<<'#'<<lw(child[i])<<' ';
			cout<<*(int*)key[i]<<' ';
		}
		if (keynum) {
			cout<<'#'<<lw(child[i])<<' ';
			cout<<*(int*)key[i];
			cout<<' '<<'#'<<lw(child[i+1])<<'['<<lw(parent)<<','<<lw(this)<<']';
		}
	
	}
	cout<<'}';
}
#undef lw

/* class bptree */
__tt(index_t, T)
class bptree{
  public:
	T* find(T const& t);
	T* insert(T const& t);
	int erase(T const& t);

	void print();
	bptree();
	~bptree();

  private:
	int unique;
	bp_node *_root;

	T* find_t(bp_node*& node, T const& t, int& i);
	void split(bp_node* node, bp_node*& node_1, int leaf);
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
			for (i=0; i<node->keynum; i++)
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
	if (unique && (t==*(T*)node->key[i]))
		return (T*)node->key[i];
	for (j=node->keynum; j>i; j--)
		node->key[j] = node->key[j-1];
	node->key[i] = new T;
	*(T*)node->key[i] = t;
	leaf = 1;
	while (++node->keynum==MAX_T) {
		split(node, node_1, leaf);
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
void
bptree<index_t, T>::print()
{
	const int fl=0x1, fc=0x2, f_lcr=0xf, f_child=0x10;
	int i, line, flag=0;
	bp_node *node=_root;
	queue<bp_node*> q;

	cout<<'{';
	q.push(node);
	q.push(NULL);
	line = q.size();
	flag|=fl;
	while (!q.empty()) {
		node = q.front();
		q.pop();
		if (line)
			line--;
		else {
			cout<<'\n';
			line = q.size();
			if (!(flag&f_child))
				break;
			else
				flag&=~f_child;
		}
		if (node) {
			flag|=fc;
			node->print();
			cout<<' ';
		}
		else {
			if (flag&fl) {
				if (flag&fc)
					cout<<'\b';
				cout<<"} ";
				flag&=~f_lcr;
			}
			else {
				cout<<'{';
				flag|=fl;
			}
			continue;
		}
		q.push(NULL);
		if (node->child[0])
			for (i=0; i<=node->keynum; i++) {
				q.push(node->child[i]);
				flag|=f_child;
			}
		q.push(NULL);
	}
	cout<<endl;
}

}//namespace __tree

#undef __tt

#endif
