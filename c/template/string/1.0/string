#ifndef _24K_STRING
#define _24K_STRING

#if defined _MSC_VER && ! defined __func__
#define __func__ __FUNCTION__
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

void
string_fatal_error (const char *file, const char *func, size_t line, const char *fmt, ...) {
 va_list ap;
 va_start(ap,fmt);
 fprintf(stderr, "_24k::error> in file `%s`, in function `%s` line %ld: \n\t(*/ω＼*): ", file, func, line);
 vfprintf(stderr, fmt, ap);
 va_end(ap);
 exit(24);
}
typedef struct{
 char *data;
 size_t size;
 size_t capacity;
}string;
typedef char* string_iterator;
int
string_init (string *vec)
{
 vec->data = (char*) malloc ((0x4 + 1) * sizeof(char));
 if ( ! vec->data )
  return 0;
 vec->size = 0;
 vec->capacity = 0x4;
 return 1;
}
void
string_destroy (string *vec)
{
 free(vec->data);
 vec->data = ((void *)0);
 vec->size = 0;
 vec->capacity = 0;
}
char*
string_at (string *vec, size_t pos)
{
 if ( pos<0 || pos>=vec->size ) {
  string_fatal_error(__FILE__, __func__, __LINE__, "Index out of bound, index=%d, size=%d\n", pos, vec->size);
  return 0;
 }
 return vec->data + pos;
}
char
string_front (string *vec)
{
 if ( ! vec->size )
  string_fatal_error(__FILE__, __func__, __LINE__, "read data from a vector which is empty\n", 0);
 return *vec->data;
}
char
string_back (string *vec)
{
 if ( ! vec->size )
  string_fatal_error(__FILE__, __func__, __LINE__, "read data from a vector which is empty\n", 0);
 return *(vec->data + vec->size - 1);
}
char*
string_data (string *vec)
{
 return vec->data;
}
char*
string_c_str (string *vec)
{
 return vec->data;
}
string_iterator
string_first (string *vec)
{
 return vec->data;
}
string_iterator
string_last (string *vec)
{
 return vec->data + vec->size - 1;
}
string_iterator
string_head (string *vec)
{
 return vec->data - 1;
}
string_iterator
string_tail (string *vec)
{
 return vec->data + vec->size;
}
string_iterator
string_prev (string_iterator it)
{
 return --it;
}
string_iterator
string_next (string_iterator it)
{
 return ++it;
}
int
string_empty (string *vec)
{
 if ( vec->size )
  return 0;
 return 1;
}
size_t
string_size (string *vec)
{
 return vec->size;
}
int
string_reserve (string *vec, size_t new_cap)
{
 char *p;
 if (new_cap > vec->capacity) {
  p = (char*) realloc (vec->data, (new_cap + 1) * sizeof(char));
  if ( ! p )
   return 0;
  vec->data = p;
  vec->capacity = new_cap;
 }
 return 1;
}
size_t
string_capacity (string *vec)
{
 return vec->capacity;
}
void
string_shrink_to_fit (string *vec)
{
 if (vec->size < vec->capacity) {
  vec->data = realloc(vec->data, (vec->size + 1) * sizeof(char));
  vec->capacity = vec->size;
 }
}
void
string_clear (string *vec)
{
 vec->size = 0;
 string_data(vec)[0] = 0;
}
int
string_resize (string *vec, size_t count)
{
 int r;
 if (vec->size >= count)
  vec->size = count;
 else {
  r = string_reserve(vec, count);
  if ( r )
   memset(vec + vec->size, 0, (count - vec->size) * sizeof(char));
  else
   return 0;
 }
 return 1;
}
int
string_insert (string *vec, string_iterator it, char t)
{
 size_t pos = it - string_data(vec);
 char *p;
 if ( pos<0 || pos>vec->size ) {
  string_fatal_error(__FILE__, __func__, __LINE__, "Index out of bound, index=%d, size=%d\n", pos, vec->size);
  return 0;
 }
 if ( vec->size == vec->capacity && ! string_reserve(vec, vec->capacity * 2.0) )
  return 0;
 p = vec->data + pos;
 memmove( p+1, p, sizeof(char) * (vec->size - pos) );
 *p = t;
 ++vec->size;
 *( string_data(vec) + string_size(vec) ) = 0;
 return 1;
}
int
string_erase (string *vec, string_iterator it)
{
 size_t pos = it - string_data(vec);
 char *p;
 if (pos<0 || pos>=vec->size) {
  string_fatal_error(__FILE__, __func__, __LINE__, "Index out of bound, index=%d, size=%d\n", pos, vec->size);
  return 0;
 }
 p = vec->data + pos;
 memmove( p, p+1, sizeof(char) * (--vec->size - pos) );
 *( string_data(vec) + string_size(vec) ) = 0;
 return 1;
}
int
string_push_back (string *vec, char t)
{
 return string_insert(vec, string_tail(vec), t);
}
int
string_pop_back (string *vec)
{
 return string_erase(vec, string_last(vec));
}
int
string_assign (string *vec, const char *s)
{
 int c;
 size_t i;
 string_clear(vec);
 for (i=0; ; ++i) {
  c = s[i];
  if ( ! c )
   return 1;
  if ( ! string_push_back(vec, c) )
   return 0;
 }
}
void
string_write (string *vec, FILE *fp)
{
 fwrite(&vec->size, sizeof(size_t), 1, fp);
 fwrite(string_data(vec), sizeof(char), string_size(vec), fp);
}
void
string_read (string *vec, FILE *fp)
{
 size_t size;
 string_init(vec);
 fread(&size, sizeof(size_t), 1, fp);
 string_reserve(vec, size);
 fread(string_data(vec), sizeof(char), size, fp);
 vec->size = size;
}
int
string_save (string *vec, const char *fname)
{
 FILE *fp;
 fp = fopen(fname, "w");
 if ( ! fp )
  return 0;
 string_write(vec, fp);
 fclose(fp);
 return 1;
}
int
string_load (string *vec, const char *fname)
{
 FILE *fp;
 fp = fopen(fname, "r");
 if ( ! fp )
  return 0;
 string_read(vec, fp);
 fclose(fp);
 return 1;
}

#endif // _24K_STRING
