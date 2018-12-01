#ifndef _PDTUPLES_H_
#define _PDTUPLES_H_

#ifndef _MALLOC_H
#include <malloc.h>
#endif

typedef struct{
	int e1;
	int e2;
}DTUPLE;

#define CopyDtuple(dt1, dt2) ((dt1)->e1=(dt2)->e1, (dt1)->e2=(dt2)->e2)

typedef struct{
	DTUPLE *dt;
	int num;
	int memsize;
}DTUPLES;

int InitDtuples_n(DTUPLES* L, int n)
{
	DTUPLE *dt;
	if(n>0){
		dt=malloc(sizeof(DTUPLE)*n);
		if(!dt)
			return -1;
		L->dt=dt;
	}
	L->num=0;
	L->memsize=n;
	return 0;
}

#define InitDtuples(L) InitDtuples_n(L, 1)

void DestroyDtuples(DTUPLES* L)
{
	free(L->dt);
	L->dt=NULL;
	L->num=0;
	L->memsize=0;
}

int DtuplesTraverse(DTUPLES* L, int (*visit)(DTUPLE*))
{
	DTUPLE *dt=L->dt;
	int i, n=L->num, ret;
	for(i=1;i<=n;i++,dt++)
		if(ret=visit(dt))
			return ret;
	return 0;
}

void PrintDtuples(DTUPLES* L)
{
	int i, n=L->num;
	DTUPLE *dt=L->dt;
	putchar('{');
	for(i=1;i<n;i++,dt++)
		printf("<%d,%d>, ", dt->e1, dt->e2);
	if(n>0)
		printf("<%d,%d>", dt->e1, dt->e2);
	putchar('}');
}

#define PrintDtuples_ln(L) (PrintDtuples(L), putchar('\n'))

int DtuplesInsert(DTUPLES* L, int i, DTUPLE* dt)
{
	DTUPLE *dt0, *dt1;
	if(i<1||i>L->num+1)
		return -1;
	dt0=L->dt;
	if(L->num==L->memsize){
		dt0=realloc(dt0, (L->num+0x40)*sizeof(DTUPLE));
		if(!dt0)
			return -2;
		L->dt=dt0;
		L->memsize+=0x40;
	}
	dt1=dt0+i-1;
	dt0+=L->num;
	while(dt0>dt1)
		CopyDtuple(dt0, dt0-1), dt0--;
	CopyDtuple(dt1, dt);
	L->num++;
	return 0;
}

int DtuplesDelete(DTUPLES* L, int i, DTUPLE* dt)
{
	DTUPLE *dt0, *dt1;
	if(i<1||i>L->num)
		return -1;
	dt0=L->dt+i-1;
	dt1=L->dt+L->num-1;
	dt&&CopyDtuple(dt, dt0);
	do
		CopyDtuple(dt0, dt0+1);
	while(++dt0<dt1);
	L->num--;
	return 0;
}














#endif
