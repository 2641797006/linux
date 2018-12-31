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
	InitGraph(G, 8);
	VertexTraverse(G, &init);
	InsertArc(G, "(1,2), (1,3), (2,4), (2,5), (4,8), (5,8), (3,6), (3,7), (6,7)");
	PrintGraph(G);
	ln();
	BFSTraverse(G, &print);
	ln();
	T=DFSTree(G);
	LevelOrderTraverse(T, &printT);
	ln();
	PreOrderTraverse(T, &printT);
	ln();
	InOrderTraverse(T, &printT);
	ln();
	PostOrderTraverse(T, &printT);
	ln();
T->child->sibling->sibling=CreateTN(&i);
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
