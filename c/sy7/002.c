#include <stdio.h>
#include </home/lxll/c/sy7/pALGraph.h>

int func(VertexType *vex);
int visit(VertexType *vex);

int main()
{
	int i=0, *pi;
	ALGraph _G, *G=&_G;
	i=InitGraph(G, 8);
printf("i=%d\n", i);
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
