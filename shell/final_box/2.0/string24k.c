#include "string24k.h"

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

#include <ctype.h>

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

void
string_destroy (string *s)
{
	free(s->_data);
	s->_data = NULL;
	s->_size = 0;
	s->_capacity = 0;
}

char
string_at (const string *s, size_t pos)
{
	if ( pos<0 || pos>=s->_size ) {
		_24k_error(__FILE__, __func__, __LINE__, "Index out of bound, index=%d, size=%d\n", pos, s->_size);
		return 0;
	}
	return *( s->_data + pos );
}

char
string_front (const string *s)
{
	if ( ! s->_size )
		_24k_error(__FILE__, __func__, __LINE__, "read data from a string which is empty\n", 0);
	return *s->_data;
}

char
string_back (const string *s)
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
string_c_str (const string *s)
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
string_empty (const string *s)
{
	if ( s->_size )
 		return 0;
	return 1;
}

size_t
string_size (const string *s)
{
	return s->_size;
}

string*
string_reserve (string *s, size_t new_cap)
{
	char *p;
	if (new_cap > s->_capacity) {
		p = (char*) realloc (s->_data, (new_cap + 1) * sizeof(char));
		if ( ! p )
			return NULL;
		s->_data = p;
		s->_capacity = new_cap;
	}
	return s;
}

size_t
string_capacity (const string *s)
{
	return s->_capacity;
}

string*
string_shrink_to_fit (string *s)
{
	if (s->_size < s->_capacity) {
		s->_data = realloc(s->_data, (s->_size + 1) * sizeof(char));
		s->_capacity = s->_size;
	}
	return s;
}

string*
string_clear (string *s)
{
	s->_size = 0;
	string_data(s)[0] = 0;
	return s;
}

string*
string_resize (string *s, size_t count)
{
	if (s->_size >= count) {
		s->_size = count;
		*(s->_data + count) = 0;
	} else {
		if ( string_reserve(s, count) ) {
			memset(s->_data + s->_size, 0, (count - s->_size) * sizeof(char));
			s->_size = count;
		} else
			return NULL;
	}
	return s;
}

string*
string_insert (string *s, size_t pos, char t)
{
	char *p, *p1;
	if ( pos<0 || pos>s->_size ) {
		string_fatal_error(__FILE__, __func__, __LINE__, "Index out of bound, index=%d, size=%d\n", pos, s->_size);
		return NULL;
	}
	if ( s->_size == s->_capacity && ! string_reserve(s, s->_capacity * 2.0) )
		return NULL;
	p = s->_data + pos;
	p1 = s->_data + s->_size;
	while ( p1 > p )
		*p1 = *(p1-1), --p1;
	*p = t;
	++s->_size;
	*( string_data(s) + string_size(s) ) = 0;
	return s;
}

string*
string_erase (string *s, size_t pos)
{
	char *p, *p1;
	if (pos<0 || pos>=s->_size) {
		string_fatal_error(__FILE__, __func__, __LINE__, "Index out of bound, index=%d, size=%d\n", pos, s->_size);
		return NULL;
	}
	p = s->_data + pos;
	p1 = s->_data + s->_size;
	while ( p < p1 )
		*p = *(p+1), ++p;
	*( string_data(s) + --s->_size ) = 0;
	return s;
}

string*
string_push_back (string *s, char t)
{
	return string_insert(s, s->size(s), t);
}

string*
string_pop_back (string *s)
{
	return string_erase(s, s->size(s)-1);
}

string*
string_assign (string *s, const char *cs)
{
	int c;
	size_t i;
	string_clear(s);
	for (i=0; ; ++i) {
		c = cs[i];
		if ( ! c )
			return s;
		if ( ! string_push_back(s, c) )
			return NULL;
	}
}

string*
string_write (string *s, FILE *fp)
{
	fwrite(&s->_size, sizeof(size_t), 1, fp);
	fwrite(string_data(s), sizeof(char), string_size(s), fp);
	return s;
}

string*
string_read (string *s, FILE *fp)
{
	size_t size;
	string_init(s);
	fread(&size, sizeof(size_t), 1, fp);
	string_reserve(s, size);
	fread(string_data(s), sizeof(char), size, fp);
	s->_size = size;
	return s;
}

string*
string_save (string *s, const char *fname)
{
	FILE *fp;
	fp = fopen(fname, "w");
	if ( ! fp )
		return NULL;
	string_write(s, fp);
	fclose(fp);
	return s;
}

string*
string_load (string *s, const char *fname)
{
	FILE *fp;
	fp = fopen(fname, "r");
	if ( ! fp )
		return NULL;
	string_read(s, fp);
	fclose(fp);
	return s;
}

string*
string_add (string *s, const string *s1)
{
	if ( ! s->reserve(s, s->size(s) + s1->size(s1)) )
		return NULL;
	strncpy(s->data(s)+s->size(s), s1->c_str(s1), s1->size(s1));
	s->_size += s1->size(s1);
	*( s->data(s) + s->size(s) ) = 0;
	return s;
}

string*
string_append (string *s, const char *cs)
{
	string s1;

	string_init(&s1);
	s1.assign(&s1, cs);
	return s->add(s, &s1);
}

int
string_compare (const string *s, const string *s1)
{
	return strcmp(s->c_str(s), s1->c_str(s1));
}

string*
string_replace (string *s, size_t pos, size_t count, const char *cs)
{
	char *p, *p1, *p2;
	size_t len = strlen(cs);

	if ( ! s->reserve( s, s->size(s) + len - count) )
		return NULL;
	if (len < count) {
		p = s->data(s) + s->size(s);
		p1 = s->data(s) + pos + len;
		p2 = s->data(s) + pos + count;
		while (p2 < p)
			*p1 = *p2, ++p1, ++p2;
	} else if (len > count) {
		p = s->data(s) + pos + count;
		p1 = s->data(s) + s->size(s) - 1;
		p2 = s->data(s) + s->size(s) - 1 + len - count;
		while (p1 >= p)
			*p2 = *p1, --p1, --p2;
	}
	strncpy(s->data(s) + pos, cs, len);
	s->_size += len - count;
	*( s->data(s) + s->size(s) ) = 0;
	return s;
}

int
string_find (const string *s, size_t pos, const char *cs)
{
	char *p;
	p = strstr(s->c_str(s) + pos, cs);
	if ( ! p )
		return -1;
	return p - s->c_str(s);
}

int
string_find_first_of (const string *s, size_t pos, const char *cs)
{
	char *p;
	p = strpbrk(s->c_str(s) + pos, cs);
	if ( ! p )
		return -1;
	return p - s->c_str(s);
}

int
string_find_first_not_of (const string *s, size_t pos, const char *cs)
{
	size_t n;
	n = strspn(s->c_str(s) + pos, cs);
	if ( pos + n == s->size(s) )
		return -1;
	return pos + n;
}

string*
string_reverse(string *s)
{
	int c;
	string_iterator it, it1;

	it = s->begin(s);
	it1 = s->rbegin(s);

	while (it < it1) {
		c = *it;
		*it = *it1;
		*it1 = c;
		it = s->next(s, it);
		it1 = s->prev(s, it1);
	}
	return s;
}

int
string_find_last_of (const string *s, size_t pos, const char *cs)
{
	char *p;
	string _s1, *s1=&_s1;
	string_init(s1) -> assign(s1, s->c_str(s)) -> reverse(s1);

	pos = s1->size(s1) - pos - 1;
	p = strpbrk(s1->c_str(s1) + pos, cs);
	pos = s1->size(s1) - (p - s1->c_str(s1)) - 1;
	s1->destroy(s1);
	if ( ! p )
		return -1;
	return pos;
}

int
string_find_last_not_of (const string *s, size_t pos, const char *cs)
{
	size_t n;
	string _s1, *s1=&_s1;
	string_init(s1) -> assign(s1, s->c_str(s)) -> reverse(s1);

	pos = s1->size(s1) - pos - 1;
	n = strspn(s1->c_str(s1) + pos, cs);
	pos += n;
	pos = s1->size(s1) - pos - 1;
	s1->destroy(s1);
	if ( pos == s1->size(s1) )
		return -1;
	return pos;
}

string*
string_fgetline(string *s, FILE *fp, int delim)
{
	int c;
	s->clear(s);
	for (;;) {
		c = fgetc(fp);
		if (c == EOF || c == delim)
			break;
		s->push_back(s, c);
	}
	return s;
}

string*
string_getline(string *s)
{
	return string_fgetline(s, stdin, '\n');
}

string*
string_fgets(string *s, FILE *fp)
{
	int c;
	s->clear(s);
	for (;;) {
		c = fgetc(fp);
		if ( ! isspace(c) )
			break;
	}
	if (c == EOF)
		return s;
	ungetc(c, stdin);
	for (;;) {
		c = fgetc(fp);
		if (c == EOF)
			break;
		if ( isspace(c) ) {
			ungetc(c, stdin);
			break;
		}
		s->push_back(s, c);
	}
	return s;
}

string*
string_gets(string *s)
{
	return string_fgets(s, stdin);
}

string*
string_swap(string *s1, string *s2)
{
	char *p;
	size_t i;

	p = s1->_data;
	s1->_data = s2->_data;
	s2->_data = p;

	i = s1->_size;
	s1->_size = s2 ->_size;
	s2->_size = i;

	i = s1->_capacity;
	s1->_capacity = s2 ->_capacity;
	s2->_capacity = i;
	return s1;
}

string*
string_init (string *s)
{
	s->_data = (char*) malloc ((0x4 + 1) * sizeof(char));
	if ( ! s->_data )
		return NULL;
	*s->_data = 0;
	s->_size = 0;
	s->_capacity = 0x4;

#define _24k(f)		s->f = string##_##f

	s->length = string_size;

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
	_24k(add);
	_24k(append);
	_24k(compare);
	_24k(replace);
	_24k(find);
	_24k(find_first_of);
	_24k(find_first_not_of);
	_24k(reverse);
	_24k(find_last_of);
	_24k(find_last_not_of);
	_24k(fgetline);
	_24k(getline);
	_24k(fgets);
	_24k(gets);
	_24k(swap);

#undef _24k

	return s;
}

#undef _24k_error
#undef _24k_error__

