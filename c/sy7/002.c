#include <stdio.h>
#include </home/lxll/c/sy7/pALGraph.h>

int func(VertexType *vex, int i);
int visit(VertexType *vex, int i);

int main()
{
	int i=0, *pi;
	ALGraph _G, *G=&_G;
	i=InitGraph(G, 8);
printf("i=%d\n", i);
VertexTraverse(G, &func);
VertexTraverse(G, &visit);
putchar('\n');

ArcNode *N, *N1;
N=malloc(1*sizeof(ArcNode));
N1=malloc(sizeof(ArcNode));
(G->vertices+2)->firstarc=N;
N->adjvex=5;N->nextarc=N1;
N1->adjvex=2;N1->nextarc=NULL;
printf("Fadj=%d\n", *FirstAdjVex(G, GetVex(G, 3)));
printf("NextAdj=%d\n", *NextAdjVex(G, GetVex(G, 3), FirstAdjVex(G, GetVex(G, 3))));
	DestroyGraph(G);
}

int func(VertexType *vex, int i)
{
	*vex=i+3;
	return 0;
}

int visit(VertexType *vex, int i)
{
	printf("%d ", *vex);
	return 0;
}
