#include <stdio.h>

typedef struct{
	char c;
	int i;
}stu;

#define _24k_list_t int
#include "list.h"

#define _24k_list_t stu
#include "list.h"

int
main()
{
	int i;
	stu s = { 'A', 0 };
	int_list v1;
	stu_list v2;

	int_list_init(&v1);
	stu_list_init(&v2);

	for ( i=0; i<30; ++i ) {
		int_list_push_back(&v1, &i);
		s.i = i+60000;
		stu_list_push_back(&v2, &s);
	}

	for ( i=0; i<10; ++i ) {
		int_list_pop_back(&v1);
		stu_list_pop_back(&v2);
	}

	int_list_iterator it1 = int_list_first(&v1);
	stu_list_iterator it2 = stu_list_first(&v2);

	while ( it1 != int_list_tail(&v1) ) {
		printf("%d ", *it1);
		it1 = int_list_next(it1);
	}
	puts("");
	while ( it2 != stu_list_tail(&v2) ) {
		printf("[%c,%d] ", it2->c, it2->i);
		it2 = stu_list_next(it2);
	}
	puts("");
	int_list_destroy(&v1);
	stu_list_destroy(&v2);
}

