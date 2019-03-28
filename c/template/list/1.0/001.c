#include <stdio.h>

#define _24k_list_t int
#include "list.h"

int print_int(int*);

int
main()
{
	int i;
	int_list v1;

	int_list_init(&v1);

	for ( i=0; i<100; ++i ) {
		int_list_push_back(&v1, &i);
		int_list_push_front(&v1, &i);
	}

	int_list_traverse(&v1, print_int);
	puts("");

	for ( i=0; i<50; ++i ) {
		int_list_pop_back(&v1);
		int_list_pop_front(&v1);
	}

	int_list_traverse(&v1, print_int);
	puts("");

	int_list_destroy(&v1);
}

int print_int(int *p)
{
	printf("%d ", *p);
	return 0;
}

