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
#define QueueLength	lk_q(QueueLength)

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

void DestroyTree(TNode *T)
{
	if(!T)
		return;
	DestroyTree(T->child);
	DestroyTree(T->sibling);
	free(T);
}

int PreOrderTraverse(TNode *T, int (*visit)(TNode*))
{
	int tmp;
	int do_PreOrderTraverse(TNode *T)
	{
		if(!T)
			return 0;
		if(tmp=visit(T))
			return tmp;
		if(tmp=do_PreOrderTraverse(T->child))
			return tmp;
		if(tmp=do_PreOrderTraverse(T->sibling))
			return tmp;
		return 0;
	}
	return do_PreOrderTraverse(T);
}

int InOrderTraverse(TNode *T, int (*visit)(TNode*))
{
	int tmp;
	int do_InOrderTraverse(TNode *T)
	{
		if(!T)
			return 0;
		if(tmp=do_InOrderTraverse(T->child))
			return tmp;
		if(tmp=visit(T))
			return tmp;
		if(tmp=do_InOrderTraverse(T->sibling))
			return tmp;
		return 0;
	}
	return do_InOrderTraverse(T);
}

int PostOrderTraverse(TNode *T, int (*visit)(TNode*))
{
	int tmp;
	int do_PostOrderTraverse(TNode *T)
	{
		if(!T)
			return 0;
		if(tmp=do_PostOrderTraverse(T->child))
			return tmp;
		if(tmp=do_PostOrderTraverse(T->sibling))
			return tmp;
		if(tmp=visit(T))
			return tmp;
		return 0;
	}
	return do_PostOrderTraverse(T);
}

int LevelOrderTraverse(TNode *T, int (*visit)(TNode*))
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

int PrintTree(TNode *T, int (*PrintTNode)(TNode*))
{
	int tmp, line, flag=0;
	const int fl=0x100, fc=0x10, fr=0x1;
	Queue Queue_Q, *Q=&Queue_Q;
	if(InitQueue(Q))
		return -1;
	putchar('{');
	EnQueue(Q, T);
	EnQueue(Q, NULL);
	line=2, flag|=fl;
	while(!DeQueue(Q, &T)){
		if(line)
			line--;
		else{
			putchar('\n');
			line=QueueLength(Q);
		}
		if(T){
			flag&fc ?: (flag|=fc);
			if(tmp=PrintTNode(T))
				break;
		}
		else{
			if(flag&fl){
				if(flag&fc)
					putchar('\b');
				putchar('}'), putchar(' ');
				flag=0;
			}
			else
				putchar('{'), flag|=fl;
			continue;
		}
		EnQueue(Q, NULL);
		if(T->child){
			T=T->child;
			EnQueue(Q, T);
			while(T->sibling)
				T=T->sibling, EnQueue(Q, T);
		}
		EnQueue(Q, NULL);
	}
	DestroyQueue(Q);
	return tmp;
}

#undef InitQueue
#undef DestroyQueue
#undef EnQueue
#undef DeQueue
#undef QueueLength

#undef Queue
#undef lk_q
#undef QElemType

#endif
