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
	mempool(size_t count){init(count);} //使用此构造函数 或 使用init(count) 来构建内存池
	~mempool(){destroy();}

	bool init(size_t count); //申请count个T大小的内存, 构建内存池
	bool resize(size_t count); //调整内存池大小, 缩小内存池时会清空<内存分配记录>, count=0时同destroy();
	void destroy(){::free(base+1); ::free(index);} //释放内存, 销毁内存池
	void reset(); //清空内存分配记录
	size_t size(){return mp_capacity;} //返回内存池容量(以T大小为单位)
	bool empty(){return mp_size==ind_size;} //是否有已分配的内存

	void savefile(FILE *fp);
	void loadfile(FILE *fp);

  private:
	mp_size_t<T> *base;
	size_t mp_size;
	size_t mp_capacity;

	ptrdiff_t *index;
	size_t ind_size;
};

__tt(T)
inline void
mempool<T>::savefile(FILE *fp)
{
	fwrite(base+1, sizeof(T), mp_size, fp);
	fwrite(index, sizeof(ptrdiff_t), ind_size, fp);
}

__tt(T)
inline void
mempool<T>::loadfile(FILE *fp)
{
	fread(base+1, sizeof(T), mp_size, fp);
	fread(index, sizeof(ptrdiff_t), ind_size, fp);
}

__tt(T)
inline void
mempool<T>::reset()
{
	mp_size = 0;
	ind_size = 0;
}

__tt(T)
bool
mempool<T>::resize(size_t count)
{
	if (count < mp_capacity)
		reset();
	index = (ptrdiff_t*)realloc(index, sizeof(ptrdiff_t)*count);
	if (!index)
		return false;
	base = (mp_size_t<T>*)realloc(base+1, sizeof(T)*count); // base+0 for OFF_NULL
	if (!base)
		return false;
	--base;
	mp_capacity = count;
	return true;
}

__tt(T)
bool
mempool<T>::init(size_t count)
{
	if (!count)
		count = mp_capacity;
	else {
		mp_size = 0;
		mp_capacity = count;
		ind_size = 0;
	}
	base = (mp_size_t<T>*)malloc(sizeof(T)*count); // base+0 for OFF_NULL
	if (!base)
		return false;
	--base;
	index = (ptrdiff_t*)malloc(sizeof(ptrdiff_t)*count);
	if (!index) {
		::free(base+1);
		return false;
	}
	return true;
}

__tt(T)
inline ptrdiff_t
mempool<T>::alloc()
{
	return ind_size ? index[--ind_size] :
		(mp_size==mp_capacity
		? (resize(mp_capacity*2) ? alloc() : OFF_NULL)
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
