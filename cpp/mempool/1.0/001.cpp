#include <iostream>
#include <time.h>
#include "mpvec.h"
using namespace std;


int
main()
{
	int i;
	size_t t0, t1;
	mempool<int> mem(10000);

	t0=clock();
	for (i=0; i<10000; i++)
		mem.alloc(sizeof(int));
	t1=clock();
	cout<<t1-t0<<endl;
}
