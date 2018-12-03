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

int PowDtuples(MANIFD* E, DTUPLES* R, int n, DTUPLES* Rn)
{
	int i;
	DTUPLE dt;
	DTUPLES dts_S, *S=&dts_S;
	InitDtuples(S);
	for(i=0;i<E->num;i++){
		dt.e1=*(E->data+i), dt.e2=dt.e1;
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











#endif
