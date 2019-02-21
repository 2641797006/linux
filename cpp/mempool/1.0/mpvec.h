#ifndef _MPVEC_H_
#define _MPVEC_H_

#ifndef _GLIBCXX_VECTOR
#include <vector>
#endif

#define __tt(T)	template <typename T>

__tt(T)
class mpvec{
  public:
	void* Alloc(size_t);
	void Free(void*);

  private:
	T t_null;
	std::vector<T> memory;
	std::vector<int> index;
};

__tt(T)
void*
mpvec<T>::Alloc(size_t size)
{
	int i;

	if (size>sizeof(T))
		return NULL;
	if (!index.empty()) {
		i = index.back();
		index.pop_back();
		return (void*)(&memory.front()+i);
	}
	memory.push_back(t_null);
	return (void*)&memory.back();
}

__tt(T)
void
mpvec<T>::Free(void *p)
{
	index.push_back((T*)p-&memory.front());
}

#undef __tt

#endif
