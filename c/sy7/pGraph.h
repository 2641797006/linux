#ifndef _PGRAPH_H_
#define _PGRAPH_H_

#ifndef _STDLIB_H
#include <stdlib.h>
#endif

#ifndef _PSQLIST_H_
#include </home/lxll/c/git/include/pSqList.h>
#endif

#ifndef _P_SCAN_H_
#include </home/lxll/c/git/include/p_scan.h>
#endif

#ifndef VertexType
#define VertexType int
#endif

#ifndef InfoType
#define InfoType int
#endif

typedef struct{
	int adj;
	InfoType *info;
}AdjMatrix;

typedef struct{
	VertexType *vexs;
	AdjMatrix *arcs;
	int vexnum, arcnum;
}MGraph;

int InitGraph(MGraph *G, int vexnum)
{
	G->vexs=malloc(vexnum*sizeof(VertexType));
	G->arcs=malloc(sizeof(AdjMatrix)*vexnum*vexnum);
	if(!G->vexs||!G->arcs)
		return -1;
	G->vexnum=vexnum;
	memset(G->arcs, 0, sizeof(AdjMatrix)*vexnum*vexnum);
	return 0;
}

void DestroyGraph(MGraph *G)
{
	free(G->vexs);
	free(G->arcs);
	G->vexs=NULL, G->arcs=NULL;
	G->vexnum=0, G->arcnum=0;
}

#define GetVex(G, i) (G->vexs+i-1)

int PutVex(MGraph *G, int i, VertexType *vex)
{
	if(i<1||i>G->vexnum)
		return -1;
	memcpy(G->vexs+i-1, vex, sizeof(VertexType));
	return 0;
}

int VertexTraverse(MGraph *G, int (*visit)(VertexType*))
{
	return SqListTraverse(G->vexs, G->vexnum, (VISIT)visit);
}

VertexType* FirstAdjVex(MGraph *G, int i)
{
	int j, n=G->vexnum;
	AdjMatrix *M=G->arcs+(i-1)*n;
	for(j=0;j<n;j++)
		if((M+j)->adj)
			return G->vexs+j;
	return NULL;
}

int SetAdjM(MGraph *G, char *dtstr)
{
	char *dts=dtstr;
	DWORD c, dw, flag, i=0, dt[2];
	AdjMatrix *M=G->arcs;
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
			dt[0]=dw-1;
		else{
			dt[1]=dw-1;
			(M+dt[0]*G->vexnum+dt[1])->adj=1;
		}
	}
	return i/2;
}

void PrintAdjMatrix(AdjMatrix *M, int n)
{
	int i, j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			printf("%-8d", (M+i*n+j)->adj);
		putchar('\n');
	}
}
#define PrintAdjM(G) PrintAdjMatrix(G->arcs, G->vexnum)
#define PrintAdjM_ln(G) ( PrintAdjM(G), putchar('\n') )

void PrintGraph_O(MGraph *G, int (*PrintVertex)(VertexType*))
{
	int i, n=G->vexnum;
	printf("Vertex: ");
	for(i=0;i<n;i++){
		if(PrintVertex)
			PrintVertex(G->vexs+i);
		else
			printf("%d ", *(G->vexs+i));
	}
	putchar('\n');
	PrintAdjM(G);
}
#define PrintGraph(G) PrintGraph_O(G, NULL)
#define PrintGraph_ln(G) ( PrintGraph(G), putchar('\n') )


























#endif
