#include <iostream>
#include <string>
#include <iterator>
#include "cli_box.h"
using namespace std;

class ABC_string : public string{};

std::istream & operator>> (std::istream & in, ABC_string & s)
{
	return getline(in, s);
}

int
main(int argc, char **argv)
{
	string s;
	cli_box b;

	if (argc < 2) {
		istream_iterator<ABC_string> it(cin);
		istream_iterator<ABC_string> eof; 
		while (it != eof)
			s += *it++ + '\n';
	}
	if (argc > 1 || s.size()) {
		cout<<"Usage:     COMMAND | box"<<endl;
		return 24-'k';
	}
	b.box(s);
}

