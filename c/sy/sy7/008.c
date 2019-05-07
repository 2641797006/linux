#include <stdio.h>
#include </home/lxll/c/sy7/pGraph.h>
#define NUM 9

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

	InsertArc(G, "$ (1,2)#5, (1,3)#3, (2,4)#1, (2,5)#3, (2,6)#6, (3,5>#8, (3,6)#7, (4,7)#3, (5,7)#5, (5,8)#2, (6,7)#6, (6,8)#6, (7,9)#4, (8,9)#3");
	PrintGraph_ln(G);
	ShortestPath(G, GetVex(G,1), path, cost);
	for(i=0;i<NUM;i++)
		printf("%d ", path[i]+1);
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
