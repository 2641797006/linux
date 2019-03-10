#ifndef _MEMPOOL_H_
#define _MEMPOOL_H_

#ifndef _BASIC_MEMPOOL_H_
#include "basic_mempool.h"
#endif

#define OFF_NULL	(0)
#define BASIC_MEMPOOL(i)	basic_mempool<char[1UL<<i]> m##i

namespace _24k{

class mempool{
  public:
	ptrdiff_t alloc(size_t);
	void free(ptrdiff_t);
	void* getptr(ptrdiff_t);

	bool resize(size_t count, size_t size); //保证有count个size大小的内存块, 以免多次扩增内存

	mempool(){status=0;}
	~mempool(){}

  private:
	size_t status;
	size_t mpow(size_t n){ // 不小于n的 最小2的幂
		--n;
		n |= n>>1;
		n |= n>>2;
		n |= n>>4;
		n |= n>>8;
		n |= n>>16;
		return n+1;
	}

// 2^2 ~ 2^30
	BASIC_MEMPOOL(2);
	BASIC_MEMPOOL(3);
	BASIC_MEMPOOL(4);
	BASIC_MEMPOOL(5);
	BASIC_MEMPOOL(6);
	BASIC_MEMPOOL(7);
	BASIC_MEMPOOL(8);
	BASIC_MEMPOOL(9);
	BASIC_MEMPOOL(10);
	BASIC_MEMPOOL(11);
	BASIC_MEMPOOL(12);
	BASIC_MEMPOOL(13);
	BASIC_MEMPOOL(14);
	BASIC_MEMPOOL(15);
	BASIC_MEMPOOL(16);
	BASIC_MEMPOOL(17);
	BASIC_MEMPOOL(18);
	BASIC_MEMPOOL(19);
	BASIC_MEMPOOL(20);
	BASIC_MEMPOOL(21);
	BASIC_MEMPOOL(22);
	BASIC_MEMPOOL(23);
	BASIC_MEMPOOL(24);
	BASIC_MEMPOOL(25);
	BASIC_MEMPOOL(26);
	BASIC_MEMPOOL(27);
	BASIC_MEMPOOL(28);
	BASIC_MEMPOOL(29);
	BASIC_MEMPOOL(30);
};

#define MPCASE(i, count)	case 1UL<<i: \
					if (! (status & size)) { \
						if (!m##i.init(count)) \
							return OFF_NULL; \
						status |= size; \
					} \
					return m##i.alloc()<<6 | i

ptrdiff_t
mempool::alloc(size_t size)
{
	size = mpow(size);
	switch (size) {
	case 1: case 2: size=4;
		MPCASE(2, 1<<10);
		MPCASE(3, 1<<9);
		MPCASE(4, 1<<8);
		MPCASE(5, 1<<7);
		MPCASE(6, 1<<6);
		MPCASE(7, 1<<5);
		MPCASE(8, 1<<4);
		MPCASE(9, 1<<3);
		MPCASE(10, 1<<2);
		MPCASE(11, 1<<1);
		MPCASE(12, 1);
		MPCASE(13, 1);
		MPCASE(14, 1);
		MPCASE(15, 1);
		MPCASE(16, 1);
		MPCASE(17, 1);
		MPCASE(18, 1);
		MPCASE(19, 1);
		MPCASE(20, 1);
		MPCASE(21, 1);
		MPCASE(22, 1);
		MPCASE(23, 1);
		MPCASE(24, 1);
		MPCASE(25, 1);
		MPCASE(26, 1);
		MPCASE(27, 1);
		MPCASE(28, 1);
		MPCASE(29, 1);
		MPCASE(30, 1);
	}
	return OFF_NULL;
}
#undef MPCASE

#define MPCASE(i)	case i: \
				m##i.free(off>>6); \
				return

void
mempool::free(ptrdiff_t off)
{
	switch (off & 0x3f) {
		MPCASE(2);
		MPCASE(3);
		MPCASE(4);
		MPCASE(5);
		MPCASE(6);
		MPCASE(7);
		MPCASE(8);
		MPCASE(9);
		MPCASE(10);
		MPCASE(11);
		MPCASE(12);
		MPCASE(13);
		MPCASE(14);
		MPCASE(15);
		MPCASE(16);
		MPCASE(17);
		MPCASE(18);
		MPCASE(19);
		MPCASE(20);
		MPCASE(21);
		MPCASE(22);
		MPCASE(23);
		MPCASE(24);
		MPCASE(25);
		MPCASE(26);
		MPCASE(27);
		MPCASE(28);
		MPCASE(29);
		MPCASE(30);
	}
}
#undef MPCASE

#define MPCASE(i)	case i: \
				return m##i.getptr(off>>6)

void*
mempool::getptr(ptrdiff_t off)
{
	switch (off & 0x3f) {
		MPCASE(2);
		MPCASE(3);
		MPCASE(4);
		MPCASE(5);
		MPCASE(6);
		MPCASE(7);
		MPCASE(8);
		MPCASE(9);
		MPCASE(10);
		MPCASE(11);
		MPCASE(12);
		MPCASE(13);
		MPCASE(14);
		MPCASE(15);
		MPCASE(16);
		MPCASE(17);
		MPCASE(18);
		MPCASE(19);
		MPCASE(20);
		MPCASE(21);
		MPCASE(22);
		MPCASE(23);
		MPCASE(24);
		MPCASE(25);
		MPCASE(26);
		MPCASE(27);
		MPCASE(28);
		MPCASE(29);
		MPCASE(30);
	}
	return NULL;
}
#undef MPCASE

#define MPCASE

void
mempool::resize(size_t count, size_t size)
{


}

} //namespace _24k

#undef OFF_NULL
#undef BASIC_MEMPOOL

#endif //_MEMPOOL_H_
