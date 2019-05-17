#include <stdio.h>
#include "string.c"

#define _24k_list_t string
#include "list.h"

void print(string_list*);

void copy(string *s1, const string *s2)
{
	string_init(s1)->add(s1, s2);
}

void destruct(string *s)
{
	s->destroy(s);
}

int
main()
{
	string _s, *s=&_s;
	string_list _L, *L=&_L;

	string_init(s);
	string_list_init(L);

	L->set_copyer(copy);
	L->set_destructor(destruct);

	s->assign(s, "Please input a string: ");

	puts(s->c_str(s));

	for (;;) {
		s->getline(s);
		if (s->size(s) > 0)
			L->push_back(L, s);
		print(L);
	}

	L->destroy(L);
	s->destroy(s);
	return 24-'k';
}

void print(string_list *L)
{
	puts("");
	puts("string_list:");
	string_list_iterator it = L->begin(L);
	while (it != L->end(L)) {
		puts(it->c_str(it));
		it = L->next(L, it);
	}
	puts("");
}

