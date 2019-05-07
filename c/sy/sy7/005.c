#include <stdio.h>
#include </home/lxll/c/sy7/pALGraph.h>
#include </home/lxll/c/sy7/pTree.h>
int init(VertexType *vex, int i);
int print(VertexType *vex);
int visit(VertexType *vex);
int printT(TNode* T);

int main()
{
	int i=0;
	ALGraph _G, *G=&_G;
	TNode *T;
	InitGraph(G, 13);
	VertexTraverse(G, &init);
	InsertArc(G, "(1,2), (1,3), (1,6), (1,12), (2,13), (4,5), (7,8), (7,9), (7,11), (8,11), (10,12), (10,13), (12,13)");
	PrintGraphI0(G);
	ln();
	BFSTraverse(G, &print);
	ln();
	T=DFSTree(G);
PRINT_STR("Level: ");
LevelOrderTraverse(T, &printT);
	ln();
PRINT_STR("Pre: ");
	PreOrderTraverse(T, &printT);
	ln();
PRINT_STR("In: ");
	InOrderTraverse(T, &printT);
	ln();
PRINT_STR("Post: ");
	PostOrderTraverse(T, &printT);
	ln();
ln();
	PrintTree(T, &printT);
	ln();
	DestroyGraph(G);
	DestroyTree(T);
}

int visit(VertexType *vex)
{
	if(vex)
		;
	else
		;
	return 0;
}

int init(VertexType *vex, int i)
{
	*vex=i-1;
	return 0;
}

int print(VertexType *vex)
{
	if(vex)
		printf("%d ", *vex+1);
	else
		putchar(','), putchar(' ');
	return 0;
}

int printT(TNode* T)
{
	if(T)
		printf("%d ", T->data+1);
	else
		ln();
	return 0;
}
