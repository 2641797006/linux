#ifndef _MPVEC_H_
#define _MPVEC_H_

#define __tt(T)	template <typename T>

__tt(T)
class mp_size_t{
	T t;
};

__tt(T)
class mempool{
  public:
	void* alloc();
	void* alloc(size_t size){return size>sizeof(mp_size_t<T>) ? NULL : alloc();}
	void free(void*);

	void print();
	size_t remain(){return mpvec_capacity-mpvec_size+mpptr_size;}
	mempool(size_t count);
	~mempool(){ delete[] mpvec; delete[] mpptr;}

  private:
	mp_size_t<T> *mpvec;
	size_t	mpvec_size;
	size_t	mpvec_capacity;
	void	**mpptr;
	size_t	mpptr_size;
};

__tt(T)
mempool<T>::mempool(size_t count)
{
	mpvec_size = 0;
	mpvec_capacity = count;
	mpvec = new mp_size_t<T>[count];
	mpptr_size = 0;
	mpptr = new void*[count];
}

__tt(T)
void*
mempool<T>::alloc()
{
	if (mpvec_size==mpvec_capacity && !mpptr_size)
		return NULL;
	if (mpptr_size)
		return mpptr[--mpptr_size];
	return (void*)(mpvec+mpvec_size++);
}

__tt(T)
inline void
mempool<T>::free(void *p)
{
	mpptr[mpptr_size++] = p;
}

__tt(T)
void
mempool<T>::print()
{
	std::cout<<'\n'
		 <<"***************************\n"
		 <<" all: "<<mpvec_capacity<<'\n'
		 <<"used: "<<mpvec_size-mpptr_size<<'\n'
		 <<"free: "<<mpvec_capacity-mpvec_size+mpptr_size<<'\n'
		 <<"sizeof()="<<sizeof(mp_size_t<T>)<<'\n'
		 <<"mpvec_size: "<<mpvec_size<<'\n'
		 <<"mpptr_size: "<<mpptr_size<<'\n'
		 <<"***************************\n";
}

#undef __tt

#endif
