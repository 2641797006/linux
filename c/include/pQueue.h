#ifndef _PQUEUE_H_
#define _PQUEUE_H_
// use basic type or pointers

#ifndef _STDLIB_H
#include <stdlib.h>
#endif

#ifndef QElemType
#define QElemType int
#endif

#define QMAXSIZE 0x40
#define QINCSIZE 0x100

typedef struct{
	QElemType *base;
	QElemType *end;
	QElemType *front;
	QElemType *rear;
}Queue;

int InitQueue(Queue *Q)
{
	Q->base=malloc(sizeof(QElemType)*QMAXSIZE);
	if(!Q->base)
		return -1;
	Q->end=Q->base+QMAXSIZE-1;
	Q->front=Q->base;
	Q->rear=Q->base;
	return 0;
}

void DestroyQueue(Queue *Q)
{
	free(Q->base);
	Q->base=NULL;
	Q->end=NULL;
	Q->front=NULL;
	Q->rear=NULL;
}

int EnQueue(Queue *Q, QElemType e)
{
	if((Q->rear+1)==Q->front
		||Q->rear==Q->end&&Q->front==Q->base)
		return -1;
	*Q->rear++=e;
	if(Q->rear>Q->end)
		Q->rear=Q->base;
	return 0;
}

int DeQueue(Queue *Q, QElemType *e)
{
	if(Q->rear==Q->front)
		return -1;
	*e=*Q->front;
	Q->front = Q->front==Q->end ? Q->base : Q->front+1;
	return 0;
}




















#endif
