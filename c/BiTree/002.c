#include <stdio.h>
#include </home/lxll/c/BiTree/pBiTNode.h>

int _;
int init(BiTNode *T);
int print(BiTNode *T);

int main()
{
	int i;
	int pre[]={1, 2, 4, 8, 9, 5, 10, 3, 6, 7};
	int in[]={8, 4, 9, 2, 10, 5, 1, 6, 3, 7};
	BiTNode BT_T, *T=&BT_T, *T1;

	T=PreInBiTree(pre, 10, in, 10);
	PreOrderTraverse_ln(T, &print);
	InOrderTraverse_ln(T, &print);
	LevelOrderTraverse_ln(T, &print);
	DestroyBiTree(T);
}

int init(BiTNode *T)
{
	T->data=++_;
	return 0;
}

int print(BiTNode *T)
{
	printf("%d ", T->data);
	return 0;
}
