#include <stdio.h>
#include </home/lxll/c/sy6/pBiTNode.h>
#include </home/lxll/c/pctype.h>

int _TREE_;
int SetTree(BiTNode* T);
int PrintBiTNode(BiTNode* T);

int main()
{
	BiTNode *T;
	T=InitBiTree(10);
	_TREE_=1;
	LevelOrderTraverse(T, &SetTree);
	PreOrderTraverse(T, &PrintBiTNode);
	DestroyBiTree(T);
	return 0;
}

int SetTree(BiTNode* T)
{
	T->data=_TREE_++;
	return 0;
}

int PrintBiTNode(BiTNode* T)
{
	printf("T->data=%d\n", T->data);
	printf("T->lchild=0x%016X \nT->rchild=0x%016X\n", T->lchild, T->rchild);
	return 0;
}
