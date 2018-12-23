#ifndef _PTREE_H_
#define _PTREE_H_

#ifndef _STDLIB_H
#include <stdlib.h>
#endif

#ifndef _PCTYPE_H_
#include </home/lxll/c/git/include/pctype.h>
#endif

#ifndef TElemType
#define TElemType int
#endif

typedef struct TNode{
	TElemType data;
	struct TNode *child, *sibling;
}TNode, *TNode_P;

#define QElemType TNode_P
#include </home/lxll/c/git/include/pQueueX.h>
#define lk_q(name)	lk_suffix(name, QElemType)
#define Queue		lk_q(Queue)
#define InitQueue	lk_q(InitQueue)
#define DestroyQueue	lk_q(DestroyQueue)
#define EnQueue		lk_q(EnQueue)
#define DeQueue		lk_q(DeQueue)

TNode* CreateTN(TElemType *data)
{
	TNode *T=malloc(sizeof(TNode));
	if(!T)
		return NULL;
	memcpy(&T->data, data, sizeof(TElemType));
	T->child=NULL;
	T->sibling=NULL;
	return T;
}

int LevelOrderTraverse(TNode *T, int (*visit)(TNode*))
{
	int tmp=0;
	Queue Queue_Q, *Q=&Queue_Q;
	if(InitQueue(Q))
		return -1;
	EnQueue(Q, T);
	while(!DeQueue(Q, &T)){
		tmp=visit(T);
		if(tmp)
			break;
		if(T->child){
			T=T->child;
			EnQueue(Q, T);
			while(T->sibling)
				T=T->sibling, EnQueue(Q, T);
		}
	}
	DestroyQueue(Q);
	return tmp;
}

#undef InitQueue
#undef DestroyQueue
#undef EnQueue
#undef DeQueue

#undef Queue
#undef lk_q
#undef QElemType

#endif
