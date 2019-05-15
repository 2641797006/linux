#include <stdio.h>
#include <time.h>

typedef struct{
	time_t php;
	int fit;
}data;

#define _24k_list_t data
#include "list.h"

void print(data_list*);

int
main()
{
	int i;
	data d;
	data_list L; // data双链表
	data_list_iterator it, it1;

	data_list_init(&L); // 初始化data list

	for (i=0; i<10; ++i) {
		d.php = time(NULL);
		d.fit = i;
		L.push_back(&L, &d); // 在链表末尾插入数据
	}

	print(&L); // 输出list

	it = L.begin(&L);
	while (it != L.end(&L)) {
		it1 = L.next(it);	// it1 = it的下一个
		if (it->fit == 6)
			L.erase(&L, it); // 删除L中it指向的数据, 此操作会使迭代器it失效
		it = it1;
	}

	print(&L); // 输出list

	return 24-'k';
}

void print(data_list *list)
{
	data_list_iterator it = list->begin(list);
	while (it != list->end(list)) {
		printf("%d ", it->fit);
		it = list->next(it);
	}
	puts("");
}

