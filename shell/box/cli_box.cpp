#include "cli_box.h"

using namespace std;

cli_box::cli_box(char x, string a, string yl, string yr)
	: flag(0), px(x), pa(a), pyl(yl), pyr(yr){}

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

// draw box on CLI
void
cli_box::box(string s)
{
	size_t pos1=0, pos2;
	string_width(s);
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

// get the max width of string
size_t
cli_box::string_width(string const& s)
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

// fix string width for chinese
size_t
cli_box::width_fix(string const& s, size_t pos1, size_t pos2)
{
	size_t i, width = pos2 - pos1;
	for (i=pos1; i<pos2; ++i)
		if ((unsigned char)s[i] > 0x7f)
			--width, i+=2;
	return width;
}

