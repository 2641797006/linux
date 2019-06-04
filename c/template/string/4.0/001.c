#include <stdio.h>
#include "__string.h"

int
main()
{
	string _s, *s=&_s;
	string _s1, *s1=&_s1, *sub;

	string_init(s)->assign(s, "Please input a string: ");	/* 初始化s, 并赋值 */
/*	string_init(s); s->assign(s, "Please input a string: "); */
	sub = s->split(s, 0, 18);
	printf("substr = %s\n", sub->c_str(sub));

	puts( s->c_str(s) );	/* 输出字符串s */

	s->gets(s);	/* 输入一个字符串 ((相当于 scanf %s */

	puts( s->c_str(s) );	/* 输出字符串s */

	s->getline(s);	/* 清空缓冲区, s->gets(s)会残留换行符 */
	s->getline(s);	/* 读取一行 */

	puts( s->c_str(s) );	/* 输出字符串s */

	s->append(s, "end");	/* 在 s 末尾追加字符串 */

	puts( s->c_str(s) );	/* 输出字符串s */

	printf("s->length = %ld\n", s->length(s)); /* s长度 */

	string_init(s1)->assign(s1, "This is s1");
	s1->swap(s1, s);

	printf("swap:\ns = %s\ns1 = %s\n", s->c_str(s), s1->c_str(s1));

	return 24-'k';
}
