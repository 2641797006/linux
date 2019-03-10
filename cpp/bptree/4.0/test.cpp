#include <iostream>
#include <string>
#define _24k_BPTREE_CHECK
#define _24k_BPTREE_PRINT
#include "bptree_f.h"
using namespace std;
using namespace _24k;

static const char *reserve_word[32] = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};

int
main()
{
	int i, a[100], *p[100];
	string s;
//	bptree<string, string> T;
//	bptree<string, string>::iterator it;
	bptree<int, int> T, T2;
	bptree<int, int>::iterator it;

	for (i=0; i<100; i++) {
		T.check();
		T.insert(i);
		T.check();
	}
		T.print();
/*
	for (i=0; i<100; i++) {
		T.check();
		T.erase(100-i);
		T.print();
	}
*/
	T.savefile("_24k.bptree");
	T2.loadfile("_24k.bptree");
	T2.print();













/*	for (i=0; i<32; i++) {
		cout<<*(string*)((char*)baseptr()+T.find(reserve_word[i]))<<endl;
		T.check();
		cout<<i<<'\n';
	}
*
	for (i=0; i<32; i++) {
		T.erase(reserve_word[i]);
	//	T.print();
		T.check();
		cout<<"size="<<T.size()<<" front()="<<T.front()<<" back()="<<T.back()<<'\n';
		cout<<i<<'\n';
	}
*/
/*
	T.check();
	cout<<"iterator begin:"<<endl;
	if (T.empty()) {
		cout<<"empty()"<<endl;
		return 0;
	}
	for (it=T.begin(); it!=T.end(); it++) {
		cout<<*it<<' ';
	}
	cout<<"\n*****endl*****"<<endl;
*/
}
