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
	int tmp;
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

int PrintBiTree(BiTNode* T, int (*visit)(BiTNode*))
{
	int line, tmp, nul;
	Queue Queue_Q, *Q=&Queue_Q;
	if(InitQueue(Q))
		return -1;
	EnQueue(Q, T);
	line=1, nul=1;
	while(!DeQueue(Q, &T)){
		if(line)
			line--;
		else{
			if(!nul)
				break;
			putchar('\n');
			line=QueueLength(Q);
			nul=0;
		}
		tmp=visit(T);
		if(tmp)
			break;
		if(!T){
			EnQueue(Q, NULL);
			EnQueue(Q, NULL);
			continue;
		}
		EnQueue(Q, T->lchild);
		EnQueue(Q, T->rchild);
		if(T->lchild||T->rchild)
			nul=1;
	}
	DestroyQueue(Q);
	return tmp;
}
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
#define CreateBTN(data) CreateBiTNode(data, NULL, NULL)

BiTNode* PreInBiTree(int *pre, int *in, int num)
{
	BiTNode *root;
	int tmp, *endpre, *endin, *p;
	endpre=pre+num-1;
	endin=in+num-1;
	root=CreateBTN(pre);
	for(p=in;p<=endin;p++)
		if(*p==*pre)
			break;
	int PIT(BiTNode *T, int *left, int *center, int *right)
	{
		if(++pre>endpre)
			return 0;
		if(left==right)
			return 1;
		for(p=left;p<center;p++)
			if(*p==*pre){
				T->lchild=CreateBTN(pre);
				tmp=PIT(T->lchild, left, p, center-1);
				if(!tmp)
					return tmp;
				break;
			}
		for(p=center+1;p<=right;p++)
			if(*p==*pre){
				T->rchild=CreateBTN(pre);
				tmp=PIT(T->rchild, center+1, p, right);
				if(!tmp)
					return tmp;
				break;
			}
		return 2;
	}
	PIT(root, in, p, endin);
	return root;
}

BiTNode* InPostBiTree(int *in, int *post, int num)
{
	BiTNode *root;
	int tmp, *endin, *endpost, *p;
	endin=in+num-1;
	endpost=post+num-1;
	root=CreateBTN(endpost);
	for(p=in;p<=endin;p++)
		if(*p==*endpost)
			break;
	int IPT(BiTNode *T, int *left, int *center, int *right)
	{
		if(--endpost<post)
			return 0;
		if(left==right)
			return 1;
		for(p=left;p<center;p++)
			if(*p==*endpost){
				T->lchild=CreateBTN(endpost);
				tmp=IPT(T->lchild, left, p, center-1);
				if(tmp&&tmp<3)
					tmp=IPT(T->lchild, center+1, p, right);
				if(tmp&&tmp<3)
					return 1;
				if(!tmp)
					return tmp;
				return 6;
			}
		for(p=center+1;p<=right;p++)
			if(*p==*endpost){
				T->rchild=CreateBTN(endpost);
				tmp=IPT(T->rchild, center+1, p, right);
				if(tmp&&tmp<3)
					tmp=IPT(T->rchild, left, p, center-1);
				if(tmp&&tmp<3)
					return 1;
				if(!tmp)
					return tmp;
				return 9;
			}
		endpost++;
		return 2;
	}
	IPT(root, in, p, endin);
	return root;
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
