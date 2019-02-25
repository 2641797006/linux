#include <iostream>
#include "md5sum.h"
using namespace std;
using namespace _24k;

int main()
{
	md5sum md5;
	cout<<md5("123", "4")<<endl;
	md5.set_upper();
	cout<<md5("12", "34")<<endl;
	md5.set_lower();
	cout<<md5("1", "234")<<endl;
}
