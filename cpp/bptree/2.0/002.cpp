#include <iostream>
#include <string>
using namespace std;

int
main()
{
	void *p=(void*)new char[10000];
	string s(__TIME__);
	cout<<s<<endl;
	*(string*)p = s;
	cout<<*(string*)p<<endl;
}
