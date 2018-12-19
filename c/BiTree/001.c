#include <stdio.h>
#include </home/lxll/c/BiTree/pBiTNode.h>

int _;
int init(BiTNode *T);
int print(BiTNode *T);

int main()
{
	int i;
	BiTNode BT_T, *T=&BT_T, *T1;
	T=InitBiTree(10);
	_=0, LevelOrderTraverse(T, &init);
	PreOrderTraverse_ln(T, &print);
	InOrderTraverse_ln(T, &print);
	PostOrderTraverse_ln(T, &print);
	LevelOrderTraverse_ln(T, &print);
//	DestroyBiTree(T);

	i=666;
	T1=CreateBiTNode(&i, T, T);
	LevelOrderTraverse_ln(T1, &print);
	DestroyBiTree(T1);
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
