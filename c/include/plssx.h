#ifndef _PLSSX_H_
#define _PLSSX_H_

#ifndef _MALLOC_H
#include <malloc.h>
#endif

#ifndef _PLOGIC_H_
#include </home/lxll/c/git/include/plogic.h>
#endif

#ifndef _PMANIFD_H_
#include </home/lxll/c/git/include/pmanifd.h>
#endif

#ifndef _PDTUPLES_H_
#include </home/lxll/c/git/include/pdtuples.h>
#endif

DTUPLES* Dcarp(MANIFD* A, MANIFD* B, DTUPLES* R)
{
	int i, j;
	DTUPLE dt;
	DTUPLES *dts;
	if(R)
		dts=R;
	else{
		dts=malloc(sizeof(DTUPLES));
		if(!dts)
			return NULL;
		InitDtuples(dts);
	}
	for(i=0;i<A->num;i++)
		for(j=0;j<B->num;j++){
			dt.e1=*(A->data+i), dt.e2=*(B->data+j);
			if(DtuplesInsert(dts, dts->num+1, &dt))
				return NULL;
		}
	return dts;
}

void RevDtuples(DTUPLES* R)
{
	int tmp;
	DTUPLE *dt, *end;
	dt=R->dt;
	end=dt+R->num;
	while(dt<end)
		tmp=dt->e1, dt->e1=dt->e2, dt->e2=tmp, dt++;
}

int CmpsDtuples_O(DTUPLES* R, DTUPLES* S, DTUPLES* RS)
{
	DTUPLE dt, *r, *s, *endr, *ends;
	endr=R->dt+R->num, ends=S->dt+S->num;
	RS->num=0;
	for(r=R->dt;r<endr;r++)
		for(s=S->dt;s<ends;s++)
			if(r->e2==s->e1){
				dt.e1=r->e1, dt.e2=s->e2;
				if(DtuplesInsert(RS, RS->num+1, &dt))
					return -1;
			}
	return 0;
}

#define CmpsDtuples(R, S, RS) (CmpsDtuples_O(R, S, RS), SetDtuples(RS, ""))

int PowDtuples(MANIFD* A, DTUPLES* R, int n, DTUPLES* Rn)
{
	int i;
	DTUPLE dt;
	DTUPLES dts_S, *S=&dts_S;
	InitDtuples(S);
	for(i=0;i<A->num;i++){
		dt.e1=*(A->data+i), dt.e2=dt.e1;
		if(DtuplesInsert(S, S->num+1, &dt))
			-1;
	}
	for(i=0;i<n;i++){
		CmpsDtuples(R, S, Rn);
		DestroyDtuples(S);
		CloneDtuples(S, Rn);
	}
	DestroyDtuples(Rn);
	CloneDtuples(Rn, S);
	DestroyDtuples(S);
	return 0;
}

#define ManifdR_I(A, R) PowDtuples(A, NULL, 0, R)

int ManifdR_E(MANIFD* A, DTUPLES* R)
{
	int i, j, n=A->num, *p=A->data;
	DTUPLE dt;
	R->num=0;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++){
			dt.e1=*(p+i);
			dt.e2=*(p+j);
			if(DtuplesInsert(R, i*n+j+1, &dt))
				return -1;
		}
	return 0;
}

int DtuplesContain(DTUPLES* A, DTUPLES* B)
{
	int i, n=0;
	DTUPLE *a, *b, *enda, *endb;
	enda=A->dt+A->num, endb=B->dt+B->num;
	for(a=A->dt;a<enda;a++)
		for(b=B->dt;b<endb;b++){
			i=CmpaDtuple(a, b);
			if(i<=0){
				i ? 0 : n++;
				break;
			}
		}
	return n;
}

int UnionDtuples(DTUPLES* Ru, DTUPLES* R)
{
	DTUPLE *r=R->dt, *endr=r+R->num;
	for(;r<endr;r++)
		if(DtuplesInsert(Ru, Ru->num+1, r))
			return -1;
	SetDtuples(Ru, "");
	return 0;
}

int IsReflexive(MANIFD* A, DTUPLES* R)
{
	int i;
	DTUPLES dts_S, *S=&dts_S;
	InitDtuples(S);
	ManifdR_I(A, S);
	i=DtuplesContain(S, R);
	DestroyDtuples(S);
	if(i==A->num)
		return 1;
	if(i==0)
		return 0;
	return -1;
}
	
int IsSymmetry(MANIFD* A, DTUPLES* R)
{
	int i, j;
	DTUPLES dts_S, dts_T, *S=&dts_S, *T=&dts_T;
	InitDtuples(S);
	ManifdR_I(A, S);
	CloneDtuples(T, R);
	RevDtuples(T);
	i=DtuplesContain(T, R);
	j=DtuplesContain(S, R);
	DestroyDtuples(S);
	DestroyDtuples(T);
	if(i==R->num)
		return 1;
	if(i==j)
		return 0;
	return -1;
}

int IsTransfer_O(DTUPLES* R)
{
	int i;
	DTUPLE *base, *end, *p1, *p2, *p3, dt;
	base=R->dt;
	end=base+R->num;
	for(p1=base;p1<end;p1++)
		for(p2=base;p2<end;p2++)
			if(p1->e2==p2->e1){
				dt.e1=p1->e1, dt.e2=p2->e2;
				for(p3=base;p3<end;p3++)
					if(!(i=CmpaDtuple(&dt, p3)))
						break;
				if(i)
					return 0;
			}
	return 1;
}

#define IsTransfer(A, R) IsTransfer_O(R)

int IsEquivalent(MANIFD* A, DTUPLES* R)
{
	if(IsReflexive(A, R)!=1)
		return 0;
	if(IsSymmetry(A, R)!=1)
		return 0;
	if(IsTransfer(A, R)!=1)
		return 0;
	return 1;
}

#define IsEqu(A, R) IsEquivalent(A, R)

int Closure_r(MANIFD* A, DTUPLES* R)
{
	int i=0;
	DTUPLES dts_R0, *R0=&dts_R0;
	InitDtuples(R0);
	ManifdR_I(A, R0);
	if(UnionDtuples(R, R0))
		i=-1;
	DestroyDtuples(R0);
	return i;
}

int Closure_s_O(DTUPLES* R)
{
	int i=0;
	DTUPLES dts_S, *S=&dts_S;
	CloneDtuples(S, R);
	RevDtuples(S);
	if(UnionDtuples(R, S))
		i=-1;
	DestroyDtuples(S);
	return i;
}

#define Closure_s(A, R) Closure_s_O(R)

int Closure_t(MANIFD* A, DTUPLES* R)
{
	int i, n=A->num;
	DTUPLES dts_S, dts_R1, dts_Rn, *S=&dts_S, *R1=&dts_R1, *Rn=&dts_Rn;
	CloneDtuples(S, R);
	CloneDtuples(R1, R);
	InitDtuples(Rn);
	for(i=2;i<=n;i++){
		CmpsDtuples(S, R1, Rn);
		DestroyDtuples(S);
		CloneDtuples(S, Rn);
		UnionDtuples(R, S);
	}
	DestroyDtuples(S);
	DestroyDtuples(R1);
	DestroyDtuples(Rn);
	return 0;
}

int RelaDtuples(MANIFD* A, DTUPLES* R, int (*visit)(int, int))
{
	int *i, *j, *enda=A->data+A->num;
	DTUPLE dt;
	R->num=0;
	for(i=A->data;i<enda;i++)
		for(j=A->data;j<enda;j++)
			if(!visit(*i, *j)){
				dt.e1=*i, dt.e2=*j;
				if(DtuplesInsert(R, R->num+1, &dt))
					return -1;
			}
	return 0;
}


#endif
