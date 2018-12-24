#ifndef _PGRAPH_H_
#define _PGRAPH_H_

#ifndef _STDLIB_H
#include <stdlib.h>
#endif

#ifndef _P_SCAN_H_
#include </home/lxll/c/git/include/p_scan.h>
#endif

#ifndef _PTREE_H_
#include </home/lxll/c/sy7/pTree.h>
#endif

#ifndef VertexType
#define VertexType int
#endif

#define QElemType int
#include </home/lxll/c/git/include/pQueueX.h>
#define lk_q(name)	lk_suffix(name, QElemType)
#define Queue		lk_q(Queue)
#define InitQueue	lk_q(InitQueue)
#define DestroyQueue	lk_q(DestroyQueue)
#define EnQueue		lk_q(EnQueue)
#define DeQueue		lk_q(DeQueue)

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
	G->arcnum=0;
	memset(G->arcs, 0, sizeof(AdjMatrix)*vexnum*vexnum);
	return 0;
}

void DestroyGraph(MGraph *G)
{
	int i, j, n=G->vexnum;
	AdjMatrix *arc=G->arcs;
	free(G->vexs);
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			free((arc+i*n+j)->info);
	free(G->arcs);
	G->vexs=NULL, G->arcs=NULL;
	G->vexnum=0, G->arcnum=0;
}

#define GetVex(G, i) (G->vexs+i-1)
#define GetVex0(G, i) (G->vexs+i)

int PutVex(MGraph *G, int i, VertexType *vex)
{
	if(i<1||i>G->vexnum)
		return -1;
	memcpy(GetVex(G, i), vex, sizeof(VertexType));
	return 0;
}

int VertexTraverse(MGraph *G, int (*visit)(VertexType*,int))
{
	int ret;
	VertexType *vex=G->vexs, *endvex=vex+G->vexnum;
	while(vex<endvex){
		ret=visit(vex,vex-G->vexs+1);
		if(ret)
			return ret;
		vex++;
	}
	return 0;
}

VertexType* FirstAdjVex(MGraph *G, VertexType *vex)
{
	int i, n=G->vexnum;
	AdjMatrix *M=G->arcs+(vex-G->vexs)*n;
	for(i=0;i<n;i++)
		if((M+i)->adj)
			return G->vexs+i;
	return NULL;
}

VertexType* NextAdjVex(MGraph *G, VertexType *vex, VertexType *adjvex)
{
	int i, j, n=G->vexnum;
	j=vex-G->vexs;
	AdjMatrix *M=G->arcs+j*n;
	for(i=j+1;i<n;i++)
		if((M+i)->adj)
			return G->vexs+i;
	return NULL;
}

int SetArc(MGraph *G, const char *dtstr, int weight, InfoType *info)
{
	const char *dts=dtstr;
	DWORD c, dw, flag, i=0, dt[2], dg=0, setw=0;
	AdjMatrix *M=G->arcs, *M_t;
	if(*dts=='$')
		setw=1, dts++;
	for(;;){
		c=*dts++;
		if(!c)
			break;
		if(c=='('){
			dg=1;
			continue;
		}
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
			if(setw)
				if(setw==1){
					dt[1]=dw-1, setw++, i--;
					continue;
				}
				else
					(weight=dw, setw=1);
			else
				dt[1]=dw-1;
			M_t=M+dt[0]*G->vexnum+dt[1];
			if(!M_t->adj&&weight)
				G->arcnum++;
			else if(M_t->adj&&!weight)
				G->arcnum--;
			M_t->adj=weight;
			M_t->info=info;
			if(dg){
				M_t=M+dt[1]*G->vexnum+dt[0];
				if(!M_t->adj&&weight)
					G->arcnum++;
				else if(M_t->adj&&!weight)
					G->arcnum--;
				M_t->adj=weight, dg=0;
				M_t->info=info;
			}
		}
	}
	return i/2;
}

int InsertArc(MGraph *G, char *str)
{
	return SetArc(G, str, 1, NULL);
}

int DeleteArc(MGraph *G, char *str)
{
	return SetArc(G, str, 0, NULL);
}

int DFSTraverse(MGraph *G, int (*visit)(VertexType*))
{
	int i, tmp, n=G->vexnum, visited[n];
	VertexType *vex=G->vexs;
	AdjMatrix *M=G->arcs;
	memset(visited, 0, n*sizeof(int));
	int DFS(int i){
		int j;
		if(!*(visited+i)){
			*(visited+i)=1, tmp=visit(vex+i);
			if(tmp)
				return tmp;
		}
		for(j=0;j<n;j++)
			if((M+i*n+j)->adj&&!*(visited+j))
				if(tmp=DFS(j))
					return tmp;
		return 0;
	}
	for(i=0;i<n;i++)
		if(tmp=DFS(i))
			return tmp;
	return 0;
}

int BFSTraverse(MGraph *G, int (*visit)(VertexType*))
{
	int i, j, k, tmp, n=G->vexnum, visited[n];
	Queue Queue_Q, *Q=&Queue_Q;
	VertexType *vex=G->vexs;
	AdjMatrix *M=G->arcs;
	if(InitQueue(Q))
		return -1;
	memset(visited, 0, n*sizeof(int));
	for(i=0;i<n;i++){
		if(!*(visited+i))
			*(visited+i)=1, EnQueue(Q, i);
		else
			continue;
		while(!DeQueue(Q, &j)){
			if(tmp=visit(vex+j))
				break;
			for(k=0;k<n;k++)
				if((M+j*n+k)->adj&&!*(visited+k))
					*(visited+k)=1, EnQueue(Q, k);
		}	
	}
	DestroyQueue(Q);
	return tmp;
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

TNode* MiniSpanTree(MGraph *G, VertexType *vex)
{
	const int n=G->vexnum;
	int i, j, k;
	AdjMatrix *arc;
	struct{
		int vex;
		int cost;
	}dge[n];
	k=vex-G->vexs;
	arc=G->arcs+k*n;
	for(i=0;i<n;i++){
		(dge+i)->vex=k;
		(dge+i)->cost=(arc+i)->adj;
	}
	(dge+k)->cost=0;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			if( (dge+j)->cost && (!(dge+k)->cost || (dge+k)->cost>(dge+j)->cost))
					k=j;
		printf("(%d,%d), ", (dge+k)->vex, k);
		(dge+k)->cost=0;
		arc=G->arcs+k*n;
		for(j=0;j<n;j++)
			if((arc+j)->adj < (dge+j)->cost)
				(dge+j)->vex=j, (dge+j)->cost=(arc+j)->adj;
	}
}

#undef InitQueue
#undef DestroyQueue
#undef EnQueue
#undef DeQueue

#undef Queue
#undef lk_q
#undef QElemType

#endif
