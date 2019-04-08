#include <stdio.h>
#define list_t int
#include "list.h"

int
main()
{
	int i;
	const char *fname = "1.24k";
	list *L=malloc(sizeof(list));
	list *L1=malloc(sizeof(list));

	list_init(L);

	for (i=0; i<100; ++i)
		list_push_back(L, &i);

	list_save(L, fname);
	list_load(L1, fname);

	for (i=0; i<20; ++i)
		list_pop_front(L1);


	list_iterator it = list_first(L);
	while ( it != list_tail(L) ) {
		printf("%d ", *it);
		it = list_next(it);
	}
	puts("");

	it = list_first(L1);
	while ( it != list_tail(L1) ) {
		printf("%d ", *it);
		it = list_next(it);
	}
	puts("");

	list_destroy(L);
	list_destroy(L1);

}
