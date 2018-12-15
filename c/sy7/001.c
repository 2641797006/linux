#include <stdio.h>
#include </home/lxll/c/sy7/pGraph.h>

int func(VertexType *vex);
int visit(VertexType *vex);

int main()
{
	int i=0, *pi;
	MGraph _G, *G=&_G;
	i=InitGraph(G, 8);
	*G->vexs=1;
	VertexTraverse(G, &func);
	PrintGraph_ln(G);

	SetAdjM(G, "(1,2), (2,4), (4,8), (5,8), (1,3), (3,7), (6,7)");

	PrintGraph_ln(G);

	BFSTraverse(G, &visit);

	DestroyGraph(G);
}

int func(VertexType *vex)
{
	if(*vex!=1)
		*vex=(*(vex-1)+1);
	return 0;
}

int visit(VertexType *vex)
{
	printf("%d ", *vex);
	return 0;
}
