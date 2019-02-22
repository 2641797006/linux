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

	void print();
	size_t remain(){return mpind_size;}
	mempool(size_t count);
	~mempool(){ delete[] mpvec; delete[] mpind;}

  private:
	mp_size_t<T> *mpvec;
	size_t mpvec_size;
	size_t *mpind;
	size_t mpind_size;
};

__tt(T)
mempool<T>::mempool(size_t count)
{
	size_t i=-1;
	size_t *mpind;

	mpvec_size = count;
	mpvec = new mp_size_t<T>[count];
	mpind_size = count;
	this->mpind = new size_t[count];
	mpind = this->mpind;
	while(++i<count)
		mpind[i]=i;
}

__tt(T)
inline void*
mempool<T>::alloc(size_t size)
{
	return ((!mpind_size) || size>sizeof(mp_size_t<T>)) ? NULL : (void*)(mpvec+mpind[--mpind_size]);
}

__tt(T)
inline void
mempool<T>::free(void *p)
{
	mpind[mpind_size++]=(mp_size_t<T>*)p-mpvec;
}

__tt(T)
void
mempool<T>::print()
{
	std::cout<<"内存块数: "<<mpvec_size<<'\n'
		 <<"单块字节: "<<sizeof(mp_size_t<T>)<<'\n'
		 <<"已用块数: "<<mpvec_size-mpind_size<<'\n'
		 <<"mpvec_size:"<<mpvec_size<<'\n'
		 <<"mpind_size:"<<mpind_size<<'\n';
}

#undef __tt

#endif
