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
		L1.push_back(&L1, &i);
		s.i = i+60000;
		L2.push_back(&L2, &s);
	}

	for ( i=0; i<10; ++i ) {
		L1.pop_back(&L1);
		L2.pop_back(&L2);
	}

	int_list_iterator it1 = L1.begin(&L1);
	stu_list_iterator it2 = L2.begin(&L2);

// 遍历L1:
	while ( it1 != L1.end(&L1) ) {
		printf("%d ", *it1);
		it1 = L1.next(it1);
	}
	puts("");

// 遍历L2:
	while ( it2 != L2.end(&L2) ) {
		printf("[%c,%d] ", it2->c, it2->i);
		it2 = L2.next(it2);
	}
	puts("");

	L1.save(&L1, "0"); // 保存L1到文件0

	int_list L3;
	int_list_init(&L3);

	L3.load(&L3, "0"); // 从文件0加载list到L3

// 逆序遍历L3:
	int_list_iterator it3 = L3.rbegin(&L3);
	while ( it3 != L3.rend(&L3) ) {
		printf("%d ", *it3);
		it3 = L3.prev(it3);
	}
	puts("");

	L3.destroy(&L3);

	L1.destroy(&L1);
	L2.destroy(&L2);
}

