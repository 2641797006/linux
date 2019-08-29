#include <iostream>
#include "rbtree.h"

using namespace std;
using namespace _24k;

int main()
{
	int i;
	rbtree<int> tree;

	for (i=0; i<1000; ++i)
		tree.insert(i);

}

