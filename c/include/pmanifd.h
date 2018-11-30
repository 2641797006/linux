#ifndef _PMANIFD_H_
#define _PMANIFD_H_

#ifndef _MALLOC_H
#include <malloc.h>
#endif

#ifndef _STDARG_H
#include <stdarg.h>
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

void PrintManifd(MANIFD* L)
{
	int i, n=L->num, *p=L->data;
	putchar('{');
	for(i=1;i<n;i++)
		printf("%d, ", *p++);
	if(n>0)
		printf("%d", *p);
	putchar('}');
}

#define PrintManifd_ln(L) (PrintManifd(L), putchar('\n'))

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
		*p0=*(p0-1), p0--;

	*p1=data;
	L->num++;
	return 0;
}

int ManifdDelete(MANIFD* L, int i, int* p)
{
	int *p0, *p1;
	if(i<1||i>L->num)
		return -1;
	p0=L->data+i-1;
	p1=L->data+L->num-1;
	p&&(*p=*p0);
	do
		*p0=*(p0+1);
	while(++p0<p1);
	L->num--;
	return 0;
}

void SortManifd(MANIFD* L)
{
	int tmp;
	int* Partition(int* left, int* right)
	{
		int pivot=*right, *tail;
		for(tail=left;left<right;left++)
			if(*left<=pivot){
				tmp=*left;
				*left=*tail;
				*tail++=tmp;
			}
		tmp=*right, *right=*tail, *tail=tmp;
		return tail;
	}
	void QuickSort(int* left, int*right)
	{
		if(left>=right)
			return;
		int *_pivot=Partition(left, right);
		QuickSort(left, _pivot-1);
		QuickSort(_pivot+1, right);
	}
	QuickSort(L->data, L->data+L->num-1);
}

int SetManifd(MANIFD* L, int n, ...)
{
	va_list ap;
	va_start(ap, n);
	int i, *p=L->data;
	for(i=1;i<=n;i++)
		if(ManifdInsert(L, L->num+1, va_arg(ap, int)))
			return i;
	va_end(ap);
	SortManifd(L);
	n=L->num;
	p=L->data+1;
	for(i=1;i<n;i++,p++)
		if(*p==*(p-1))
			ManifdDelete(L, i+1, NULL), i--, n--, p--;
	return 0;
}

int CloneManifd(MANIFD* A, MANIFD* B)
{
	int *p;
	p=malloc(B->memsize*sizeof(int));
	if(!p)
		return -1;
	A->data=p;
	A->num=B->num;
	A->memsize=B->memsize;
	int *p1=B->data, *end=B->data+B->num;
	while(p1<end)
		*p++=*p1++;
	return 0;
}










#endif
