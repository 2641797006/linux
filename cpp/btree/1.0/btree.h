#ifndef _BTREE_H_
#define _BTREE_H_

#ifndef _GLIBCXX_QUEUE
#include <queue>
#endif

#ifndef _GLIBCXX_IOMANIP
#include <iomanip>
#endif

#define __tt(T)	template <typename T>

#define MAX_T	4
#define MIN_T	((MAX_T+1)/2)

namespace __btree{
using namespace std;

__tt(T)
class bt_node{
  public:
	int		keynum;
	bt_node<T>	*parent;
	T		*key[MAX_T];
	bt_node<T>	*child[MAX_T+1];

	void print();
	void printx();
	void clrc();
	bt_node(bt_node<T>* const& p=NULL): keynum(0), parent(p) {clrc();}
//	static int max_t, min_t;
};

__tt(T)
inline void
bt_node<T>::clrc()
{
	int i;
	for (i=0; i<MAX_T+1; i++)
		child[i] = NULL;
}
#define lw(x)	hex<<((long long)(x)&0xffff)<<dec
__tt(T)
void
bt_node<T>::printx()
{
	int i;
	cout<<'{';
	for (i=0; i<keynum-1; i++) {
		cout<<'#'<<lw(child[i])<<' ';
		cout<<*key[i]<<' ';
	}
	if (keynum) {
		cout<<'#'<<lw(child[i])<<' ';
		cout<<*key[i];
		cout<<' '<<'#'<<lw(child[i+1])<<'['<<lw(parent)<<','<<lw(this)<<']';
	}
	cout<<'}';
}
#undef lw

__tt(T)
void
bt_node<T>::print()
{
	int i;
	cout<<'{';
	for (i=0; i<keynum-1; i++)
		cout<<*key[i]<<' ';
	if (keynum)
		cout<<*key[i];
	cout<<'}';
}

/* class btree */
__tt(T)
class btree{
  public:
	void print();
	bt_node<T>* const& root(){return _root;}
	T* find(T const& t);
	int insert(T const& t);
	int erase(T const& t);

	btree();
	~btree();

  private:
	bt_node<T> *_root;

	T* find_t(bt_node<T>*& node, T const& t, int& i);
	int find_to_insert(bt_node<T>*& node, T const& t);
	void split(bt_node<T>* const& node, bt_node<T>*& node_1, int leaf);
	int get_cind(bt_node<T>* const& node);
};

__tt(T)
btree<T>::btree()
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
		delete node;
	}
}

__tt(T)
int
btree<T>::get_cind(bt_node<T>* const& node)
{
	int i;
	bt_node<T> *node_p = node->parent;
	if (!node_p)
		return -1;
	for (i=0; i<node_p->keynum; i++)
		if (node_p->child[i]==node)
			break;
	return i;
}

__tt(T)
inline T*
btree<T>::find(T const& t)
{
	return find_t(NULL, t, 0);
}

__tt(T)
T*
btree<T>::find_t(bt_node<T>*& node, T const& t, int& i)
{
	if (!_root)
		return NULL;
	if (!node)
		node = _root;
	for (;;) {
		for (i=0; i<node->keynum; i++)
			if (t<=*node->key[i])
				break;
		if ((i<node->keynum) && (t==*node->key[i]))
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
	int i, cind;
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
		cind = get_cind(node);
		if (cind && (node_p->child[cind-1]->keynum>=MIN_T)) {
			i = node->keynum;
			node->child[i+1] = node->child[i];
			while (--i>=0) {
				node->key[i+1] = node->key[i];
				node->child[i+1] = node->child[i];
			}
			node->key[0] = node_p->key[cind-1];
			node_1 = node_p->child[cind-1];
			node_p->key[cind-1] = node_1->key[node_1->keynum-1];
			node->child[0] = node_1->child[node_1->keynum];
			if (node->child[0])
				node->child[0]->parent = node;
			node->keynum++, node_1->keynum--;
			return 1;
		}
		else if ((cind+1<=node_p->keynum) && (node_p->child[cind+1]->keynum>=MIN_T)) {
			node_1 = node_p->child[cind+1];
			node->key[node->keynum] = node_p->key[cind];
			if (node_1->child[0]) {
				node_1->child[0]->parent = node;
				node->child[node->keynum+1] = node_1->child[0];
			}
			node_p->key[cind] = node_1->key[0];
			for (i=1; i<node_1->keynum; i++) {
				node_1->key[i-1] = node_1->key[i];
				node_1->child[i-1] = node_1->child[i];
			}
			node_1->child[i-1] = node_1->child[i];
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
			for (i=0; i<node_1->keynum; i++) {
				node->key[node->keynum+i] = node_1->key[i];
				if (node_1->child[i]) {
					node_1->child[i]->parent = node;
					node->child[node->keynum+i] = node_1->child[i];
				}
			}
			if (node_1->child[i]) {
				node_1->child[i]->parent = node;
				node->child[node->keynum+i] = node_1->child[i];
			}
			node->keynum += node_1->keynum;
			node = node_p;
			delete node_1;
		}
	}
	return 1;
}

__tt(T)
int
btree<T>::find_to_insert(bt_node<T>*& node, T const& t)
{
	int i;
	for (;;) {
		for (i=0; i<node->keynum; i++)
			if (t<=*node->key[i])
				break;
		if (node->child[i])
			node = node->child[i];
		else
			break;
	}
	return i;
}

__tt(T)
void
btree<T>::split(bt_node<T>* const& node, bt_node<T>*& node_1, int leaf)
{
	int i;
	node_1 = new bt_node<T>(node->parent);

	for (i=MIN_T; i<MAX_T; i++) {
		node_1->key[i-MIN_T] = node->key[i];
		if (!leaf) {
			node->child[i]->parent = node_1;
			node_1->child[i-MIN_T] = node->child[i];
		}
	}
	if (!leaf) {
		node->child[i]->parent = node_1;
		node_1->child[i-MIN_T] = node->child[i];
	}
	node_1->keynum = MIN_T;
	node->keynum = MIN_T-1;
}

__tt(T)
int
btree<T>::insert(T const& t)
{
	int i, j, leaf;
	bt_node<T> *node=_root, *node_1, *node_p;
	i = find_to_insert(node, t);
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
			node_p = node;
			node_1->parent = node_p;
			node = new bt_node<T>(node_p);
			for (i=0; i<MIN_T-1; i++) {
				node->key[i] = node_p->key[i];
				if (!leaf) {
					node_p->child[i]->parent = node;
					node->child[i] = node_p->child[i];
				}
			}
			if (!leaf) {
				node_p->child[i]->parent = node;
				node->child[i] = node_p->child[i];
			}
			node->keynum = MIN_T-1;
			node_p->key[0] = node_p->key[MIN_T-1];
			node_p->child[0] = node;
			node_p->child[1] = node_1;
			node_p->keynum = 1;
			break;
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
		leaf = 0;
	}
	return 0;
}

__tt(T)
void
btree<T>::print()
{
	const int fl=0x1, fc=0x2, f_lcr=0xf, f_child=0x10;
	int i, line, flag=0;
	bt_node<T> *node=_root;
	queue<bt_node<T>*> q;

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

}//namespace __btree

#endif
