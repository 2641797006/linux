#ifndef _24k_vector_t
# error: No define "_24k_vector_t"
#else

#if defined _MSC_VER && ! defined __func__
#define __func__ __FUNCTION__
#endif

/*
 * T = _24k_vector_t
 * T_vector // vector type
 * T_vector_iterator // itetator type
 *
 * bool T_vector_init (T_vector *vec) // init T_vector vec
 * void T_vector_destroy (T_vector *vec) // destroy T_vector vec
 *
 * bool T_vector_assign (T_vector *vec, size_t count, const T *t) // 清空vec 并且 插入count个t
 * T* T_vector_at (T_vector *vec, size_t pos) // 获取vec中第pos个元素的地址
 * T T_vector_front (T_vector *vec) // 获取vec首个元素
 * T T_vector_back (T_vector *vec) // 获取vec最后一个元素
 * T* T_vector_data (T_vector *vec) // 返回vec的T数组首地址
 *
 * T_vector_iterator T_vector_first (T_vector *vec) // 返回指向首个元素的迭代器
 * T_vector_iterator T_vector_last (T_vector *vec) // 返回指向最后一个元素的迭代器
 * T_vector_iterator T_vector_head (T_vector *vec) // 首个元素前一个位置
 * T_vector_iterator T_vector_tail (T_vector *vec) // 最后一个元素后一个位置
 * bool T_vector_prev (T_vector_iterator *pit) // pit:迭代器地址, 使迭代器指向前一个元素
 * bool T_vector_next (T_vector_iterator *pit) // pit:迭代器地址, 使迭代器指向后一个元素
 *
 * bool T_vector_empty (T_vector *vec) // 判断vec是否为空
 * size_t T_vector_size (T_vector *vec) // 返回vec元素个数
 * bool T_vector_reserve (T_vector *vec, size_t new_cap) // 保证vec可以容纳new_cap个元素, 避免多次扩展内存
 * size_t T_vector_capacity (T_vector *vec) // 返回vec的可以容纳元素的数量
 * void T_vector_shrink_to_fit (T_vector *vec) // 释放多余的内存
 * void T_vector_clear (T_vector *vec) // 清空vec中所有元素
 * bool T_vector_resize (T_vector *vec, size_t count) // 调整vec元素个数, 新增元素将被初始化为0
 *
 * bool T_vector_insert (T_vector *vec, T_vector_iterator it, const T *t) // 在迭代器it前面插入元素t
 * bool T_vector_erase (T_vector *vec, T_vector_iterator it) // 删除迭代器it指向的元素
 * bool T_vector_push_back (T_vector *vec, const T *t) // 在vec末尾插入元素t
 * bool T_vector_pop_back (T_vector *vec) // 删除vec最后一个元素
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

#define _24k_vector_lk__(T)	T##_##vector
#define _24k_vector_lk(T)	_24k_vector_lk__(T)
#define _24k_vector	_24k_vector_lk(_24k_vector_t)

#define _24k__(x, T)	T##_##vector##_##x
#define _24k_(x, T)	_24k__(x, T)
#define _24k(x)		_24k_(x, _24k_vector_t)

#define _24k_error__(fmt, ...)	_24k(fatal_error)(__FILE__, __func__, __LINE__, fmt, __VA_ARGS__)
#define _24k_error(fmt, ...)	_24k_error__(fmt, __VA_ARGS__)

#define _24k_vector_init_size	0x4
#define _24k_expand_times	2.0

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

typedef struct{
	_24k_vector_t *data;
	size_t size;
	size_t capacity;
}_24k_vector;

typedef _24k_vector_t* _24k(iterator);

int
_24k(init) (_24k_vector *vec)
{
	vec->data = (_24k_vector_t*) malloc (_24k_vector_init_size * sizeof(_24k_vector_t));
	if ( ! vec->data )
		return 0;
	vec->size = 0;
	vec->capacity = _24k_vector_init_size;
	return 1;
}

void
_24k(destroy) (_24k_vector *vec)
{
	free(vec->data);
	vec->data = NULL;
	vec->size = 0;
	vec->capacity = 0;
}

_24k_vector_t*
_24k(at) (_24k_vector *vec, size_t pos)
{
	if ( pos<0 || pos>=vec->size ) {
		_24k_error("Index out of bound, index=%d, size=%d\n", pos, vec->size);
		return 0;
	}
	return vec->data + pos;
}

_24k_vector_t
_24k(front) (_24k_vector *vec)
{
	if ( ! vec->size )
		_24k_error("read data from a vector which is empty\n", 0);
	return *vec->data;
}

_24k_vector_t
_24k(back) (_24k_vector *vec)
{
	if ( ! vec->size )
		_24k_error("read data from a vector which is empty\n", 0);
	return *(vec->data + vec->size - 1);
}

_24k_vector_t*
_24k(data) (_24k_vector *vec)
{
	return vec->data;
}

_24k(iterator)
_24k(first) (_24k_vector *vec)
{
	return vec->data;
}

_24k(iterator)
_24k(last) (_24k_vector *vec)
{
	return vec->data + vec->size - 1;
}

_24k(iterator)
_24k(head) (_24k_vector *vec)
{
	return vec->data - 1;
}

_24k(iterator)
_24k(tail) (_24k_vector *vec)
{
	return vec->data + vec->size;
}

_24k(iterator)
_24k(prev) (_24k(iterator) it)
{
	return --it;
}

_24k(iterator)
_24k(next) (_24k(iterator) it)
{
	return ++it;
}

int
_24k(empty) (_24k_vector *vec)
{
	if ( vec->size )
		return 0;
	return 1;
}

size_t
_24k(size) (_24k_vector *vec)
{
	return vec->size;
}

int
_24k(reserve) (_24k_vector *vec, size_t new_cap)
{
	_24k_vector_t *p;
	if (new_cap > vec->capacity) {
		p = (_24k_vector_t*) realloc (vec->data, new_cap * sizeof(_24k_vector_t));
		if ( ! p )
			return 0;
		vec->data = p;
		vec->capacity = new_cap;
	}
	return 1;
}

size_t
_24k(capacity) (_24k_vector *vec)
{
	return vec->capacity;
}

void
_24k(shrink_to_fit) (_24k_vector *vec)
{
	if (vec->size < vec->capacity) {
		vec->data = realloc(vec->data, (vec->size ? vec->size : 1) * sizeof(_24k_vector_t));
		vec->capacity = vec->size ? vec->size : 1;
	}
}

void
_24k(clear) (_24k_vector *vec)
{
	vec->size = 0;
}

int
_24k(resize) (_24k_vector *vec, size_t count)
{
	int r;
	if (vec->size >= count)
		vec->size = count;
	else {
		r = _24k(reserve)(vec, count);
		if ( r )
			memset(vec + vec->size, 0, (count - vec->size) * sizeof(_24k_vector_t));
		else
			return 0;
	}
	return 1;
}

int
_24k(insert) (_24k_vector *vec, _24k(iterator) it, const _24k_vector_t *t)
{
	size_t pos = it - _24k(data)(vec);
	_24k_vector_t *p;

	if ( pos<0 || pos>vec->size ) {
		_24k_error("Index out of bound, index=%d, size=%d\n", pos, vec->size);
		return 0;
	}
	if ( vec->size == vec->capacity && ! _24k(reserve)(vec, vec->capacity * _24k_expand_times) )
		return 0;
	p = vec->data + pos;
	memmove( p+1, p, sizeof(_24k_vector_t) * (vec->size - pos) );
	memcpy(p, t, sizeof(_24k_vector_t));
	++vec->size;
	return 1;
}

int
_24k(erase) (_24k_vector *vec, _24k(iterator) it)
{
	size_t pos = it - _24k(data)(vec);
	_24k_vector_t *p;

	if (pos<0 || pos>=vec->size) {
		_24k_error("Index out of bound, index=%d, size=%d\n", pos, vec->size);
		return 0;
	}
	p = vec->data + pos;
	memmove( p, p+1, sizeof(_24k_vector_t) * (--vec->size - pos) );
	return 1;
}

int
_24k(push_back) (_24k_vector *vec, const _24k_vector_t *t)
{
	return _24k(insert)(vec, _24k(tail)(vec), t);
}

int
_24k(pop_back) (_24k_vector *vec)
{
	return _24k(erase)(vec, _24k(last)(vec));
}

int
_24k(assign) (_24k_vector *vec, size_t count, const _24k_vector_t *t)
{
	size_t i;

	_24k(clear)(vec);
	for (i=0; i<count; ++i)
		if ( ! _24k(push_back)(vec, t) )
			return 0;
	return 1;
}

#undef _24k_vector_lk__
#undef _24k_vector_lk
#undef _24k_vector

#undef _24k__
#undef _24k_
#undef _24k

#undef _24k_error__
#undef _24k_error

#undef _24k_vector_init_size
#undef _24k_expand_times

#undef _24k_vector_t

#endif
