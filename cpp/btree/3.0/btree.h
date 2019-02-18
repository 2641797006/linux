#ifndef _BTREE_H_
#define _BTREE_H_

#ifndef _GLIBCXX_QUEUE
#include <queue>
#endif

#define __tt(T)	template <typename T>

#ifndef MAX_T
#define MAX_T	4
#endif

#ifndef MIN_T
#define MIN_T	((MAX_T+1)/2)
#endif

namespace __tree{
using namespace std;	//std::queue

__tt(T)
class bt_node{
  public:
	int		keynum;
	bt_node<T>	*parent;
	T		*key[MAX_T];
	bt_node<T>	*child[MAX_T+1];

	void clrc();
	bt_node(bt_node<T>* p=NULL): keynum(0), parent(p) {clrc();}
};

__tt(T)
inline void
bt_node<T>::clrc()
{
	int i;
	for (i=0; i<MAX_T+1; i++)
		child[i] = NULL;
}

/* class btree */
__tt(T)
class btree{
  public:
	T* find(T const& t);
	T* insert(T const& t);
	int erase(T const& t);

	int isunique(){return unique;}
	void set_unique(){unique=1;}
	void set_nounique(){unique=0;}
	btree();
	~btree();

  private:
	int unique;
	bt_node<T> *_root;

	T* find_t(bt_node<T>*& node, T const& t, int& i);
	void split(bt_node<T>* node, bt_node<T>*& node_1, int leaf);
};

__tt(T)
btree<T>::btree(): unique(0)
{
	_root = new bt_node<T>;
}

__tt(T)
btree<T>::~btree()
{
	int i;
	bt_node<T> *node;
	queue<bt_node<T>*> q;

	q.push(_root);
	while (!q.empty()) {
		node = q.front();
		q.pop();
		if (node->child[0])
			for (i=0; i<=node->keynum; i++)
				q.push(node->child[i]);
		for (i=0; i<node->keynum; i++)
			delete node->key[i];
		delete node;
	}
}

__tt(T)
inline T*
btree<T>::find(T const& t)
{
	int i;
	bt_node<T> *node=_root;
	return find_t(node, t, i);
}

__tt(T)
T*
btree<T>::find_t(bt_node<T>*& node, T const& t, int& i)
{
	if (!node)
		node = _root;
	for (;;) {
		for (i=0; i<node->keynum; i++)
			if (t<=*node->key[i])			// <=
				break;
		if ((i<node->keynum) && (t==*node->key[i]))	// == Can be improved
			break;
		if (node->child[i])
			node = node->child[i];
		else
			return NULL;
	}
	return node->key[i];
}

__tt(T)
int
btree<T>::erase(T const& t)
{
	int i, cind, leaf;
	T *tp;
	bt_node<T> *node=_root, *node_1, *node_p;

	tp = find_t(node, t, i);
	if (!tp)
		return 0;
	delete tp;
	while (node->child[i]) {
		node = node->child[i];
		node->parent->key[i] = node->key[node->keynum-1];
		i = node->keynum-1;
	}
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
				_root = new bt_node<T>;
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
				node->child[0] = node_1->child[node_1->keynum];
				node->child[0]->parent = node;
			}
			else
				while (--i>=0)
					node->key[i+1] = node->key[i];
			node->key[0] = node_p->key[cind-1];
			node_p->key[cind-1] = node_1->key[node_1->keynum-1];
			node->keynum++, node_1->keynum--;
			return 1;
		}
		else if ((cind+1<=node_p->keynum) && (node_p->child[cind+1]->keynum>=MIN_T)) {
			node_1 = node_p->child[cind+1];
			node->key[node->keynum] = node_p->key[cind];
			node_p->key[cind] = node_1->key[0];
			if (!leaf) {
				node_1->child[0]->parent = node;
				node->child[node->keynum+1] = node_1->child[0];
				for (i=1; i<node_1->keynum; i++) {
					node_1->key[i-1] = node_1->key[i];
					node_1->child[i-1] = node_1->child[i];
				}
				node_1->child[i-1] = node_1->child[i];
			}
			else
				for (i=1; i<node_1->keynum; i++)
					node_1->key[i-1] = node_1->key[i];
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
			node->key[node->keynum] = node_p->key[cind];
			node->keynum++;
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
			else
				for (i=0; i<node_1->keynum; i++)
					node->key[node->keynum+i] = node_1->key[i];
			node->keynum += node_1->keynum;
			node = node_p;
			delete node_1;
		}
		leaf ? (leaf=0) : 0;
	}
	return 1;
}

__tt(T)
void
btree<T>::split(bt_node<T>* node, bt_node<T>*& node_1, int leaf)
{
	int i;
	node_1 = new bt_node<T>(node->parent);

	if (!leaf) {
		for (i=MIN_T; i<MAX_T; i++) {
			node_1->key[i-MIN_T] = node->key[i];
			node->child[i]->parent = node_1;
			node_1->child[i-MIN_T] = node->child[i];
		}
		node->child[i]->parent = node_1;
		node_1->child[i-MIN_T] = node->child[i];
	}
	else
		for (i=MIN_T; i<MAX_T; i++)
			node_1->key[i-MIN_T] = node->key[i];
	node_1->keynum = MAX_T-MIN_T;
	node->keynum = MIN_T-1;
}

__tt(T)
T*
btree<T>::insert(T const& t)
{
	int i, j, leaf;
	bt_node<T> *node=_root, *node_1, *node_p;

	for (;;) {
		for (i=0; i<node->keynum; i++)
			if (t<=*node->key[i])
				break;
		if (unique && (i<node->keynum) && (t==*node->key[i]))
			return node->key[i];
		if (node->child[i])
			node = node->child[i];
		else
			break;
	}
	for (j=node->keynum; j>i; j--)
		node->key[j] = node->key[j-1];
	node->key[i] = new T;
	*node->key[i] = t;
	node->keynum++;
	leaf = 1;
	while (node->keynum==MAX_T) {
		split(node, node_1, leaf);
		node_p = node->parent;
		if (!node_p) {
			_root = new bt_node<T>;
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
		node_p->key[i] = node->key[MIN_T-1];
		node_p->child[i+1] = node_1;
		node_p->keynum++;
		node = node_p;
		leaf ? (leaf=0) : 0;
	}
	return NULL;
}

}//namespace __tree

#undef __tt

#endif
