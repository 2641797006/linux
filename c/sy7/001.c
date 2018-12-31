#include <stdio.h>
#include </home/lxll/c/sy7/pGraph.h>

int init(VertexType *vex, int i);
int visit(VertexType *vex);
int print(TNode *T);

int main()
{
	TNode *T;
	MGraph _G, *G=&_G;
	InitGraph(G, 6);
	VertexTraverse(G, &init);

	SetGW(G, DWS_MAX);
	PrintGraph_ln(G);

	InsertArc(G, "$(1,2)#6, (1,3)#1, (1,4)#5, (2,3)#5, (2,5)#3, (3,4)#5, (3,5)#6, (3,6)#4, (4,6)#2, (5,6)#6");
	PrintGraph_ln(G);

T=MiniSpanTree(G, GetVex(G,2));
ln();
PrintTree(T, &print);
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
