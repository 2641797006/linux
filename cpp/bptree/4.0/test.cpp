#include <iostream>
#define _24k_BPTREE_PRINT
#include "bptree_f.h"
using namespace std;
using namespace _24k;

int
main()
{
	int i;
	xbptree<int> tree_old, tree_new;

	for (i=0; i<100; i++)
		tree_old.insert(i);

	cout<<"tree_old:"<<endl;
	tree_old.print();

	tree_old.savefile("_24k.bptree");

	tree_new.loadfile("_24k.bptree");

	cout<<"tree_new:"<<endl;
	tree_new.print();
}
