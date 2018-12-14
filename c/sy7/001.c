#include <stdio.h>
#include </home/lxll/c/sy7/pGraph.h>

int func(VertexType *vex)
{
	if(*vex!=1)
		*vex=(*(vex-1)+1);
	return 0;
}

int main()
{
	int i=0, *pi;
	MGraph _G, *G=&_G;
	i=InitGraph(G, 5);
	*G->vexs=1;
	VertexTraverse(G, &func);
	PrintGraph_ln(G);

	SetAdjM(G, "<1,2>, <2,3>, <4,4>, <5,4>, <5,2>, <1,1>");

	PrintGraph_ln(G);

	pi=FirstAdjVex(G, 3);
	if(pi)
		printf("FirstAdjVex=%d\n", *pi);
	else
		puts("None");
	DestroyGraph(G);
}
