#include <iostream>

#define _24k_RBTREE_PRINT
#include "rbtree.h"

using namespace std;
using namespace _24k;

int main()
{
	int i;
	rbtree<int> tree;


	for (i=0; i<20; ++i) {
		tree.insert(i);
		tree.print();
		cout<<'\n'<<'\n';
	}

//	tree.print();

}

