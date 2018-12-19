#ifndef _PBITNODE_H_
#define _PBITNODE_H_

#ifndef _STDLIB_H
#include <stdlib.h>
#endif

#ifndef _PCTYPE_H_
#include </home/lxll/c/pctype.h>
#endif

#ifndef TElemType
#define TElemType int
#endif

typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode;

#ifndef _PQUEUE_H_
#define QElemType BiTNode*
#include </home/lxll/c/git/include/pQueue.h>
#endif

BiTNode* InitBiTree(int n)
{
	int i, t;
	BiTNode* p;
	if(n<1||!(p=malloc(sizeof(BiTNode))))
		return NULL;
	n++, t=n, i=1;
	while(t)
		t>>=1, i<<=1;
	i>>=2, t=n&i;
	p->lchild=InitBiTree(i+(t ? t : n&(i-1))-1);
	p->rchild=InitBiTree(i+(t ? n&(i-1) : 0)-1);
	return p;
}

void DestroyBiTree(BiTNode* T)
{
	if(!T)
		return;
	DestroyBiTree(T->lchild);
	DestroyBiTree(T->rchild);
	free(T);
}

int PreOrderTraverse(BiTNode* T, int (*visit)(BiTNode*))
{
	int ret;
	int do_PreOrderTraverse(BiTNode* T)
	{
		if(!T)
			return 0;
		if(ret=visit(T))
			return ret;
		if(ret=do_PreOrderTraverse(T->lchild))
			return ret;
		if(ret=do_PreOrderTraverse(T->rchild))
			return ret;
		return 0;
	}
	return do_PreOrderTraverse(T);
}
#define PreOrderTraverse_ln(T, visit) ( PreOrderTraverse(T, visit), putchar('\n') )

int InOrderTraverse(BiTNode* T, int (*visit)(BiTNode*))
{
	int ret;
	int do_InOrderTraverse(BiTNode* T)
	{
		if(!T)
			return 0;
		if(ret=do_InOrderTraverse(T->lchild))
			return ret;
		if(ret=visit(T))
			return ret;
		if(ret=do_InOrderTraverse(T->rchild))
			return ret;
		return 0;
	}
	return do_InOrderTraverse(T);
}
#define InOrderTraverse_ln(T, visit) ( InOrderTraverse(T, visit), putchar('\n') )

int PostOrderTraverse(BiTNode* T, int (*visit)(BiTNode*))
{
	int ret;
	int do_PostOrderTraverse(BiTNode* T)
	{
		if(!T)
			return 0;
		if(ret=do_PostOrderTraverse(T->lchild))
			return ret;
		if(ret=do_PostOrderTraverse(T->rchild))
			return ret;
		if(ret=visit(T))
			return ret;
		return 0;
	}
	return do_PostOrderTraverse(T);
}
#define PostOrderTraverse_ln(T, visit) ( PostOrderTraverse(T, visit), putchar('\n') )

int LevelOrderTraverse(BiTNode* T, int (*visit)(BiTNode*))
{
	int i, j, tmp;
	BiTNode *T1;
	Queue Queue_Q, *Q=&Queue_Q;
	if(InitQueue(Q))
		return -1;
	EnQueue(Q, T);
	while(!DeQueue(Q, &T)){
		tmp=visit(T);
		if(tmp)
			break;
		if(T->lchild)
			EnQueue(Q, T->lchild);
		if(T->rchild)
			EnQueue(Q, T->rchild);
	}
	DestroyQueue(Q);
	return tmp;
}
#define LevelOrderTraverse_ln(T, visit) ( LevelOrderTraverse(T, visit), putchar('\n') )

BiTNode* CreateBiTNode(TElemType* data, BiTNode* lchild, BiTNode* rchild)
{
	BiTNode* T=malloc(sizeof(BiTNode));
	if(!T)
		return NULL;
	if(data)
		CopyElem(&T->data, data);
	T->lchild=lchild;
	T->rchild=rchild;
	return T;
}


/*

 3 2 1 0x0011
 4 2 2 0x0100
 5 3 2 0x0101
 6 4 2 0x0110
 7 4 3 0x0111
 8 4 4 0x1000
 9 5 4 0x1001
10 6 4 0x1010
11 7 4 0x1011
12 8 4 0x1100
13 8 5 0x1101
14 8 6 0x1110
15 8 7 0x1111
16 8 8 0x10000

*/

#endif
