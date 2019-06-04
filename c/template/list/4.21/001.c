#include <stdio.h>

typedef struct{
	int *p;
}STU;

#define __list_t STU
#include "list.h"

void copy(STU* des, const STU* src)
{
	des->p = malloc(sizeof(int));
	*des->p = *src->p;
	printf("copy STU\n");
}

void destruct(STU *stu)
{
	free(stu->p);
	printf("destroy STU\n");
}

int
main()
{
	int i;
	STU _s, *const s=&_s;
	STU_list _L, *const L=&_L;

	STU_list_iterator it1;

	s->p = malloc(sizeof(int));
	*s->p = 24;

	STU_list_init(L);

	L->set_copyer(copy);
	L->set_destructor(destruct);

	for ( i=0; i<10; ++i ) {
		L->push_back(L, s);
		++*s->p;
	}

	for ( i=0; i<5; ++i )
		L->pop_back(L);

/* 遍历L: */

	it1 = L->begin(L);

	while ( it1 != L->end(L) ) {
		printf("%d ", *it1->p);
		it1 = L->next(L, it1);
	}
	puts("");

	L->destroy(L);

	return 0;
}

