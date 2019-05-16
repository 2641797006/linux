#include <stdio.h>

typedef struct{
	char c;
	float i;
}stu;

#define _24k_vector_t int
#include "vector.h"

#define _24k_vector_t stu
#include "vector.h"

int
main()
{
	int i;
	stu s = {'A', 0};

	int_vector v1;
	stu_vector v2;

	int_vector_init(&v1);
	stu_vector_init(&v2);

	for (i=0; i<30; ++i) {
		int_vector_push_back(&v1, &i);
		s.i=i*100;
		stu_vector_push_back(&v2, &s);
	}

	for (i=0; i<10; ++i) {
		int_vector_pop_back(&v1);
		stu_vector_pop_back(&v2);
	}

	int_vector_iterator it1 = int_vector_first(&v1);
	stu_vector_iterator it2 = stu_vector_first(&v2);

	while (it1 != int_vector_tail(&v1)) {
		printf("%d ", *it1);
		it1 = int_vector_next(it1);
	}
	puts("");
	while (it2 != stu_vector_tail(&v2)) {
		printf("[%c,%f] ", it2->c, it2->i);
		it2 = stu_vector_next(it2);
	}
	puts("");

	int_vector_destroy(&v1);
	stu_vector_destroy(&v2);
}
