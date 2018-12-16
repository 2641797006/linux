#ifndef _PALGRAPH_H_
#define _PALGRAPH_H_

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

#define QElemType VertexType*
#ifndef _PQUEUE_H_
#include </home/lxll/c/git/include/pQueue.h>
#endif

#ifndef InfoType
#define InfoType int
#endif

typedef struct ArcNode{
	int 		adjvex;
	struct ArcNode 	*nextarc;
	InfoType 	*info;
}ArcNode;

typedef struct{
	VertexType 	data;
	ArcNode 	*firstarc;
}AdjList;

typedef struct{
	AdjList	*vertices;
	int vexnum, arcnum;
}ALGraph;

int InitGraph(ALGraph *G, int vexnum)
{
	G->vertices=malloc(vexnum*sizeof(AdjList));
	if(!G->vertices)
		return -1;
	memset(G->vertices, 0, vexnum*sizeof(AdjList));
	G->vexnum=vexnum;
	G->arcnum=0;
	return 0;
}

void DestroyGraph(ALGraph *G)
{
	free(G->vertices);
	G->vertices=NULL;
	G->vexnum=0;
	G->arcnum=0;
}












#endif
