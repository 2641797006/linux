#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class cli_box{
  public:
	cli_box(char x, string a, string yl, string yr);
	void set_align(int);

	void line(size_t n);
	void line(string&, size_t, size_t);
	void box(string);

	size_t width_fix(string const&, size_t, size_t);
	size_t str_width(string const&);

  private:
	int flag;
	char px;
	string pa;
	string pyl, pyr;
	int width;
};

cli_box::cli_box(char x='-', string a="+", string yl="| ", string yr=" |")
	: flag(-1), px(x), pa(a), pyl(yl), pyr(yr){}

void
cli_box::set_align(int i) { flag = i; }

void
cli_box::line(size_t n)
{
	size_t i, w;
	w = n + pyl.size() + pyr.size() - 2;
	cout<<pa;
	for (i=0; i<w; ++i)
		cout<<px;
	cout<<pa<<'\n';
}

void
cli_box::line(string& s, size_t pos1, size_t pos2)
{
	int c;
	size_t i, wd, left, right;
	wd = width - width_fix(s, pos1, pos2);
	if (flag < 0)
		left = 0, right = wd;
	else if (flag > 0)
		left = wd, right = 0;
	else
		left = wd/2, right = wd - left;
	cout<<pyl;
	for (i=0; i<left; ++i)
		cout<<' ';
	c = s[pos2];
	s[pos2] = 0;
	cout<<(&s[pos1]);
	s[pos2] = c;
	for (i=0; i<right; ++i)
		cout<<' ';
	cout<<pyr;
	cout<<'\n';
}

void
cli_box::box(string s)
{
	size_t pos1=0, pos2;
	str_width(s);
	line(width);
	for (;pos1<s.size();) {
		pos2 = s.find_first_of('\n', pos1);
		if (pos2 == string::npos)
			pos2 = s.size();
		line(s, pos1, pos2);
                pos1 = pos2 + 1;
	}
	line(width);
}

size_t
cli_box::str_width(string const& s)
{
	size_t pos1=0, pos2, subw, width=0;
	for (;pos1<s.size();) {
		pos2 = s.find_first_of('\n', pos1);
		if (pos2 == string::npos)
			pos2 = s.size();
		subw = width_fix(s, pos1, pos2);
		if (subw > width)
			width = subw;
		pos1 = pos2 + 1;
	}
	this->width = width;
	return width;
}

// for chinese
size_t
cli_box::width_fix(string const& s, size_t pos1, size_t pos2)
{
	size_t i, width = pos2 - pos1;
	for (i=pos1; i<pos2; ++i)
		if ((unsigned char)s[i] > 0x7f)
			--width, i+=2;
	return width;
}

