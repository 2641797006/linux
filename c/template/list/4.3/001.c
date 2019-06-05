#include <stdio.h>

#define __list_t int
#include "list.h"

int print(int *p)
{
	printf("%d ", *p);
	return 0;
}

int to_rm(const int *p)
{
	if (*p > 50)
		return 1;
	return 0;
}

int to_find(const int *p)
{
	if (*p >= 24)
		return 1;
	return 0;
}

int
main()
{
	int i;
	int_list _L, *const L=&_L, *L1;

	int_list_init(L);

	for ( i=1; i<=100; ++i )
		L->push_back(L, &i);

	L->traverse(L, print);
	puts("");
	puts("");

	L->remove_if(L, to_rm);
	L->traverse(L, print);
	puts("");
	puts("");

	L1 = L->find_if(L, to_find);
	L1->traverse(L1, print);
	puts("");

	L->destroy(L);
	L1->destroy(L1);
	free(L1);

	return 0;
}

