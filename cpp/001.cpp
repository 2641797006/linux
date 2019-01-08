#include <iostream>
#include </home/cpplay/cpp/file/pfile.h>
using namespace std;
using namespace __pfile;

int main()
{
	char *buf=new char[0x1000];
	pfile pf("cpplay.tmp", ios::in);
	pf.print();
	pf.close();
	delete[] buf;
	return 0;
}
