#include <stdio.h>
#include <unistd.h>
#include "string24k.h"
#include "cli_box.h"

int main(int argc, char **argv)
{
	int i, n=1;
	string _s, *s=&_s;
	BOX _b, *b=&_b;

	string_init(s);
	box_init(b, '-', "+", "| ", " |");

	if (argc > 1)
		if ( sscanf(argv[1], "%d", &n) < 1 ) {
			printf(
"Usage: [command] | %s [-%%d]\n"
"           (Read data from the previous command)\n"
"   or  %s [-%%d] [string]\n"
"           (Use parameter 2 as the input string)\n"
"   or  %s [-%%d]\n"
"           (Read a line from the keyboard)\n"
,
argv[0], argv[0], argv[0]);
			return 24-'k';
		} else if (argc > 2)
			s->assign(s, argv[2]);

	if (s->empty(s))
		if ( isatty(fileno(stdin)) )
			s->getline(s);
		else
			s->fgetline(s, stdin, EOF);

	n = n>0 ? n : -n;
	for (i=0; i<n; ++i) {
		string_clear(b->strbuf);
		b->box(b, s);
		s->swap(s, b->strbuf);
	}

	printf("%s", string_c_str(s));

	return 24-'k';
}

