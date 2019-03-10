#include <iostream>
#include <string>
#define _24k_BPTREE_CHECK
#define _24k_BPTREE_PRINT
#include "bptree_f.h"
using namespace std;
using namespace _24k;

int
main()
{
	int i;
	bptree<int, int> T, load_t;

	for (i=0; i<100; i++) {
		T.insert(i);
		T.check();
	}

	cout<<"T"<<endl;
	T.print();

	T.savefile("_24k.bptree");
	load_t.loadfile("_24k.bptree");

	cout<<"load_t"<<endl;
	load_t.print();
}
