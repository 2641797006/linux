#ifndef _PSQLIST_H_
#define _PSQLIST_H_

#ifndef _PCTYPE_H_
#include </home/lxll/c/git/include/pctype.h>
#endif

typedef int (*VISIT)(void*);

int SqListTraverse_O(void *p, int length, int size, VISIT visit)
{
	int i, ret;
	for(i=0;i<length;i++,p+=size){
		ret=visit(p);
		if(ret)
			return ret;
	}
	return 0;
}
#define SqListTraverse(p, length, visit) SqListTraverse_O(p, length, sizeof(*(p)), visit)

int SqListInsert_O(void **p0, int length, int size, int i, void *e)
{
	void *tmp, *p=*p0;
	if(i<1||i>length+1)
		return -1;
	tmp=realloc(p, (length+1)*size);
	if(!tmp)
		return -2;
	*p0=tmp;
	tmp=p+(i-1)*size;
	p+=length*size;
	while(p>tmp)
		memcpy(p, p-size, size), p-=size;
	memcpy(tmp, e, size);
	return 0;
}
#define SqListInsert(p, length, i, e) SqListInsert_O(&(p), length, sizeof(*(p)), i, e)
































#endif
