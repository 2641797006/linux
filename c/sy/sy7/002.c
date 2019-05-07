#include <stdio.h>
#include </home/lxll/c/sy7/pGraph.h>

#define NUM 6
int init(VertexType *vex, int i);
int visit(VertexType *vex);
int print(TNode *T);

int main()
{
	int i, path[NUM];
	MGraph _G, *G=&_G;
	InitGraph(G, NUM);
	VertexTraverse(G, &init);

	InsertArc(G, "<1,2>, <1,3>, <1,4>, <2,5>, <3,5>, <4,5>, <6,4>, <6,5>");
	PrintGraph_ln(G);
	
	TopoSort(G, path);
	for(i=0;i<NUM;i++)
		printf("%d ", path[i]+1);
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
