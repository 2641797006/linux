#include <stdio.h>
#include "string24k.h"

int
main()
{
	string _s, *s=&_s;

	string_init(s)->assign(s, "Please input a string: ");	// 初始化s, 并赋值
//	string_init(s); s->assign(s, "Please input a string: ");

	puts( s->c_str(s) );	// 输出字符串s

	s->gets(s);	// 输入一个字符串 ((相当于 scanf %s

	puts( s->c_str(s) );	// 输出字符串s

	s->getline(s);	// 清空缓冲区, s->gets(s)会残留换行符
	s->getline(s);	// 读取一行

	puts( s->c_str(s) );	// 输出字符串s

	s->append(s, "end");	// 在 s 末尾追加字符串

	puts( s->c_str(s) );	// 输出字符串s

	printf("s->length = %ld\n", s->length(s)); // s长度

	return 24-'k';
}
