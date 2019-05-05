#ifndef _24k_list_t
# error: No define "_24k_list_t"
#else

#if defined _MSC_VER && ! defined __func__
#define __func__ __FUNCTION__
#endif

/*
 * T = _24k_list_t
 * T_list // list type
 * T_list_iterator // 迭代器类型
 * 
 * bool T_list_init (T_list *list) // 初始化list
 * void T_list_destroy (T_list *list) // 销毁list
 *
 * bool T_list_assign (T_list *list, size_t count, const T *t) // 清空list 并且 插入count个t
 * T T_list_front (T_list *list) // 返回list中首个元素
 * T T_list_back (T_list *list) // 返回list中最后一个元素
 *
 * T_list_iterator T_list_first (T_list *list) // 返回指向首个元素的迭代器
 * T_list_iterator T_list_last (T_list *list) // 返回指向最后一个元素的迭代器
 * T_list_iterator T_list_head (T_list *list) // 首个元素前一个位置
 * T_list_iterator T_list_tail (T_list *list) // 最后一个元素后一个位置
 * T_list_iterator T_list_prev (T_list_iterator it) // 返回前一个迭代器
 * T_list_iterator T_list_next (T_list_iterator it) // 返回后一个迭代器
 *
 * bool T_list_empty (T_list *list) // 判断list是否为空
 * size_t T_list_size (T_list *list) // 返回list中元素个数
 * void T_list_clear (T_list *list) // 清空list中所有元素
 * bool T_list_insert (T_list *list, T_list_iterator it, const T *t) // 把元素t插入到迭代器it前面
 * bool T_list_erase (T_list *list, T_list_iterator it) // 删除迭代器it指向的元素
 *
 * bool T_list_push_back (T_list *list, const T *t) // 向list末尾插入元素t
 * bool T_list_push_front (T_list *list, const T *t) // 向list首部插入元素t
 * bool T_list_pop_back (T_list *list) // 删除list末尾的一个元素
 * bool T_list_pop_front (T_list *list) // 删除list首部的一个元素
 *
 */

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

#define _24k_list_lk__(T)	T##_##list
#define _24k_list_lk(T)	_24k_list_lk__(T)
#define _24k_list	_24k_list_lk(_24k_list_t)

#define _24k__(x, T)	T##_##list##_##x
#define _24k_(x, T)	_24k__(x, T)
#define _24k(x)		_24k_(x, _24k_list_t)

#define _24k_error__(fmt, ...)	_24k(fatal_error)(__FILE__, __func__, __LINE__, fmt, __VA_ARGS__)
#define _24k_error(fmt, ...)	_24k_error__(fmt, __VA_ARGS__)

#define _24k_sptr(s, m, mptr)	( (s*) ( (char*)mptr - (char*)&(((s*)0)->m) ) )

void
_24k(fatal_error) (const char *file, const char *func, size_t line, const char *fmt, ...) {
#ifndef _24K_NOT_PRINT_ERR_MSG
	va_list ap;
	va_start(ap, fmt);
	fprintf(stderr, "_24k::error> in file `%s`, in function `%s` line %ld: \n\t(*/ω＼*): ", file, func, line);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
#endif
#ifndef _24K_NOT_EXIT
	exit(24);
#endif
}

typedef struct _24k(node){
	_24k_list_t data;
	struct _24k(node) *prev;
	struct _24k(node) *next;
}_24k(node);

typedef struct{
	_24k(node) *head;
	_24k(node) *tail;
	size_t size;
}_24k_list;

typedef _24k_list_t* _24k(iterator);

int
_24k(init) (_24k_list *list)
{
	list->head = (_24k(node)*) malloc ( sizeof(_24k(node)) );
	if ( ! list->head )
		return 0;
	list->tail = (_24k(node)*) malloc ( sizeof(_24k(node)) );
	if ( ! list->tail ) {
		free ( list->head );
		return 0;
	}
	list->head->prev = NULL;
	list->head->next = list->tail;
	list->tail->prev = list->head;
	list->tail->next = NULL;
	list->size = 0;
	return 1;
}

void
_24k(destroy) (_24k_list *list)
{
	_24k(node) *p = list->head;

	while (p) {
		list->head = list->head->next;
		free(p);
		p = list->head;
	}
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
}

_24k_list_t
_24k(front) (_24k_list *list)
{
	if ( ! list->size )
		_24k_error("read data from an empty list\n", 0);
	return list->head->next->data;
}

_24k_list_t
_24k(back) (_24k_list *list)
{
	if ( ! list->size )
		_24k_error("read data from an empty list\n", 0);
	return list->tail->prev->data;
}

_24k(iterator)
_24k(first) (_24k_list *list)
{
	return &list->head->next->data;
}

_24k(iterator)
_24k(last) (_24k_list *list)
{
	return &list->tail->prev->data;
}

_24k(iterator)
_24k(head) (_24k_list *list)
{
	return &list->head->data;
}

_24k(iterator)
_24k(tail) (_24k_list *list)
{
	return &list->tail->data;
}

_24k(iterator)
_24k(prev) (_24k(iterator) it)
{
	_24k(node) *p = _24k_sptr( _24k(node), data, it );
	if ( ! p->prev ) {
		_24k_error("iterator out of bound\n", 0);
		return NULL;
	}
	return &p->prev->data;
}

_24k(iterator)
_24k(next) (_24k(iterator) it)
{
	_24k(node) *p = _24k_sptr( _24k(node), data, it );
	if ( ! p->next ) {
		_24k_error("iterator out of bound\n", 0);
		return NULL;
	}
	return &p->next->data;
}

int
_24k(empty) (_24k_list *list)
{
	if ( list->size )
		return 0;
	return 1;
}

size_t
_24k(size) (_24k_list *list)
{
	return list->size;
}

void
_24k(clear) (_24k_list *list)
{
	_24k(destroy)(list);
	_24k(init)(list);
}

int
_24k(insert) (_24k_list *list, _24k(iterator) it, const _24k_list_t *t)
{
	_24k(node) *p = _24k_sptr( _24k(node), data, it );
	if ( p == list->head ) {
		_24k_error("insert pos error\n", 0);
		return 0;
	}
	_24k(node) *p1 = (_24k(node)*) malloc ( sizeof(_24k(node)) );
	if ( ! p1 )
		return 0;
	memcpy(&p1->data, t, sizeof(_24k_list_t));
	p1->next = p;
	p1->prev = p->prev;
	p->prev = p1;
	p1->prev->next = p1;
	++list->size;
	return 1;
}

int
_24k(erase) (_24k_list *list, _24k(iterator) it)
{
	_24k(node) *p = _24k_sptr( _24k(node), data, it );
	if ( p == list->head || p == list->tail ) {
		_24k_error("erase pos error\n", 0);
		return 0;
	}
	p->next->prev = p->prev;
	p->prev->next = p->next;
	free(p);
	--list->size;
	return 1;
}


int
_24k(push_back) (_24k_list *list, const _24k_list_t *t)
{
	return _24k(insert)(list, _24k(tail)(list), t);
}

int
_24k(push_front) (_24k_list *list, const _24k_list_t *t)
{
	return _24k(insert)(list, _24k(first)(list), t);
}

int
_24k(pop_back) (_24k_list *list)
{
	return _24k(erase)(list, _24k(last)(list));
}

int
_24k(pop_front) (_24k_list *list)
{
	return _24k(erase)(list, _24k(first)(list));
}

int
_24k(assign) (_24k_list *list, size_t count, const _24k_list_t *t)
{
	size_t i;

	_24k(clear)(list);
	for (i=0; i<count; ++i)
		if ( ! _24k(push_back)(list, t) )
			return 0;
	return 1;
}

void
_24k(write) (_24k_list *list, FILE *fp)
{
	_24k(iterator) it = _24k(first)(list);

	fwrite(&list->size, sizeof(size_t), 1, fp);
	while (it != _24k(tail)(list)) {
		fwrite(it, sizeof(_24k_list_t), 1, fp);
		it = _24k(next)(it);
	}
}

void
_24k(read) (_24k_list *list, FILE *fp)
{
	size_t i, size;
	_24k_list_t t;

	_24k(init)(list);
	fread(&size, sizeof(size_t), 1, fp);
	for (i=0; i<size; ++i) {
		fread(&t, sizeof(_24k_list_t), 1, fp);
		_24k(push_back)(list, &t);
	}
}

int
_24k(save) (_24k_list *list, const char *fname)
{
	FILE *fp;
	fp = fopen(fname, "w");
	if ( ! fp )
		return 0;
	_24k(write)(list, fp);
	fclose(fp);
	return 1;
}

int
_24k(load) (_24k_list *list, const char *fname)
{
	FILE *fp;
	fp = fopen(fname, "r");
	if ( ! fp )
		return 0;
	_24k(read)(list, fp);
	fclose(fp);
	return 1;
}

#undef _24k_list_lk__
#undef _24k_list_lk
#undef _24k_list

#undef _24k__
#undef _24k_
#undef _24k

#undef _24k_error__
#undef _24k_error

#undef _24k_list_t
#undef _24k_sptr

#endif
