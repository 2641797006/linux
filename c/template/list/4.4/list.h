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

#ifndef _STDIO_H /* io */
#include <stdio.h>
#ifndef _STDIO_H
#define _STDIO_H
#endif
#endif

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

	void (*sort)(struct __list*, int (*)(const __list_t*, const __list_t*));

}__list;


int _(init) (__list*);

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
