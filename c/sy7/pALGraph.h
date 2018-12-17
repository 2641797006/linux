#ifndef _PALGRAPH_H_
#define _PALGRAPH_H_

#ifndef _STDLIB_H
#include <stdlib.h>
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
	AdjList *L=G->vertices, *endL=L+G->vexnum;
	ArcNode *arc, *arc_t;
	while(L<endL){
		arc=L->firstarc;
		while(arc){
			free(arc->info);
			arc_t=arc;
			arc=arc->nextarc;
			free(arc_t);
		}
		L++;
	}
	free(G->vertices);
	G->vertices=NULL;
	G->vexnum=0;
	G->arcnum=0;
}

#define GetVex(G, i)	( & ( G->vertices+i-1 )->data )
#define GetVex0(G, i)	( & ( G->vertices+i )->data )

int PutVex(ALGraph *G, int i, VertexType *vex)
{
	if(i<1||i>G->vexnum)
		return -1;
	memcpy(GetVex(G, i), vex, sizeof(VertexType));
	return 0;
}

int VertexTraverse(ALGraph *G, int (*visit)(VertexType*,int))
{
	int ret;
	AdjList *L=G->vertices, *endL=L+G->vexnum;
	while(L<endL){
		ret=visit(&L->data, L-G->vertices+1);
		if(ret)
			return ret;
		L++;
	}
	return 0;
}

VertexType* NextAdjVex(ALGraph *G, VertexType *vex, VertexType *adjvex)
{
	AdjList *L=G->vertices;
	ArcNode *arc;
	arc=*(ArcNode**)( (void*)vex + ( (void*)(&L->firstarc) - (void*)(&L->data) ) );
	if(arc&&!adjvex)
		return GetVex0(G, arc->adjvex);
	while(arc){
		if( GetVex0(G, arc->adjvex)==adjvex && arc->nextarc )
			return GetVex0(G, arc->nextarc->adjvex);
		else
			return NULL;
		arc=arc->nextarc;
	}
	return NULL;
}

VertexType* FirstAdjVex(ALGraph *G, VertexType *vex)
{
	return NextAdjVex(G, vex, NULL);
}

int SetArc_N(ALGraph *G, int v1, int v2, int add_del, InfoType *info)
{
	v1--, v2--;
	ArcNode *arc, *arc_t=NULL, *arc_n;
	AdjList *L=G->vertices+v1;
	arc=L->firstarc;
	while(arc){
		if(arc->adjvex<=v2)
			break;
		arc_t=arc;
		arc=arc->nextarc;
	}
	if(!add_del)
		if(arc && arc->adjvex==v2){
			if(arc_t)
				arc_t->nextarc=arc->nextarc;
			else
				L->firstarc=arc->nextarc;
			free(arc->info);
			free(arc);
			return 0;
		}
		else
			return -1;
	if(arc && arc->adjvex==v2)
		return -2;
	arc_n=malloc(sizeof(ArcNode));
	if(!arc_n)
		return -3;
	arc_n->adjvex=v2, arc_n->nextarc=arc, arc_n->info=info;
	if(arc_t)
		arc_t->nextarc=arc_n;
	else
		L->firstarc=arc_n;
	return 0;
}

int SetAdjL_O(ALGraph *G, char *dtstr, int add_del, InfoType *info)
{
	char *dts=dtstr;
	DWORD c, dw, flag, i=0, dt[2], dg=0;
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
			dt[0]=dw;
		else{
			dt[1]=dw;
			c=SetArc_N(G, dt[0], dt[1], add_del, info);
			if(c)
				return c;
			if(dg){
				c=SetArc_N(G, dt[1], dt[0], add_del, info), dg=0;
				if(c)
					return c;
			}
		}
	}
	return i/2;
}
























#endif
