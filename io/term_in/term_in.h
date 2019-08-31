#ifndef _TERM_IN_H_
#define _TERM_IN_H_

#ifndef _GETCH_H_
#include "getch.h"
#endif

#ifndef _GLIBCXX_IOSTREAM
#include <iostream>
#endif

#ifndef _GLIBCXX_STRING
#include <string>
#endif

namespace _24k
{
using namespace std;

char tin_cache[128];
//void cursor_up(int n=1);
//void cursor_down(int n=1);
void cursor_left(int n=1);
void cursor_right(int n=1);
void clear_line();
void backspace(string&, int&);
void save_cursor();
void unsave_cursor();

string
input_line()
{
	int c, index=0;
	string istr;

	init_getch();
	set_getch();
	for (;;) {
		c = getchar();
		if (c == '\n') {
			putchar('\n');
			break;
		}
		switch ( c ) {
		case 127://backspace
			backspace(istr, index);
			break;
		case 27://Esc
			if ( (c=getchar()) != '[' ) {
				ungetc(c, stdin);
				continue;
			}
			c = getchar();
			switch (c) {
			case 'D':
				cursor_left();
				if (index > 0)
					--index;
				continue;
			case 'C':
				if ((unsigned)index < istr.size())
					++index;
				cursor_right();
				continue;
			}
			break;
		}
		putchar(c);
		istr.insert(index++, 1, c);
	}
	return istr;
	end_getch();
}


void cursor_left(int n)
{
	sprintf(tin_cache, "\033[%dD", n);
	cout<<tin_cache;
}

void cursor_right(int n)
{
	sprintf(tin_cache, "\033[%dC", n);
	cout<<tin_cache;
}

void clear_line()
{
	cout<<"\033[K";
}

void save_cursor()
{
	cout<<"\033[s";
}

void unsave_cursor()
{
	cout<<"\033[u";
}

void backspace(string& s, int& index)
{
	cursor_left();
	clear_line();
//	save_cursor();
	s.erase(--index);
	cout<<s.c_str()+index;
//	unsave_cursor();
}

} // namespace _24k

#endif

