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
	void* alloc(){return alloc(1);}
	void* alloc(size_t size);
	void free(void*);

	void print();
	size_t remain(){return mpvec_capacity-mpvec_size+mpind_size;}
	mempool(size_t count);
	~mempool(){ delete[] mpvec; delete[] mpind;}

  private:
	mp_size_t<T> *mpvec;
	size_t mpvec_size;
	size_t mpvec_capacity;
	size_t *mpind;
	size_t mpind_size;
};

__tt(T)
mempool<T>::mempool(size_t count)
{
	mpvec_size = 0;
	mpvec_capacity = count;
	mpvec = new mp_size_t<T>[count];
	mpind_size = 0;
	mpind = new size_t[count];
}

__tt(T)
void*
mempool<T>::alloc(size_t size)
{
	size_t i;

	if ((mpvec_size==mpvec_capacity && !mpind_size) || size>sizeof(mp_size_t<T>))
		return NULL;
	if (mpind_size) {
		i = mpind[--mpind_size];
		return (void*)(mpvec+i);
	}
	mpvec_size++;
	return (void*)(mpvec+mpvec_size);
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
	std::cout<<'\n'
		 <<"***************************\n"
		 <<" all: "<<mpvec_capacity<<'\n'
		 <<"used: "<<mpvec_size-mpind_size<<'\n'
		 <<"free: "<<mpvec_capacity-mpvec_size+mpind_size<<'\n'
		 <<"sizeof()="<<sizeof(mp_size_t<T>)<<'\n'
		 <<"mpvec_size: "<<mpvec_size<<'\n'
		 <<"mpind_size: "<<mpind_size<<'\n'
		 <<"***************************\n";
}

#undef __tt

#endif
