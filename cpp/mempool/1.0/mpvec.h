#ifndef _MPVEC_H_
#define _MPVEC_H_

#ifndef _GLIBCXX_VECTOR
#include <vector>
#endif

#define __tt(T)	template <typename T>

__tt(T)
class mp_size_t{
	T t;
};

__tt(T)
class mempool{
  public:
	void* alloc(){return alloc(1);}
	void* alloc(size_t size);
	void free(void*);

	size_t remain(){return mpvec_capacity-mpvec_size+index.size();}
	mempool(size_t count);

  private:
	size_t mpvec_size;
	size_t mpvec_capacity;
	mp_size_t<T> *base;
	std::vector<mp_size_t<T>> memory;
	std::vector<int> index;
};

__tt(T)
mempool<T>::mempool(size_t count):mpvec_size(0),mpvec_capacity(count)
{
	memory.reserve(count);
	memory.resize(count);
	base = &memory.front();
}

__tt(T)
void*
mempool<T>::alloc(size_t size)
{
	int i;

	if ((mpvec_size==mpvec_capacity && index.empty()) || size>sizeof(mp_size_t<T>))
		return NULL;
	if (!index.empty()) {
		i = index.back();
		index.pop_back();
		return (void*)(base+i);
	}
	mpvec_size++;
	return (void*)(base+mpvec_size);
}

__tt(T)
inline void
mempool<T>::free(void *p)
{
	index.push_back((mp_size_t<T>*)p-base);
}

#undef __tt

#endif
