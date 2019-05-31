#include <stdio.h>
#include "string24k.h"
#include "cli_box.h"

int main(int argc, char **argv)
{
	string _s, *s=&_s;
	BOX _b, *b=&_b;

	string_init(s);
	box_init(b, '-', "+", "| ", " |");

	if (argc < 2) {
		s->fgetline(s, stdin, EOF);
	}
	if (argc > 1 || ! s->size(s) ) {
		printf("Usage:     COMMAND | box [%%d]\n");
		return 24-'k';
	}
	b->box(b, s);
	printf("%s", string_c_str(b->strbuf));
}

