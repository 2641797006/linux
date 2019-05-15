#include <stdio.h>
#include <time.h>

typedef struct{
	time_t php;
	int fit;
}data;

#define _24k_list_t data
#include "list.h"

int
main()
{
	int i;
	data d;
	data_list L; // data双链表

	data_list_init(&L); // 初始化data list

	for (i=0; i<10; ++i) {
		d.php = time(NULL);
		d.fit = i;
		L.push_back(&L, &d); // 在链表末尾插入数据
	}

puts("顺序遍历:");
	data_list_iterator it = L.begin(&L); // data list 迭代器 it, 并让 it 指向 list 的第一个数据
	while (it != L.end(&L)) {	// it 不等于正向结尾 则继续
		printf("data.time: %ld\t time: %ld\t data.fit: list%d\n", it->php, time(NULL), it->fit);
		it = L.next(it);	// it 指向下一个data
	}

puts("");
puts("");

puts("逆序遍历:");
	it = L.rbegin(&L); // 让 it 指向 list 的 [倒数] 第一个数据
	while (it != L.rend(&L)) {       // it 不等于反向结尾 则继续
		printf("data.time: %ld\t time: %ld\t data.fit: list%d\n", it->php, time(NULL), it->fit);
		it = L.prev(it);        // it 指向上一个data
	}

	return 24-'k';
}
