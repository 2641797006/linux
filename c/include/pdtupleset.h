#ifndef _PDTUPLESET_H_
#define _PDTUPLESET_H_

#ifndef _MALLOC_H
#include <malloc.h>
#endif

typedef struct{
	int e1;
	int e2;
}DTUPLE;

typedef struct{
	DTUPLE *dt;
	int num;
	int memsize;
}DTUPLESET;
















#endif
