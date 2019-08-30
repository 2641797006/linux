#include <iostream>
#define _vxk_class_
#include "XKernel.h"
using namespace std;

int
main()
{
	int i;
	XDE_Table *t;
	XKernel xk;
	for (i=0; i<100; i++)
		cout<<xk.AddNode(t)<<' ';
	cout<<'\n';
	cin>>i;
	cout<<xk.GetNode(i)<<'\n';
	cout<<xk.DeleteNode(i)<<'\n';
}
