#include <iostream>
#include "mmsql.h"
using namespace std;
using namespace _24k;

int main()
{
	MMSQL mmsql("root", "123456", "111.222.66.66");
	mmsql.connect();
	mmsql.query("set names utf8");
	mmsql.set_dbname("my_database");
	mmsql.query("select * from my_table");

	for (auto x : mmsql.result()) {
		for (int i=0; i<mmsql.result_col(); ++i)
			cout<<x[i]<<' ';
		cout<<'\n';
	}
}

