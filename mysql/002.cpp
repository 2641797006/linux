#include <iostream>
#include <string>
#include "mmsql.h"
using namespace std;
using namespace _24k;

int main()
{
	MMSQL mmsql("cpplay", "123456", "127.0.0.1");
	mmsql.connect();
	mmsql.query("set names utf8");
	mmsql.set_dbname("tmp");
	mmsql.query("select * from Student");

	for (auto x : mmsql.result()) {
		for (int i=0; i<mmsql.result_col(); ++i)
			cout<<x[i]<<' ';
		cout<<'\n';
	}
}

