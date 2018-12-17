#include <stdio.h>
#include </home/lxll/c/sy7/pALGraph.h>

int func(VertexType *vex, int i);

int main()
{
	int i=0, *pi;
	ALGraph _G, *G=&_G;
	InitGraph(G, 8);
	VertexTraverse(G, &func);
	InsertArc(G, "(4,7), (4,3), (2,5), (2,3), (2,4), (2,2)");
	PrintGraph(G);
printf("Fadj=%d\n", *FirstAdjVex(G, GetVex(G, 3)));
printf("NextAdj=%d\n", *NextAdjVex(G, GetVex(G, 3), FirstAdjVex(G, GetVex(G, 3))));
	DestroyGraph(G);
}

int func(VertexType *vex, int i)
{
	*vex=i-1;
	return 0;
}
