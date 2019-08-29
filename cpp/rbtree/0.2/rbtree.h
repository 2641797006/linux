#ifndef _RBTREE_H_
#define _RBTREE_H_

#ifndef _GLIBCXX_QUEUE
#include <queue>
#endif

#define __tt(T)	template <typename T>

namespace _24k {
using namespace std;
enum RB_Color { rb_black, rb_red };

__tt(T)
class RB_Node {
  public:
	RB_Color color;
	T key;
	RB_Node *parent, *left, *right;

	RB_Node(T const& t, RB_Color c, RB_Node *p, RB_Node *l, RB_Node *r)
	{
		key = t, color = c, parent = p, left = l, right = r;
	}

	RB_Node(T const& t, RB_Node *p, RB_Node *l, RB_Node *r)
	{
		new (this)RB_Node(t, rb_red, p, l, r);
	}

	RB_Node(T const& t)
	{
		new (this)RB_Node(t, rb_red, NULL, NULL, NULL);
	}

	void turn_red() { color = rb_red; }
	void turn_black() { color = rb_black; }
	bool is_red() { return color == rb_red; }
	bool is_black() { return color == rb_black; }
};

__tt(T)
class rbtree {
//  private:
  public:
	RB_Node<T> *root;
	size_t _size;
	unsigned int unique;

  public:
	rbtree() { root = NULL, _size = 0, unique = 0; }
	~rbtree(){}

	bool insert(T const&);

	void left_rotate(RB_Node<T>*);
	void right_rotate(RB_Node<T>*);

#ifdef _24k_RBTREE_PRINT
	void print();
#endif
};

__tt(T)
bool
rbtree<T>::insert(T const& t)
{
	RB_Node<T> *node, *node_p, *node_1;

	node = new RB_Node<T>(t);
	if ( ! node )
		return false;

	node_1 = root;
	node_p = NULL;
	while ( node_1 ) {
		node_p = node_1;
		if (node->key < node_1->key)
			node_1 = node_1->left;
		else
			node_1 = node_1->right;
	}

	node->parent = node_p;
	if ( ! node_p ) {
		root = node;
		root->turn_black();
		return true;
	}
	if (node->key < node_p->key)
		node_p->left = node;
	else
		node_p->right = node;
// fix
	while ( (node_p = node->parent) && node_p->is_red() ) {
		node_1 = node_p->parent;
		if (node_p == node_1->left) {
			if (node_1->right && node_1->right->is_red()) {
				node_1->right->turn_black();
				node_p->turn_black();
				node_1->turn_red();
				node = node_1;
				continue;
			}
			if (node_p->right == node) {
				left_rotate(node_p);
				RB_Node<T> *tmp = node_p;
				node_p = node;
				node = tmp;
			}
			node_p->turn_black();
			node_1->turn_red();
			right_rotate(node_1);
		} else {
			if (node_1->left && node_1->left->is_red()) {
				node_1->left->turn_black();
				node_p->turn_black();
				node_1->turn_red();
				node = node_1;
				continue;
			}
			if (node_p->left == node) {
				right_rotate(node_p);
				RB_Node<T> *tmp = node_p;
				node_p = node;
				node = tmp;
			}
			node_p->turn_black();
			node_1->turn_red();
			left_rotate(node_1);
		}
	}
	root->turn_black();
	++_size;
	return true;
}

__tt(T)
void
rbtree<T>::left_rotate(RB_Node<T> *node)
{
	RB_Node<T> *node_1 = node->right;

	node->right = node_1->left;
	if (node_1->left != NULL)
		node_1->left->parent = node;

	node_1->parent = node->parent;
	if (node->parent == NULL)
		root = node_1;
	else if (node->parent->left == node)
		node->parent->left = node_1;
	else
		node->parent->right = node_1;

	node_1->left = node;
	node->parent = node_1;
}

__tt(T)
void
rbtree<T>::right_rotate(RB_Node<T> *node)
{
	RB_Node<T> *node_1 = node->left;

	node->left = node_1->right;
	if (node_1->right != NULL)
		node_1->right->parent = node;

	node_1->parent = node->parent;
	if (node->parent == NULL)
		root = node_1;
	else if (node == node->parent->right)
		node->parent->right = node_1;
	else
		node->parent->left = node_1;

	node_1->right = node;
	node->parent = node_1;
}

#ifdef _24k_RBTREE_PRINT

__tt(T)
void
rbtree<T>::print()
{
	const int fl=0x1, fc=0x2, f_lcr=0xf;
	int line, flag=0;
	RB_Node<T> *node = root, *NIL = (RB_Node<T>*)-1;
	queue<RB_Node<T>*> q;

	cout<<'{';
	q.push(node);
	q.push(NULL);
	line = q.size();
	flag |= fl;
	while ( ! q.empty() ) {
		node = q.front();
		q.pop();
		if (line)
			line--;
		else {
			cout<<'\n';
			line = q.size();
		}
		if (node == NIL) {
#ifdef __linux__
			cout<<"\033[40;37m";
#endif
			cout<<"nil ";
#ifdef __linux__
			cout<<"\033[0m";
#endif
			continue;
		}
		if (node) {
			if (flag & fc)
				cout<<' ';
			else
				flag |= fc;
#ifdef __linux__
			if (node->is_black())
				cout<<"\033[40;37m";
			else
				cout<<"\033[41;37m";
#endif
			cout<< node->key;
#ifdef __linux__
			cout<<"\033[0m";
#endif
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
		q.push(NULL);
		if (node->left)
			q.push(node->left);
		else
			q.push(NIL);
		if (node->right)
			q.push(node->right);
		else
			q.push(NIL);
		q.push(NULL);
	}
	cout<<'\n';
}

#endif

} // namespace _24k

#undef __tt

#endif // _RBTREE_H_

