#include <iostream>
#include <string>
#define _24k_BPTREE_CHECK
#define _24k_BPTREE_PRINT
#include "bptree_f.h"
using namespace std;
using namespace __tree;

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
	int i;
	string s;
	bptree<string, string> T;

	for (i=0; i<32; i++) {
		T.insert(reserve_word[i]);
		T.check();
		cout<<i<<'\n';
	}

	for (i=0; i<32; i++) {
		cout<<*(string*)((char*)T.baseptr()+T.find(reserve_word[i]))<<endl;
		T.check();
		cout<<i<<'\n';
	}

	for (i=0; i<32; i++) {
		T.erase(reserve_word[i]);
		T.print();
		T.check();
		cout<<i<<'\n';
	}
	T.check();
	cout<<"endl"<<endl;

}
