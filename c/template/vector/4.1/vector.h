#ifndef vector_t
# error: 24k macro: No define vector_t
#else

#include <stdlib.h>
#include <string.h>

#define _24k_vector_init_size	0x4
#define _24k_expand_times	2.0

typedef struct{
	vector_t *data;
	size_t size;
	size_t capacity;
}vector;

typedef vector_t* vector_iterator;

int
vector_init (vector *vec)
{
	vec->data = (vector_t*) malloc (_24k_vector_init_size * sizeof(vector_t));
	if ( ! vec->data )
		return 0;
	vec->size = 0;
	vec->capacity = _24k_vector_init_size;
	return 1;
}

void
vector_destroy (vector *vec)
{
	free(vec->data);
	vec->data = NULL;
	vec->size = 0;
	vec->capacity = 0;
}

vector_t*
vector_at (vector *vec, size_t pos)
{
	if (pos<0 || pos>=vec->size)
		return NULL;
	return vec->data + pos;
}

vector_t
vector_front (vector *vec)
{
	return *vec->data;
}

vector_t
vector_back (vector *vec)
{
	return *(vec->data + vec->size - 1);
}

vector_t*
vector_data (vector *vec)
{
	return vec->data;
}

vector_iterator
vector_first (vector *vec)
{
	return vec->data;
}

vector_iterator
vector_last (vector *vec)
{
	return vec->data + vec->size - 1;
}

vector_iterator
vector_head (vector *vec)
{
	return vec->data - 1;
}

vector_iterator
vector_tail (vector *vec)
{
	return vec->data + vec->size;
}

vector_iterator
vector_prev (vector_iterator it)
{
	return it-1;
}

vector_iterator
vector_next (vector_iterator it)
{
	return it+1;
}

int
vector_empty (vector *vec)
{
	return vec->size ? 0 : 1;
}

size_t
vector_size (vector *vec)
{
	return vec->size;
}

int
vector_reserve (vector *vec, size_t new_cap)
{
	vector_t *p;
	if (new_cap > vec->capacity) {
		p = (vector_t*) realloc (vec->data, new_cap * sizeof(vector_t));
		if ( ! p )
			return 0;
		vec->data = p;
		vec->capacity = new_cap;
	}
	return 1;
}

size_t
vector_capacity (vector *vec)
{
	return vec->capacity;
}

void
vector_shrink_to_fit (vector *vec)
{
	if (vec->size < vec->capacity) {
		vec->data = realloc(vec->data, (vec->size ? vec->size : 1) * sizeof(vector_t));
		vec->capacity = vec->size ? vec->size : 1;
	}
}

void
vector_clear (vector *vec)
{
	vec->size = 0;
}

int
vector_resize (vector *vec, size_t count)
{
	if (vec->size >= count)
		vec->size = count;
	else {
		if ( vector_reserve(vec, count) )
			memset(vec + vec->size, 0, (count - vec->size) * sizeof(vector_t));
		else
			return 0;
	}
	return 1;
}

int
vector_insert (vector *vec, vector_iterator it, const vector_t *t)
{
	size_t pos = it - vector_first(vec);
	vector_t *p;

	if ( pos<0 || pos>vec->size )
		return 0;
	if ( vec->size == vec->capacity && ! vector_reserve(vec, vec->capacity * _24k_expand_times) )
		return 0;
	p = vec->data + pos;
	memmove( p+1, p, sizeof(vector_t) * (vec->size - pos) );
	memcpy(p, t, sizeof(vector_t));
	++vec->size;
	return 1;
}

int
vector_erase (vector *vec, vector_iterator it)
{
	size_t pos = it - vector_first(vec);
	vector_t *p;

	if (pos<0 || pos>=vec->size)
		return 0;
	p = vec->data + pos;
	memmove( p, p+1, sizeof(vector_t) * (--vec->size - pos) );
	return 1;
}

int
vector_push_back (vector *vec, const vector_t *t)
{
	return vector_insert(vec, vector_tail(vec), t);
}

int
vector_pop_back (vector *vec)
{
	return vector_erase(vec, vector_last(vec));
}

int
vector_assign (vector *vec, size_t count, const vector_t *t)
{
	size_t i;

	vector_clear(vec);
	for (i=0; i<count; ++i)
		if ( ! vector_push_back(vec, t) )
			return 0;
	return 1;
}

void
vector_write (vector *vec, FILE *fp)
{
	fwrite(&vec->size, sizeof(size_t), 1, fp);
	fwrite(vector_data(vec), sizeof(vector_t), vec->size, fp);
}

void
vector_read (vector *vec, FILE *fp)
{
	size_t size;

	vector_init(vec);
	fread(&size, sizeof(size_t), 1, fp);
	vector_reserve(vec, size);
	vec->size = size;
	fread(vector_data(vec), sizeof(vector_t), vec->size, fp);
}

int
vector_save (vector *vec, const char *fname)
{
	FILE *fp;
	fp = fopen(fname, "w");
	if ( ! fp )
		return 0;
	vector_write(vec, fp);
	fclose(fp);
	return 1;
}

int
vector_load (vector *vec, const char *fname)
{
	FILE *fp;
	fp = fopen(fname, "r");
	if ( ! fp )
		return 0;
	vector_read(vec, fp);
	fclose(fp);
	return 1;
}

#undef _24k_vector_init_size
#undef _24k_expand_times

#undef vector_t

#endif
