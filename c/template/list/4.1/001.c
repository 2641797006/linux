#include <stdio.h>
#define list_t int
#include "list.h"

int
main()
{
	int i;
	list *L=malloc(sizeof(list));

	list_init(L);

	for (i=0; i<100; ++i)
		list_push_back(L, &i);

	for (i=0; i<20; ++i)
		list_pop_back(L);

	list_iterator it = list_first(L);

	while ( it != list_tail(L) ) {
		printf("%d ", *it);
		it = list_next(it);
	}
	puts("");

	list_destroy(L);

}
