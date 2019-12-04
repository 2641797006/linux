#include <stdio.h>

typedef struct {
	char c;
	int i;
} Stu;

#define __list_t int
#include "list.h"

#define __list_t Stu
#include "list.h"

int main() {
	int i;
	Stu s = { 'A', 0 };

	int_list _L1, *L1 = &_L1;
	Stu_list _L2, *L2 = &_L2;

	int_list_init(L1);
	Stu_list_init(L2);

	for (i=0; i<30; ++i) {
		L1->push_back(L1, &i);
		s.i = i + 60000;
		L2->push_back(L2, &s);
	}

	for (i=0; i<10; ++i) {
		L1->pop_back(L1);
		L2->pop_back(L2);
	}

	int_list_iterator it1 = L1->begin(L1);
	Stu_list_iterator it2 = L2->begin(L2);

	while (it1 != L1->end(L1)) {
		printf("%d ", *it1);
		it1 = L1->next(L1, it1);
	}
	puts("");

	while (it2 != L2->end(L2)) {
		printf("[%c,%d] ", it2->c, it2->i);
		it2 = L2->next(L2, it2);
	}
	puts("");
}


