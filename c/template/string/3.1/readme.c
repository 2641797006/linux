
// s->function(s, ...);

char at(string *s, size_t pos);
	// 返回 s 的第pos个字符,  pos>=0

char front(string *s);
	// 返回 s 的第一个字符

char back(string *s);
	// 返回 s 的最后一个字符

char* data(string *s);
	// 返回 s 的字符串地址

const char* c_str(string *s);
	// 返回 s 的字符串地址, 不可修改, 建议在输出时使用

bool empty(string *s);
	// 判断 s 是否为空字符串

size_t size(string *s);
size_t length(string *s);
	// 返回 s 的长度, 2个函数一样

string* reserve(string *s, size_t new_cap);
	// 确保 s 有new_cap个字符的空间, 避免string增长时多次realloc

size_t capacity(string *s);
	// 返回 s 的内存大小

string* shrink_to_fit(string *s);
	// 使 s 的内存大小适应它的长度, 释放多余的内存

string* clear(string *s);
	// 清空字符串内容, s长度变为0

string* resize(string *s, size_t count);
	// 强行调整s的长度

string* insert(string *s, string_iterator it, char c);
	// 在it位置插入字符c

string* erase(string *s, string_iterator it);
	// 删除it位置的字符

string* push_back(string *s, char c);
	// 在s的末尾追加字符c

string* pop_back(string *s);
	// 删除s的最后一个字符

string* assign(string *s, const char *cs);
	// 清空字符串s内容, 把字符串cs赋值给s

string* add(string *s, const string *s1);
	// 把string s1追加到s末尾

string* append(string *s, const char *cs);
	// 把字符串cs追加到s末尾

int compare(const string *s, const string *s1);
	// 比较s, s1大小  返回 s - s1

string* replace(string *s, size_t pos, size_t count, const char *cs);
	// 把s的pos位置开始的count个字符替换为cs字符串

int find(string *s, size_t pos, const char *cs);
	// 从s的pos位置开始查找cs字符串


