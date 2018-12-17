#include <stdio.h>
#include </home/lxll/c/sy7/pGraph.h>

int func(VertexType *vex, int i);
int visit(VertexType *vex);

int main()
{
	int i=0, *pi;
	MGraph _G, *G=&_G;
	i=InitGraph(G, 8);
	*G->vexs=1;
	VertexTraverse(G, &func);
	PrintGraph_ln(G);

	SetAdjM(G, "(1,2), (1,3), (2,4), (2,5), (4,8), (5,8), (3,6), (3,7), (6,7), <2,3>");

//	DeleteArc(G, "<1,2>");
	PrintGraph_ln(G);

	DFSTraverse(G, &visit);
printf("arcnum=%d\n", G->arcnum);
	DestroyGraph(G);
}

int func(VertexType *vex, int i)
{
	*vex=i;
	return 0;
}

int visit(VertexType *vex)
{
	printf("%d ", *vex);
	return 0;
}
