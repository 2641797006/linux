
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

string* insert(string *s, size_t pos, char c);
	// 在pos位置插入字符c

string* erase(string *s, size_t pos);
	// 删除pos位置的字符

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

int find_first_of(const string *s, size_t pos, const char *cs);
	// 从s的pos位置开始查找 包含在 cs字符串 中的字符, 返回其下标, 没找到返回-1

int find_first_not_of(const string *s, size_t pos, const char *cs);
	// 从s的pos位置开始查找 不在 cs字符串 中的字符, 返回其下标, 没找到返回-1

int find_last_of(const string *s, size_t pos, const char *cs);
	// 从s的pos位置开始[向前]查找 包含在 cs字符串 中的字符, 返回其下标, 没找到返回-1

int find_last_not_of(const string *s, size_t pos, const char *cs);
	// 从s的pos位置开始[向前]查找 不在 cs字符串 中的字符, 返回其下标, 没找到返回-1

string* reverse(string *s);
	// 将字符串内容倒置

string* fgetline(string *s, FILE *fp, int delim);
	// 从文件fp读取字符到s, 自动扩展s内存, 直到遇到字符delim, 读取并抛弃字符delim

string* getline(string *s);
	// 读取一行, 相当于 fgetline(s, stdin, '\n');

string* fgets(string *s, FILE *fp);
	// 从文件读取字符串 相当于 fscanf fp,%s  忽略前后空白字符

string* gets(string *s);
	// 相当于 fgets(s, stdin);

string* string_init(string *s);
	// 初始化string s

void destroy(string *s);
	// 释放s申请的内存, s将被置于 未初始化 状态
