#ifndef _MEMPOOL_H_
#define _MEMPOOL_H_

#ifndef _MEMORY_H
#include <memory.h>
#endif

#define __tt(T)		template <typename T>
#define OFF_NULL	(0)

namespace _24k{

__tt(T) class mp_size_t{T t;};

__tt(T)
class mempool{
  public:
	ptrdiff_t alloc();
	void free(ptrdiff_t);
	void* getptr(ptrdiff_t off){return (void*)(base+off);}

	mempool(){};
	mempool(size_t count){init(count);}
	~mempool(){::free(base+1); ::free(index);}

	void* init(size_t);
	void reset();
	size_t size(){return mp_capacity;}

	void savefile(FILE *fp);
	void loadfile(FILE *fp);

  private:
	ptrdiff_t expand();

	mp_size_t<T> *base;
	size_t mp_size;
	size_t mp_capacity;

	ptrdiff_t *index;
	size_t ind_size;
};

__tt(T)
void
mempool<T>::savefile(FILE *fp)
{
	fwrite(base+1, sizeof(T), mp_capacity, fp);
	fwrite(index, sizeof(ptrdiff_t), ind_size, fp);
}

__tt(T)
void
mempool<T>::loadfile(FILE *fp)
{
	fread(base+1, sizeof(T), mp_capacity, fp);
	fread(index, sizeof(ptrdiff_t), ind_size, fp);
}

__tt(T)
void
mempool<T>::reset()
{
	memset(base+1, 0, mp_capacity*sizeof(T));
	memset(index, 0, mp_capacity*sizeof(ptrdiff_t));
	mp_size = 0;
	ind_size = 0;
}

__tt(T)
ptrdiff_t
mempool<T>::expand()
{
	mp_capacity *= 2;
	base = (((mp_size_t<T>*)realloc(base+1, sizeof(T)*mp_capacity)) - 1); // base+0 for OFF_NULL
	index = (ptrdiff_t*)realloc(index, sizeof(ptrdiff_t)*mp_capacity);
	return alloc();
}

__tt(T)
void*
mempool<T>::init(size_t count)
{
	if (!count)
		count = mp_capacity;
	base = (((mp_size_t<T>*)malloc(sizeof(T)*count)) - 1); // base+0 for OFF_NULL
	index = (ptrdiff_t*)malloc(sizeof(ptrdiff_t) * count);
	if (count) {
		mp_size = 0;
		mp_capacity = count;
		ind_size = 0;
	}
	return base;
}

__tt(T)
inline ptrdiff_t
mempool<T>::alloc()
{
	return ind_size ? index[--ind_size] :
		(mp_size==mp_capacity
		? expand()
		: ++mp_size);
}

__tt(T)
inline void
mempool<T>::free(ptrdiff_t off)
{
	index[ind_size++] = off;
}

} //namespace _24k

#undef __tt
#undef OFF_NULL

#endif //_MEMPOOL_H_
