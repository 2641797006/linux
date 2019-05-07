#include <stdio.h>
#include </home/lxll/c/sy7/pGraph.h>
#define NUM 13

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

	InsertArc(G, "$ (1,3)#750, (1,9)#180, (1,11)#470, (2,6)#660, (2,8)#200, (2,11)#330, (2,12)#640, (3,6)#780, (4,7)#420, (4,8)#70, (5,7)#390, (5,10)#790, (5,11)#360, (5,13)#560, (6,7)#510, (6,10)#790, (7,10)#90, (7,12)#160, (9,10)#460, (9,11)#600, (9,12)#480, (10,12)#360, (11,12)#290, (12,13)#10");
	PrintGraph_ln(G);
	ShortestPath(G, GetVex(G,2), path, cost);
//	for(i=0;i<NUM;i++)
//		printf("%d ", path[i]+1);
//	ln();
	PrintSEPath(G, path, 1);
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
