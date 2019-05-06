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
	int_list L1;
	stu_list L2;

	int_list_init(&L1);
	stu_list_init(&L2);

	for ( i=0; i<30; ++i ) {
		int_list_push_back(&L1, &i);
		s.i = i+60000;
		stu_list_push_back(&L2, &s);
	}

	for ( i=0; i<10; ++i ) {
		int_list_pop_back(&L1);
		stu_list_pop_back(&L2);
	}

	int_list_iterator it1 = int_list_first(&L1);
	stu_list_iterator it2 = stu_list_first(&L2);

// 遍历L1:
	while ( it1 != int_list_tail(&L1) ) {
		printf("%d ", *it1);
		it1 = int_list_next(it1);
	}
	puts("");

// 遍历L2:
	while ( it2 != stu_list_tail(&L2) ) {
		printf("[%c,%d] ", it2->c, it2->i);
		it2 = stu_list_next(it2);
	}
	puts("");

	int_list_save(&L1, "0"); // 保存L1到文件0
	int_list L3;
	int_list_load(&L3, "0"); // 从文件0加载list到L3

// 逆序遍历L3:
	int_list_iterator it3 = int_list_last(&L3);
	while ( it3 != int_list_head(&L3) ) {
		printf("%d ", *it3);
		it3 = int_list_prev(it3);
	}
	puts("");

	int_list_destroy(&L3);

	int_list_destroy(&L1);
	stu_list_destroy(&L2);
}

