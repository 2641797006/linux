#include <stdio.h>
#include </home/lxll/c/sy7/pGraph.h>

int main()
{
	int i=0;
	MGraph _G, *G=&_G;
	i=InitGraph(G, 5);
	printf("i=%d\n", i);
	PrintMatrix_ln(G->arcs);

	SetAdjM(G, "<1,2>, <2,3>, <4,4>, <3,4>, <2,2>");

	PrintMatrix_ln(G->arcs);
	DestroyGraph(G);
}
