#ifndef _PMANIFD_H_
#define _PMANIFD_H_

#ifndef _MALLOC_H
#include <malloc.h>
#endif

typedef struct{
	int *data;
	int num;
	int memsize;
}MANIFD;

int InitManifd_n(MANIFD* L, int n)
{
	int *p;
	if(n>0){
		p=malloc(sizeof(int)*n);
		if(!p)
			return -1;
		L->data=p;
	}
	L->num=0;
	L->memsize=n;
	return 0;
}

#define InitManifd(L) InitManifd_n(L, 1)

void DestroyManifd(MANIFD* L)
{
	free(L->data);
	L->data=NULL;
	L->num=0;
	L->memsize=0;
}

int ManifdTraverse(MANIFD* L, int (*visit)(int*))
{
	int* p=L->data;
	int i, n=L->num, ret;
	for(i=1;i<=n;i++,p++)
		if(ret=visit(p))
			return ret;
	return 0;
}

int ManifdInsert(MANIFD* L, int i, int data)
{
	int *p0, *p1;
	if(i<1||i>L->num+1)
		return -1;
	p0=L->data;
	if(L->num==L->memsize){
		p0=realloc(p0, (L->num+0x40)*sizeof(int));
		if(!p0)
			return -2;
		L->data=p0;
		L->memsize+=0x40;
	}
	p1=p0+i-1;
	p0+=L->num;
	while(p0>p1)
		*p0=*--p0;
	*p1=data;
	L->num++;
	return 0;
}




int SetManifd(MANIFD* L, int n, ...)
{
	int i, *p=L->data, *val=&n+1;
	for(i=0;i<n;i++)
		*p++=*val++;
	L->num=n;
	L->memsize=n;
	return i;
}












#endif
