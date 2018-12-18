#include <stdio.h>
#include </home/lxll/c/sy7/pALGraph.h>

int func(VertexType *vex, int i);
int visit(VertexType *vex);

int main()
{
	int i=0, *pi;
	ALGraph _G, *G=&_G;
	InitGraph(G, 13);
	VertexTraverse(G, &func);
	InsertArc(G, "(1,2), (1,3), (1,6), (1,12), (2,13), (4,5), (7,8), (7,9), (7,11), (8,11), (10,12), (10,13), (12,13)");
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
	if(vex)
		printf("%c ", *vex+'A');
	else
		putchar(','), putchar(' ');
	return 0;
}
