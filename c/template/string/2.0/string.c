#ifndef _24K_STRING
#define _24K_STRING

#if defined _MSC_VER

#ifndef __func__
#define __func__ __FUNCTION__
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#endif

#ifndef _STDLIB_H // malloc(), exit()
#include <stdlib.h>
#ifndef _STDLIB_H
#define _STDLIB_H
#endif
#endif

#ifndef _STRING_H // memcpy()
#include <string.h>
#ifndef _STRING_H
#define _STRING_H
#endif
#endif

#ifndef _STDARG_H // va_list
#include <stdarg.h>
#ifndef _STDARG_H
#define _STDARG_H
#endif
#endif

#define _24k_error__(fmt, ...)	string_fatal_error(__FILE__, __func__, __LINE__, fmt, __VA_ARGS__)
#define _24k_error(fmt, ...)	_24k_error__(fmt, __VA_ARGS__)

void
string_fatal_error (const char *file, const char *func, size_t line, const char *fmt, ...) {
#ifndef _24K_NOT_PRINT_ERR_MSG
	va_list ap;
	va_start(ap,fmt);
	fprintf(stderr, "_24k::error> in file `%s`, in function `%s` line %ld: \n\t(*/ω＼*): ", file, func, line);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
#endif
#ifndef _24K_NOT_EXIT
	exit(24);
#endif
}

typedef char* string_iterator;

typedef struct string{
	char *_data;
	size_t _size;
	size_t _capacity;

	char* (*at)(struct string*, size_t);
	char (*front)(struct string*);
	char (*back)(struct string*);
	char* (*data)(struct string*);
	const char* (*c_str)(struct string*);

	string_iterator (*begin)(struct string*);
	string_iterator (*end)(struct string*);
	string_iterator (*rbegin)(struct string*);
	string_iterator (*rend)(struct string*);
	string_iterator (*prev)(struct string*, string_iterator);
	string_iterator (*next)(struct string*, string_iterator);

	int (*empty)(struct string*);
	size_t (*size)(struct string*);
	size_t (*length)(struct string*);
	int (*reserve)(struct string*, size_t);
	size_t (*capacity)(struct string*);
	void (*shrink_to_fit)(struct string*);
	void (*clear)(struct string*);
	int (*resize)(struct string*, size_t);

	int (*insert)(struct string*, string_iterator, char);
	int (*erase)(struct string*, string_iterator);
	int (*push_back)(struct string*, char);
	int (*pop_back)(struct string*);
	int (*assign)(struct string*, const char*);

	void (*write)(struct string*, FILE*);
	void (*read)(struct string*, FILE*);
	int (*save)(struct string*, const char*);
	int (*load)(struct string*, const char*);

	void (*destroy)(struct string*);

}string;

int string_init (string *s);

void
string_destroy (string *s)
{
	free(s->_data);
	s->_data = NULL;
	s->_size = 0;
	s->_capacity = 0;
}

char*
string_at (string *s, size_t pos)
{
	if ( pos<0 || pos>=s->_size ) {
		_24k_error(__FILE__, __func__, __LINE__, "Index out of bound, index=%d, size=%d\n", pos, s->_size);
		return NULL;
	}
	return s->_data + pos;
}

char
string_front (string *s)
{
	if ( ! s->_size )
		_24k_error(__FILE__, __func__, __LINE__, "read data from a string which is empty\n", 0);
	return *s->_data;
}

char
string_back (string *s)
{
	if ( ! s->_size )
		_24k_error(__FILE__, __func__, __LINE__, "read data from a string which is empty\n", 0);
	return *(s->_data + s->_size - 1);
}

char*
string_data (string *s)
{
	return s->_data;
}

const char*
string_c_str (string *s)
{
	return s->_data;
}

string_iterator
string_begin (string *s)
{
	return s->_data;
}

string_iterator
string_end (string *s)
{
	return s->_data + s->_size;
}

string_iterator
string_rbegin (string *s)
{
	return s->_data + s->_size - 1;
}

string_iterator
string_rend (string *s)
{
	return s->_data - 1;
}

string_iterator
string_prev (string *s, string_iterator it)
{
	if (--it < string_rend(s))
		_24k_error("iterator out of bound\n", 0);
	return it;
}

string_iterator
string_next (string *s, string_iterator it)
{
	if (++it > string_end(s))
		_24k_error("iterator out of bound\n", 0);
	return it;
}

int
string_empty (string *s)
{
	if ( s->_size )
 		return 0;
	return 1;
}

size_t
string_size (string *s)
{
	return s->_size;
}

int
string_reserve (string *s, size_t new_cap)
{
	char *p;
	if (new_cap > s->_capacity) {
		p = (char*) realloc (s->_data, (new_cap + 1) * sizeof(char));
		if ( ! p )
			return 0;
		s->_data = p;
		s->_capacity = new_cap;
	}
	return 1;
}

size_t
string_capacity (string *s)
{
	return s->_capacity;
}

void
string_shrink_to_fit (string *s)
{
	if (s->_size < s->_capacity) {
		s->_data = realloc(s->_data, (s->_size + 1) * sizeof(char));
		s->_capacity = s->_size;
	}
}

void
string_clear (string *s)
{
	s->_size = 0;
	string_data(s)[0] = 0;
}

int
string_resize (string *s, size_t count)
{
	if (s->_size >= count) {
		s->_size = count;
		*(s->_data + count) = 0;
	} else {
		if ( ! string_reserve(s, count) )
			memset(s->_data + s->_size, 0, (count - s->_size) * sizeof(char));
		else
			return 0;
	}
	return 1;
}

int
string_insert (string *s, string_iterator it, char t)
{
	size_t pos = it - string_data(s);
	char *p, *p1;
	if ( pos<0 || pos>s->_size ) {
		string_fatal_error(__FILE__, __func__, __LINE__, "Index out of bound, index=%d, size=%d\n", pos, s->_size);
		return 0;
	}
	if ( s->_size == s->_capacity && ! string_reserve(s, s->_capacity * 2.0) )
		return 0;
	p = s->_data + pos;
	p1 = s->_data + s->_size;
	while ( p1 > p )
		*p1 = *(p1-1), --p1;
	*p = t;
	++s->_size;
	*( string_data(s) + string_size(s) ) = 0;
	return 1;
}

int
string_erase (string *s, string_iterator it)
{
	size_t pos = it - string_data(s);
	char *p, *p1;
	if (pos<0 || pos>=s->_size) {
		string_fatal_error(__FILE__, __func__, __LINE__, "Index out of bound, index=%d, size=%d\n", pos, s->_size);
		return 0;
	}
	p = s->_data + pos;
	p1 = s->_data + s->_size;
	while ( p < p1 )
		*p = *(p+1), ++p;
	*( string_data(s) + --s->_size ) = 0;
	return 1;
}

int
string_push_back (string *s, char t)
{
	return string_insert(s, string_end(s), t);
}

int
string_pop_back (string *s)
{
	return string_erase(s, string_rbegin(s));
}

int
string_assign (string *s, const char *cs)
{
	int c;
	size_t i;
	string_clear(s);
	for (i=0; ; ++i) {
		c = cs[i];
		if ( ! c )
			return 1;
		if ( ! string_push_back(s, c) )
			return 0;
	}
}

void
string_write (string *s, FILE *fp)
{
	fwrite(&s->_size, sizeof(size_t), 1, fp);
	fwrite(string_data(s), sizeof(char), string_size(s), fp);
}

void
string_read (string *s, FILE *fp)
{
	size_t size;
	string_init(s);
	fread(&size, sizeof(size_t), 1, fp);
	string_reserve(s, size);
	fread(string_data(s), sizeof(char), size, fp);
	s->_size = size;
}

int
string_save (string *s, const char *fname)
{
	FILE *fp;
	fp = fopen(fname, "w");
	if ( ! fp )
		return 0;
	string_write(s, fp);
	fclose(fp);
	return 1;
}

int
string_load (string *s, const char *fname)
{
	FILE *fp;
	fp = fopen(fname, "r");
	if ( ! fp )
		return 0;
	string_read(s, fp);
	fclose(fp);
	return 1;
}

int
string_init (string *s)
{
	s->_data = (char*) malloc ((0x4 + 1) * sizeof(char));
	if ( ! s->_data )
		return 0;
	*s->_data = 0;
	s->_size = 0;
	s->_capacity = 0x4;

#define _24k(f)		s->f = string##_##f

	_24k(at);
	_24k(front);
	_24k(back);
	_24k(data);
	_24k(c_str);
	_24k(begin);
	_24k(end);
	_24k(rbegin);
	_24k(rend);
	_24k(prev);
	_24k(next);
	_24k(empty);
	_24k(size);
	_24k(reserve);
	_24k(capacity);
	_24k(shrink_to_fit);
	_24k(clear);
	_24k(resize);
	_24k(insert);
	_24k(erase);
	_24k(push_back);
	_24k(pop_back);
	_24k(assign);
	_24k(write);
	_24k(read);
	_24k(save);
	_24k(load);
	_24k(destroy);

#undef _24k

	return 1;
}

#endif
