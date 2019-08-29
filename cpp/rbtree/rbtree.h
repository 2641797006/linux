#ifndef _RBTREE_H_
#define _RBTREE_H_

#define __tt(T)	template <typename T>

namespace _24k {

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
  private:
	RB_Node<T> *root;
	size_t _size;
	unsigned int unique;

  public:
	rbtree() { root = NULL, _size = 0, unique = 0; }
	~rbtree(){}

	bool insert(T const&);

	void left_rotate(RB_Node<T>*);
	void right_rotate(RB_Node<T>*);
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
	while ( node_p && node_p->is_red() ) {
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

} // namespace _24k

#undef __tt

#endif // _RBTREE_H_

