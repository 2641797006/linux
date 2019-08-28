#ifndef _CLI_BOX_H_
#define _CLI_BOX_H_

#ifndef _GLIBCXX_IOSTREAM
#include <iostream>
#endif

#ifndef _GLIBCXX_STRING
#include <string>
#endif

using namespace std;

class cli_box{
  public:
	cli_box(char x='-', string a="+", string yl="| ", string yr=" |");
	void set_align(int);

	void line(size_t n);
	void line(string&, size_t, size_t);
	void box(string);

	size_t width_fix(string const&, size_t, size_t);
	size_t string_width(string const&);

  private:
	int flag;
	char px;
	string pa;
	string pyl, pyr;
	int width;
};

#endif // _CLI_BOX_H_
