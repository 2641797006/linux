#include <stdio.h>

typedef struct{
	char c;
	float i;
}stu;

#define _24k_vector_t int
#include "vector.h"

#define _24k_vector_t stu
#include "vector.h"

int print_int(int *p);
int print_stu(stu *p);

int
main()
{
	int i;
	stu s;

	int_vector v1;
	stu_vector v2;

	int_vector_init(&v1);
	stu_vector_init(&v2);

	for (i=0; i<20; ++i) {
		int_vector_push_back(&v1, &i);
		s.i=i*2+0.666666;
		stu_vector_push_back(&v2, &s);
	}

printf("\n<1> print int vector:\n");
	int_vector_traverse(&v1, print_int);
printf("\n<1> print stu vector:\n");
	stu_vector_traverse(&v2, print_stu);

	for (i=16; i>6; --i) {
		int_vector_erase(&v1, i);
		stu_vector_erase(&v2, i);
	}

printf("\n<2> print int vector:\n");
	int_vector_traverse(&v1, print_int);
printf("\n<2> print stu vector:\n");
	stu_vector_traverse(&v2, print_stu);



}

int print_int(int *p)
{
	printf("%d\n", *p);
	return 0;
}

int print_stu(stu *p)
{
	printf("%f\n", p->i);
	return 0;
}
