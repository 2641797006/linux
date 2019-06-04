#ifndef __list_t
# error: No define "__list_t"
#else

#if defined _MSC_VER

#ifndef __func__
#define __func__ __FUNCTION__
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#endif

/*
 * T = __list_t
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

#ifndef _STDLIB_H /* malloc(), exit() */
#include <stdlib.h>
#ifndef _STDLIB_H
#define _STDLIB_H
#endif
#endif

#ifndef _STRING_H /* memcpy() */
#include <string.h>
#ifndef _STRING_H
#define _STRING_H
#endif
#endif

#ifndef _STDARG_H /* va_list */
#include <stdarg.h>
#ifndef _STDARG_H
#define _STDARG_H
#endif
#endif

#define __list_lk__(T)	T##_##list
#define __list_lk(T)	__list_lk__(T)
#define __list	__list_lk(__list_t)

#define ___(x, T)	T##_##list##_##x
#define __(x, T)	___(x, T)
#define _(x)		__(x, __list_t)

#if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L \
	&& ! defined __TEMPLATE_ERROR
#define __TEMPLATE_ERROR
#endif

#ifdef __TEMPLATE_ERROR
#define __error__(fmt, ...)	_(fatal_error)(__FILE__, __func__, __LINE__, fmt, __VA_ARGS__)
#define __error(fmt, ...)	__error__(fmt, __VA_ARGS__)
#else
#define __error		while (0)
#endif

#define __sptr(s, m, mptr)	( (s*) ( (char*)mptr - (char*)&(((s*)0)->m) ) )

#ifdef __TEMPLATE_ERROR

void
_(fatal_error) (const char *file, const char *func, size_t line, const char *fmt, ...) {
#ifndef _24K_NOT_PRINT_ERR_MSG
	va_list ap;
	va_start(ap, fmt);
	fprintf(stderr, "_::error> in file `%s`, in function `%s` line %ld: \n\t(*/ω＼*): ", file, func, line);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
#endif
#ifndef _24K_NOT_EXIT
	exit(24);
#endif
}

#endif

typedef __list_t* _(iterator);

typedef struct _(node){
	__list_t data;
	struct _(node) *prev;
	struct _(node) *next;
}_(node);

typedef struct __list{
	_(node) *head;
	_(node) *tail;
	size_t _size;

	__list_t (*front)(struct __list*);
	__list_t (*back)(struct __list*);

	_(iterator) (*begin)(struct __list*);
	_(iterator) (*end)(struct __list*);
	_(iterator) (*rbegin)(struct __list*);
	_(iterator) (*rend)(struct __list*);
	_(iterator) (*prev)(struct __list*, _(iterator));
	_(iterator) (*next)(struct __list*, _(iterator));

	int (*empty)(struct __list*);
	size_t (*size)(struct __list*);
	void (*clear)(struct __list*);
	int (*assign)(struct __list*, size_t, const __list_t*);

	int (*insert)(struct __list*, _(iterator), const __list_t*);
	int (*erase)(struct __list*, _(iterator));
	int (*push_back)(struct __list*, const __list_t*);
	int (*push_front)(struct __list*, const __list_t*);
	int (*pop_front)(struct __list*);
	int (*pop_back)(struct __list*);

	void (*write)(struct __list*, FILE*);
	void (*read)(struct __list*, FILE*);
	int (*save)(struct __list*, const char*);
	int (*load)(struct __list*, const char*);

	int (*traverse)(struct __list*, int (*)(__list_t*));
	int (*rtraverse)(struct __list*, int (*)(__list_t*));
	struct __list* (*find_if)(struct __list*, int (*)(const __list_t*));
	int (*remove_if)(struct __list*, int (*)(const __list_t*));

	void (*destroy)(struct __list*);

	void (*set_copyer)( void (*) (__list_t*, const __list_t*) );
	void (*set_destructor)( void (*) (__list_t*) );

}__list;

static void (*_(copyer)) (__list_t*, const __list_t*) = NULL;
static void (*_(destructor)) (__list_t*) = NULL;

void
_(set_copyer) ( void (*copyer) (__list_t*, const __list_t*) )
{
	_(copyer) = copyer;
}

void
_(set_destructor) ( void (*destructor) (__list_t*) )
{
	_(destructor) = destructor;
}

int _(init) (__list*);

void
_(destroy) (__list *list)
{
	_(node) *p = list->head->next, *tmp = p;

	while (p != list->tail) {
		tmp = p->next;
		if ( _(destructor) )
			_(destructor)(&p->data);
		free(p);
		p = tmp;
	}

	free(list->head);
	free(list->tail);

	list->head = NULL;
	list->tail = NULL;
	list->_size = 0;
}

__list_t
_(front) (__list *list)
{
	if ( ! list->_size )
		__error("read data from an empty list\n", 0);
	return list->head->next->data;
}

__list_t
_(back) (__list *list)
{
	if ( ! list->_size )
		__error("read data from an empty list\n", 0);
	return list->tail->prev->data;
}

_(iterator)
_(first) (__list *list)
{
	return &list->head->next->data;
}

_(iterator)
_(last) (__list *list)
{
	return &list->tail->prev->data;
}

_(iterator)
_(head) (__list *list)
{
	return &list->head->data;
}

_(iterator)
_(tail) (__list *list)
{
	return &list->tail->data;
}

_(iterator)
_(prev) (__list *list, _(iterator) it)
{
	_(node) *p = __sptr( _(node), data, it );
	if ( ! p->prev ) {
		__error("iterator out of bound\n", 0);
		return NULL;
	}
	return &p->prev->data;
}

_(iterator)
_(next) (__list *list, _(iterator) it)
{
	_(node) *p = __sptr( _(node), data, it );
	if ( ! p->next ) {
		__error("iterator out of bound\n", 0);
		return NULL;
	}
	return &p->next->data;
}

int
_(empty) (__list *list)
{
	if ( list->_size )
		return 0;
	return 1;
}

size_t
_(size) (__list *list)
{
	return list->_size;
}

void
_(clear) (__list *list)
{
	_(destroy)(list);
	_(init)(list);
}

int
_(insert) (__list *list, _(iterator) it, const __list_t *t)
{
	_(node) *p = __sptr( _(node), data, it );
	_(node) *p1 = (_(node)*) malloc ( sizeof(_(node)) );
	if ( p == list->head ) {
		free(p1);
		__error("insert pos error\n", 0);
		return 0;
	}
	if ( ! p1 ) {
		free(p1);
		return 0;
	}

/*	memcpy(&p1->data, t, sizeof(__list_t)); */
	if ( _(copyer) )
		_(copyer)(&p1->data, t);
	else
		p1->data = *t;

	p1->next = p;
	p1->prev = p->prev;
	p->prev = p1;
	p1->prev->next = p1;
	++list->_size;
	return 1;
}

int
_(erase) (__list *list, _(iterator) it)
{
	_(node) *p = __sptr( _(node), data, it );
	if ( p == list->head || p == list->tail ) {
		__error("erase pos error\n", 0);
		return 0;
	}
	p->next->prev = p->prev;
	p->prev->next = p->next;
	if ( _(destructor) )
		_(destructor)(it);
	free(p);
	--list->_size;
	return 1;
}


int
_(push_back) (__list *list, const __list_t *t)
{
	return _(insert)(list, _(tail)(list), t);
}

int
_(push_front) (__list *list, const __list_t *t)
{
	return _(insert)(list, _(first)(list), t);
}

int
_(pop_back) (__list *list)
{
	return _(erase)(list, _(last)(list));
}

int
_(pop_front) (__list *list)
{
	return _(erase)(list, _(first)(list));
}

int
_(assign) (__list *list, size_t count, const __list_t *t)
{
	size_t i;

	_(clear)(list);
	for (i=0; i<count; ++i)
		if ( ! _(push_back)(list, t) )
			return 0;
	return 1;
}

void
_(write) (__list *list, FILE *fp)
{
	_(iterator) it = _(first)(list);

	fwrite(&list->_size, sizeof(size_t), 1, fp);
	while (it != _(tail)(list)) {
		fwrite(it, sizeof(__list_t), 1, fp);
		it = _(next)(list, it);
	}
}

void
_(read) (__list *list, FILE *fp)
{
	size_t i, _size;
	__list_t t;

/*	_(init)(list); */
	fread(&_size, sizeof(size_t), 1, fp);
	for (i=0; i<_size; ++i) {
		fread(&t, sizeof(__list_t), 1, fp);
		_(push_back)(list, &t);
	}
}

int
_(save) (__list *list, const char *fname)
{
	FILE *fp;
	fp = fopen(fname, "w");
	if ( ! fp )
		return 0;
	_(write)(list, fp);
	fclose(fp);
	return 1;
}

int
_(load) (__list *list, const char *fname)
{
	FILE *fp;
	fp = fopen(fname, "r");
	if ( ! fp )
		return 0;
	_(read)(list, fp);
	fclose(fp);
	return 1;
}

int
_(traverse) (__list *list, int (*f)(__list_t*))
{
	int ret;
	_(iterator) it;

	it = list->begin(list);
	while (it != list->end(list)) {
		ret = f(it);
		if ( ret )
			return ret;
		it = list->next(list, it);
	}
	return 0;
}

int
_(rtraverse) (__list *list, int (*f)(__list_t*))
{
	int ret;
	_(iterator) it;

	it = list->rbegin(list);
	while (it != list->rend(list)) {
		ret = f(it);
		if ( ret )
			return ret;
		it = list->prev(list, it);
	}
	return 0;
}

__list*
_(find_if) (__list *list, int (*f)(const __list_t*))
{
	int ret;
	__list *L=(__list*)malloc(sizeof(__list));
	_(iterator) it;

	_(init)(L);

	it = list->begin(list);
	while (it != list->end(list)) {
		ret = f(it);
		if ( ret )
			L->push_back(L, it);
		it = list->next(list, it);
	}

	return L;
}

int
_(remove_if) (__list *list, int (*f)(const __list_t*))
{
	int n=0;
	_(iterator) it, it1;

	it = list->begin(list);
	while (it != list->end(list)) {
		it1 = list->next(list, it);
		if ( f(it) )
			++n, list->erase(list, it);
		it = it1;
	}
	return n;
}

int
_(init) (__list *list)
{
	list->head = (_(node)*) malloc ( sizeof(_(node)) );
	if ( ! list->head )
		return 0;
	list->tail = (_(node)*) malloc ( sizeof(_(node)) );
	if ( ! list->tail ) {
		free ( list->head );
		return 0;
	}
	list->head->prev = NULL;
	list->head->next = list->tail;
	list->tail->prev = list->head;
	list->tail->next = NULL;
	list->_size = 0;

	list->front = _(front);
	list->back = _(back);

	list->begin = _(first);
	list->end = _(tail);
	list->rbegin = _(last);
	list->rend = _(head);
	list->prev = _(prev);
	list->next = _(next);

	list->empty = _(empty);
	list->size = _(size);
	list->clear = _(clear);
	list->assign = _(assign);

	list->insert = _(insert);
	list->erase = _(erase);
	list->push_back = _(push_back);
	list->push_front = _(push_front);
	list->pop_back = _(pop_back);
	list->pop_front = _(pop_front);

	list->write = _(write);
	list->read = _(read);
	list->save = _(save);
	list->load = _(load);

	list->traverse = _(traverse);
	list->rtraverse = _(rtraverse);
	list->find_if = _(find_if);
	list->remove_if = _(remove_if);

	list->destroy = _(destroy);

	list->set_copyer = _(set_copyer);
	list->set_destructor = _(set_destructor);

	return 1;
}

#undef __list_lk__
#undef __list_lk
#undef __list

#undef ___
#undef __
#undef _

#undef __error__
#undef __error

#undef __list_t
#undef __sptr

#endif
