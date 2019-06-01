#ifndef _24K_STRING
#define _24K_STRING

#ifndef _STDIO_H
#include <stdio.h>
#endif

typedef char* string_iterator;

typedef struct string{
	char *_data;
	size_t _size;
	size_t _capacity;

	char (*at)(const struct string*, size_t);
	char (*front)(const struct string*);
	char (*back)(const struct string*);
	char* (*data)(struct string*);
	const char* (*c_str)(const struct string*);

	string_iterator (*begin)(struct string*);
	string_iterator (*end)(struct string*);
	string_iterator (*rbegin)(struct string*);
	string_iterator (*rend)(struct string*);
	string_iterator (*prev)(struct string*, string_iterator);
	string_iterator (*next)(struct string*, string_iterator);

	int (*empty)(const struct string*);
	size_t (*size)(const struct string*);
	size_t (*length)(const struct string*);
	struct string* (*reserve)(struct string*, size_t);
	size_t (*capacity)(const struct string*);
	struct string* (*shrink_to_fit)(struct string*);
	struct string* (*clear)(struct string*);
	struct string* (*resize)(struct string*, size_t);

	struct string* (*insert)(struct string*, size_t, char);
	struct string* (*erase)(struct string*, size_t);
	struct string* (*push_back)(struct string*, char);
	struct string* (*pop_back)(struct string*);
	struct string* (*assign)(struct string*, const char*);

	struct string* (*write)(struct string*, FILE*);
	struct string* (*read)(struct string*, FILE*);
	struct string* (*save)(struct string*, const char*);
	struct string* (*load)(struct string*, const char*);

	void (*destroy)(struct string*);

	struct string* (*add)(struct string*, const struct string*);
	struct string* (*append)(struct string*, const char*);
	int (*compare)(const struct string*, const struct string*);
	struct string* (*replace)(struct string*, size_t, size_t, const char*);

	int (*find)(const struct string*, size_t, const char*);
	int (*find_first_of)(const struct string*, size_t, const char*);
	int (*find_first_not_of)(const struct string*, size_t, const char*);
	struct string* (*reverse)(struct string*);
	int (*find_last_of)(const struct string*, size_t, const char*);
	int (*find_last_not_of)(const struct string*, size_t, const char*);

	struct string* (*fgetline)(struct string*, FILE*, int);
	struct string* (*getline)(struct string*);
	struct string* (*fgets)(struct string*, FILE*);
	struct string* (*gets)(struct string*);

	struct string* (*swap)(struct string*, struct string*);

}string;

string* string_init (string *s);

// s->function(s, ...);

char string_at(const string *s, size_t pos);
	// 返回 s 的第pos个字符,  pos>=0

char string_front(const string *s);
	// 返回 s 的第一个字符

char string_back(const string *s);
	// 返回 s 的最后一个字符

char* string_data(string *s);
	// 返回 s 的字符串地址

const char* string_c_str(const string *s);
	// 返回 s 的字符串地址, 不可修改, 建议在输出时使用

int string_empty(const string *s);
	// 判断 s 是否为空字符串

size_t string_size(const string *s);
size_t string_length(const string *s);
	// 返回 s 的长度, 2个函数一样

string* string_reserve(string *s, size_t new_cap);
	// 确保 s 有new_cap个字符的空间, 避免string增长时多次realloc

size_t string_capacity(const string *s);
	// 返回 s 的内存大小

string* string_shrink_to_fit(string *s);
	// 使 s 的内存大小适应它的长度, 释放多余的内存

string* string_clear(string *s);
	// 清空字符串内容, s长度变为0

string* string_resize(string *s, size_t count);
	// 强行调整s的长度

string* string_insert(string *s, size_t pos, char c);
	// 在pos位置插入字符c

string* string_erase(string *s, size_t pos);
	// 删除pos位置的字符

string* string_push_back(string *s, char c);
	// 在s的末尾追加字符c

string* string_pop_back(string *s);
	// 删除s的最后一个字符

string* string_assign(string *s, const char *cs);
	// 清空字符串s内容, 把字符串cs赋值给s

string* string_add(string *s, const string *s1);
	// 把string s1追加到s末尾

string* string_append(string *s, const char *cs);
	// 把字符串cs追加到s末尾

int string_compare(const string *s, const string *s1);
	// 比较s, s1大小  返回 s - s1

string* string_replace(string *s, size_t pos, size_t count, const char *cs);
	// 把s的pos位置开始的count个字符替换为cs字符串

int string_find(const string *s, size_t pos, const char *cs);
	// 从s的pos位置开始查找cs字符串

int string_find_first_of(const string *s, size_t pos, const char *cs);
	// 从s的pos位置开始查找 包含在 cs字符串 中的字符, 返回其下标, 没找到返回-1

int string_find_first_not_of(const string *s, size_t pos, const char *cs);
	// 从s的pos位置开始查找 不在 cs字符串 中的字符, 返回其下标, 没找到返回-1

int string_find_last_of(const string *s, size_t pos, const char *cs);
	// 从s的pos位置开始[向前]查找 包含在 cs字符串 中的字符, 返回其下标, 没找到返回-1

int string_find_last_not_of(const string *s, size_t pos, const char *cs);
	// 从s的pos位置开始[向前]查找 不在 cs字符串 中的字符, 返回其下标, 没找到返回-1

string* string_reverse(string *s);
	// 将字符串内容倒置

string* string_fgetline(string *s, FILE *fp, int delim);
	// 从文件fp读取字符到s, 自动扩展s内存, 直到遇到字符delim, 读取并抛弃字符delim

string* string_getline(string *s);
	// 读取一行, 相当于 fgetline(s, stdin, '\n');

string* string_fgets(string *s, FILE *fp);
	// 从文件读取字符串 相当于 fscanf fp,%s  忽略前后空白字符

string* string_gets(string *s);
	// 相当于 fgets(s, stdin);

string* string_string_init(string *s);
	// 初始化string s

void string_destroy(string *s);
	// 释放s申请的内存, s将被置于 未初始化 状态

string* string_swap(string *s1, string *s2);
	// 交换字符串s1与s2的内容

#endif
