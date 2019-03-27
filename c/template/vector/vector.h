#ifndef _24k_vector_t
#error: No define "_24k_vector_t"
#endif

#ifndef _MEMORY_H
#include <memory.h>
#ifndef _MEMORY_H
#define _MEMORY_H
#endif
#endif

#ifndef _STRING_H
#include <string.h>
#ifndef _STRING_H
#define _STRING_H
#endif
#endif

#ifndef _STDARG_H
#include <stdarg.h>
#ifndef _STDARG_H
#define _STDARG_H
#endif
#endif

#ifndef _STDLIB_H
#include <stdlib.h>
#ifndef _STDLIB_H
#define _STDLIB_H
#endif
#endif

#define _24k_vector_lk__(T)	T##_##vector
#define _24k_vector_lk(T)	_24k_vector_lk__(T)
#define _24k_vector	_24k_vector_lk(_24k_vector_t)

#define _24k__(x, T)	T##_##vector##_##x
#define _24k_(x, T)	_24k__(x, T)
#define _24k(x)		_24k_(x, _24k_vector_t)

#define _24k_error__(fmt, ...)	_24k(fatal_error)(fmt, __VA_ARGS__)
#define _24k_error(fmt, ...)	_24k_error__(fmt, __VA_ARGS__)

#define _24k_strmac__(x)	#x
#define _24k_strmac(x)		_24k_strmac__(x)

#define _24k_vector_init_size	0x4
#define _24k_expand_times	2.0

void
_24k(fatal_error) (const char *fmt, ...) {
#ifndef _24k_vector_not_print_error
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
#endif
#ifndef _24k_vector_not_exit
	exit(24);
#endif
}

typedef struct{
	_24k_vector_t *data;
	size_t size;
	size_t capacity;
}_24k_vector;

int
_24k(init) (_24k_vector *vec) {
	vec->data = (_24k_vector_t*) malloc (_24k_vector_init_size * sizeof(_24k_vector_t));
	if ( ! vec->data ) {
		_24k_error("error: %s: Memory allocation failed\n", _24k_strmac(_24k(init)));
		return 0;
	}
	vec->size = 0;
	vec->capacity = _24k_vector_init_size;
	return 1;
}

void
_24k(destroy) (_24k_vector *vec) {
	free(vec->data);
	vec->size = 0;
	vec->capacity = 0;
}

int
_24k(insert) (_24k_vector *vec, int pos, _24k_vector_t *t) {
	_24k_vector_t *p0, *p1;

	if ( pos<0 || pos>vec->size ) {
		_24k_error("error: %s: Index out of bound, pos=%d, size=%d\n", _24k_strmac(_24k(insert)), pos, vec->size);
		return 0;
	}
	p0 = vec->data;
	if ( vec->size == vec->capacity ) {
		p0 = (_24k_vector_t*) realloc (p0, (size_t)(vec->capacity * _24k_expand_times) * sizeof(_24k_vector_t));
		if ( ! p0 ) {
			_24k_error("error: %s: Memory reallocation failed\n", _24k(insert));
			return 0;
		}
		vec->data = p0;
		vec->capacity = (size_t)(vec->capacity * _24k_expand_times);
	}
	p1 = p0 + pos;
	p0 += vec->size;
	while ( p0 > p1 )
		memcpy(p0, p0-1, sizeof(_24k_vector_t)), --p0;
	memcpy(p1, t, sizeof(_24k_vector_t));
	++vec->size;
	return 1;
}

int
_24k(traverse) (_24k_vector *vec, int (*visit)(_24k_vector_t*)) {
	_24k_vector_t *p = vec->data;
	int i, r, size = vec->size;

	for (i=0; i<size; ++i,++p) {
		r = visit(p);
		if (r)
			return r;
	}
	return 0;
}


#undef _24k_vector_lk__
#undef _24k_vector_lk
#undef _24k_vector

#undef _24k__
#undef _24k_
#undef _24k

#undef _24k_error__
#undef _24k_error

#undef _24k_strmac__
#undef _24k_strmac

#undef _24k_vector_init_size
#undef _24k_expand_times

#undef _24k_vector_t
