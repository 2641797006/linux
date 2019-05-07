#include <stdio.h>
#include </home/lxll/c/sy7/pGraph.h>
#define NUM 6

int init(VertexType *vex, int i);
int visit(VertexType *vex);
int print(TNode *T);

int main()
{
	int i, j, path[NUM], cost[NUM];
	MGraph _G, *G=&_G;
	InitGraph(G, NUM);
	VertexTraverse(G, &init);

	SetGW(G, DWS_MAX);

	InsertArc(G, "$0 <0,2>#10, <0,4>#30, <0,5>#100, <1,2>#5, <2,3>#50, <3,5>#10, <4,3>#20, <4,5>#60");
	PrintGraph_ln(G);
	ShortestPath(G, GetVex(G,1), path, cost);
	for(i=0;i<NUM;i++)
		printf("%d ", path[i]);
	ln();
	for(i=0;i<NUM;i++)
		printf("%d ", cost[i]);
	ln();

	DestroyGraph(G);
}

int init(VertexType *vex, int i)
{
	*vex=i;
	return 0;
}

int visit(VertexType *vex)
{
	printf("%d ", *vex);
	return 0;
}

int print(TNode *T)
{
	printf("%d ", T->data);
	return 0;
}
