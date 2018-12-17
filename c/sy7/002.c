#include <stdio.h>
#include </home/lxll/c/sy7/pALGraph.h>

int func(VertexType *vex, int i);
int visit(VertexType *vex);

int main()
{
	int i=0, *pi;
	ALGraph _G, *G=&_G;
	InitGraph(G, 8);
	VertexTraverse(G, &func);
	InsertArc(G, "(1,3), (2,4), (2,5), (3,6), (3,7), (6,7), (4,8), (5,8)");
	PrintGraph(G);
	putchar('\n');
	BFSTraverse(G, &visit);
printf("\narcnum=%d\n", G->arcnum);
	DestroyGraph(G);
}

int func(VertexType *vex, int i)
{
	*vex=i-1;
	return 0;
}

int visit(VertexType *vex)
{
	printf("%d ", *vex+1);
	return 0;
}
