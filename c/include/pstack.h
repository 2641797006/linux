#ifndef _PSTACK_H_
#define _PSTACK_H_

#ifndef _STDLIB_H
#include <stdlib.h>
#endif

#ifndef SElemType
#define SElemType int
#endif

#define STACK_INIT_SIZE		0x80
#define STACKINCREMENT		0x40

typedef struct{
	SElemType *base;
	SElemType *top;
	int stacksize;
}Stack;

int InitStack(Stack *S)
{
	S->base=malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!S->base)
		return -1;
	S->top=S->base;
	S->stacksize=STACK_INIT_SIZE-1;
	return 0;
}

void DestroyStack(Stack *S)
{
	free(S->base);
	S->base=NULL;
	S->top=NULL;
	S->stacksize=0;
}

void ClearStack(Stack *S)
{
	S->top=S->base;
}

int StackLength(Stack *S)
{
	return S->top-S->base;
}

SElemType* GetSTP(Stack *S)
{
	return S->top;
}

void SetSTP(Stack *S, void *p)
{
	S->top=p;
}

int Push(Stack *S, SElemType e)
{
	int size;
	void* p;
	size=S->top-S->base;
	if(size+1>S->stacksize){
		p=realloc(S->base, sizeof(SElemType)*(S->stacksize+1+STACKINCREMENT));
		if(!p)
			return -1;
		S->base=p;
		S->top=S->base+size;
		S->stacksize+=STACKINCREMENT;
	}
	*++S->top=e;
	return 0;
}

int Pop(Stack *S, SElemType *e)
{
	if(S->top<=S->base)
		return -1;
	*e=*S->top--;
	return 0;
}

int PrintStack(Stack *S)
{
	SElemType *p=S->top;
	printf("---->>>TOP<<<<----\n");
	while(p!=S->base)
		printf("0x%016llX\n", *p--);
	printf("---->>>BASE<<<----\n");
}

#endif
