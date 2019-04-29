#include <iostream>
#include <iomanip>
#include <string>
#include <memory.h>
using namespace std;

class cli_box{
  public:
	cli_box(char x='-', string a="+", string yl="| ", string yr=" |");
	void set_align(int);

	void box(string);

  private:
	int flag;
	char px;
	string pa;
	string pyl, pyr;
	int width;
};

int
main(int argc, char **argv)
{
	int i;
	const size_t buf_size = BUFSIZ;
	char *buf = (char*)malloc(buf_size);
	string s;
	cli_box b;

	memset(buf, 0, buf_size);
	setvbuf(stdin, buf, _IOLBF, buf_size);

	if (argc < 2)
		getline(cin, s), s.assign(buf);
	else
		for (i=1; i<argc; ++i) {
			s += argv[i];
			if (i<argc-1)
				s.push_back('\n');
		}
	b.set_align(0);
	b.box(s);
}

