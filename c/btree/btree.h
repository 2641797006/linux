#ifndef _BTREE_H_
#define _BTREE_H_

#ifndef KeyType
#define KeyType int
#endif

#ifndef _STDLIB_H
#include <stdlib.h>
#endif

#ifndef _MEMORY_H
#include <memory.h>
#endif

#define MAX_T	4
#define MIN_T	((MAX_T+1)/2)

typedef struct BTNode{
	int		keynum;
	struct BTNode	*parent;
	KeyType		key[MAX_T];
	struct BTNode	*child[MAX_T+1];
}BTNode, *BTNode_P;

#define QElemType BTNode_P
#include </home/cpplay/c/git/include/pQueueX.h>
#define lk_q(name)      lk_suffix(name, QElemType)
#define Queue           lk_q(Queue)
#define InitQueue       lk_q(InitQueue)
#define DestroyQueue    lk_q(DestroyQueue)
#define EnQueue         lk_q(EnQueue)
#define DeQueue         lk_q(DeQueue)
#define QueueLength     lk_q(QueueLength)

BTNode* CreateBTN(BTNode *parent)
{
	BTNode *btnode=malloc(sizeof(BTNode));
	if(!btnode)
		return NULL;
	btnode->keynum=0;
	btnode->parent=parent;
	memset(btnode->child, 0, sizeof(BTNode*)*MAX_T);
	return btnode;
}

int BTNodeSplit(BTNode *btnode, int i)
{
	
}

int BtreeInsert(BTNode *T, KeyType *key)
{
	int i, j;
	BTNode *T1, *Tp;
	for(;;){
		for(i=0;i<T->keynum;i++)
			if(*key<=T->key[i])
				break;
		if(T->child[i])
			T=T->child[i];
		else
			break;
	}
	for(j=T->keynum;j>i;j--)
		T->key[j]=T->key[j-1];
	T->key[i]=*key;
	T->keynum++;
	while(T->keynum==MAX_T){
		T1=CreateBTN(T->parent);
		for(i=MIN_T;i<MAX_T;i++){
			T1->key[i-MIN_T]=T->key[i];
			T1->child[i-MIN_T]=T->child[i];
		}
		T1->child[i-MIN_T]=T->child[i];
		T1->keynum=MIN_T;
		T->keynum=MIN_T-1;
		Tp=T->parent;
		if(!Tp){
			Tp=T;
			T1->parent=Tp;
			T=CreateBTN(Tp);
			for(i=0;i<MIN_T-1;i++){
				T->key[i]=Tp->key[i];
				T->child[i]=Tp->child[i];
			}
			T->child[i]=Tp->child[i];
			T->keynum=MIN_T-1;
			Tp->key[0]=Tp->key[MIN_T-1];
			Tp->child[0]=T;
			Tp->child[1]=T1;
			Tp->keynum=1;
			break;
		}
		for(i=0;i<Tp->keynum;i++)
			if(Tp->child[i]==T)
				break;
		for(j=Tp->keynum;j>i;j--){
			Tp->key[j]=Tp->key[j-1];
			Tp->child[j+1]=Tp->child[j];
		}
		Tp->key[i]=T->key[MIN_T-1];
		Tp->child[i+1]=T1;
		Tp->keynum++;
		T=Tp;
	}
	return 0;
}

int PrintBtree(BTNode *T, int PrintBTNode(BTNode*))
{
	int i, tmp, line, flag=0;
	const int fl=0x100, fc=0x10;
	Queue Queue_Q, *Q=&Queue_Q;
	if(InitQueue(Q))
		return -1;
	putchar('{');
	EnQueue(Q, T);
	EnQueue(Q, NULL);
	line=QueueLength(Q);
	flag|=fl;
	while(!DeQueue(Q, &T)){
		if(line)
			line--;
		else{
			putchar('\n');
			line=QueueLength(Q);
		}
		if(T){
			flag&fc ?: (flag|=fc);
			if(tmp=PrintBTNode(T))
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
		for(i=0;(i<=T->keynum)&&T->child[i];i++)
			EnQueue(Q, T->child[i]);
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
