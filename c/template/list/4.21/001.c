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
	STU s;
	STU_list L1;

	s.p = malloc(sizeof(int));
	*s.p = 24;

	STU_list_init(&L1);

	L1.set_copyer(copy);
	L1.set_destructor(destruct);

	for ( i=0; i<10; ++i ) {
		L1.push_back(&L1, &s);
		++*s.p;
	}

	for ( i=0; i<5; ++i )
		L1.pop_back(&L1);

	STU_list_iterator it1 = L1.begin(&L1);

/* 遍历L1: */
	while ( it1 != L1.end(&L1) ) {
		printf("%d ", *it1->p);
		it1 = L1.next(&L1, it1);
	}
	puts("");

	L1.destroy(&L1);

	return 0;
}

