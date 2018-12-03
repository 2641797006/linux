#ifndef _PDTUPLES_H_
#define _PDTUPLES_H_

#ifndef _MALLOC_H
#include <malloc.h>
#endif

#ifndef _P_SCAN_H_
#include </home/lxll/c/git/include/p_scan.h>
#endif

typedef struct{
	int e1;
	int e2;
}DTUPLE;

#define CopyDtuple_O(dt1, dt2) (dt1->e1=dt2->e1, dt1->e2=dt2->e2)
#define CopyDtuple(dt1, dt2) CopyDtuple_O((dt1), (dt2))
#define CmpaDtuple_O(dt1, dt2) (dt1->e1==dt2->e1 ? \
			CmpaElem(dt1->e2, dt2->e2) : \
			CmpaElem(dt1->e1, dt2->e1))
#define CmpaDtuple(dt1, dt2) CmpaDtuple_O((dt1), (dt2))

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

#define link_dtuple(e1, e2) #e1","#e2

void SortDtuples(DTUPLES* L)
{
	DTUPLE dtmp, *tail;
	DTUPLE* Partition(DTUPLE* left, DTUPLE* right)
	{
		for(tail=left;left<right;left++)
			if(CmpaDtuple(left, right)<=0){
				CopyDtuple(&dtmp, left);
				CopyDtuple(left, tail);
				CopyDtuple(tail, &dtmp), tail++;
			}
		CopyDtuple(&dtmp, right);
		CopyDtuple(right, tail);
		CopyDtuple(tail, &dtmp);
		return tail;
	}
	void QuickSort(DTUPLE* left, DTUPLE* right)
	{
		if(left>=right)
			return;
		DTUPLE *_pivot=Partition(left, right);
		QuickSort(left, _pivot-1);
		QuickSort(_pivot+1, right);
	}
	QuickSort(L->dt, L->dt+L->num-1);
}

int SetDtuples(DTUPLES* L, char* dtstr)
{
	char *dts=dtstr;
	DWORD c, dw, flag, i=0;
	DTUPLE dt, *dtp;
	for(;;){
		c=*dts++;
		if(!c)
			break;
		if(!isdigit(c)&&(c!='+')&&(c!='-'))
			continue;
		c=_dw_scan(dts-1, &dw, &flag);
		if(c<1||!(flag&SCAN_OK))
			break;
		i++;
		dts=dts+c-1;
		if(i%2)
			dt.e1=dw;
		else{
			dt.e2=dw;
			if(DtuplesInsert(L, L->num+1, &dt))
				return -i/2;
		}
	}
	c=i;
	SortDtuples(L);
	dw=L->num;
	dtp=L->dt+1;
	for(i=1;i<dw;i++,dtp++)
		if(CmpaDtuple(dtp, dtp-1)==0)
			DtuplesDelete(L, i+1, NULL), i--, dw--, dtp--;
	return c/2;
}

int CloneDtuples(DTUPLES* R1, DTUPLES* R2)
{
	DTUPLE *dtp;
	dtp=malloc(R2->memsize*sizeof(DTUPLE));
	if(!dtp)
		return -1;
	R1->dt=dtp;
	R1->num=R2->num;
	R1->memsize=R2->memsize;
	DTUPLE *dtp2=R2->dt, *end=R2->dt+R2->num;
	while(dtp2<end)
		CopyDtuple(dtp, dtp2), dtp++, dtp2++;
	return 0;
}







#endif
