#ifndef _PGRAPH_H_
#define _PGRAPH_H_

#ifndef _PMATRIX_H_
#include </home/lxll/c/git/include/pMatrix.h>
#endif

#ifndef _P_SCAN_H_
#include </home/lxll/c/git/include/p_scan.h>
#endif

#ifndef VertexType
#define VertexType int
#endif

typedef struct{
	VertexType *vexs;
	MATRIX *arcs;
	int vexnum, arcnum;
}MGraph;

int InitGraph(MGraph *G, int vexnum)
{
	G->vexs=malloc(vexnum*sizeof(VertexType));
	G->arcs=malloc(sizeof(MATRIX));
	if(!G->vexs||!G->arcs||InitMatrix(G->arcs, vexnum, vexnum))
		return -1;
	G->vexnum=vexnum;
	MatrixZero(G->arcs);
	return 0;
}

void DestroyGraph(MGraph *G)
{
	free(G->vexs);
	DestroyMatrix(G->arcs);
	free(G->arcs);
}

int SetAdjM(MGraph *G, char *dtstr)
{
	char *dts=dtstr;
	DWORD c, dw, flag, i=0, dt[2];
	double **bp=G->arcs->bp;
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
			dt[0]=dw;
		else{
			dt[1]=dw;
			*(*(bp+dt[0]-1)+dt[1]-1)=1;
		}
	}
	return i/2;
}
































#endif
