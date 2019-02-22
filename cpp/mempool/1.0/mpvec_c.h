#ifndef _MPVEC_C_H_
#define _MPVEC_C_H_

#ifndef _STDLIB_H
#include <stdlib.h>
#endif

struct mp_c{
	unsigned char *vec;	//基址 g++(c++模式下)空指针相减error [抠鼻]
	size_t vec_size;	//已申请内存块 [虚] 数量
	size_t vec_capacity;	//内存块总数
	size_t vec_blocksize;	//单个内存块大小
	size_t *index;		//free的内存块会记录在此
	size_t ind_size;	//index中元素个数
};

struct mp_c*
mp_create(size_t sz, size_t num) //sz:内存块大小, num:内存块数量
{
	struct mp_c *m = (struct mp_c*)malloc(sizeof(struct mp_c));
	if (!m)
		return NULL;
	m->vec = (unsigned char*)malloc(sz*num);
	m->index = (size_t*)malloc(sizeof(size_t)*num);
	if (!m->vec||!m->index)
		return NULL;
	m->vec_size = 0;
	m->vec_capacity = num;
	m->vec_blocksize = sz;
	m->ind_size = 0;
	return m;
}

void*
mp_alloc(struct mp_c *m, size_t sz)
{
	if ((m->vec_size==m->vec_capacity && !m->ind_size) || sz>m->vec_blocksize)
		return NULL;
	if (m->ind_size)
		return (void*)(m->vec+m->index[--m->ind_size]);
	return (void*)(m->vec+m->vec_blocksize*m->vec_size++);
}

void
mp_free(struct mp_c *m, void *p)
{
	m->index[m->ind_size++] = (unsigned char*)p-m->vec;
}

void
mp_destroy(struct mp_c *m)
{
	free(m->vec);
	free(m->index);
	free(m);
}

#endif
