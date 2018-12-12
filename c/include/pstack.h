#ifndef _PSTACK_H_
#define _PSTACK_H_

#ifndef _STDLIB_H
#include <stdlib.h>
#endif

#ifndef _STDARG_H
#include <stdarg.h>
#endif

#ifndef _PCTYPE_H_
#include </home/lxll/c/git/include/pctype.h>
#endif

#define STACK_INIT_SIZE		0x80
#define STACKINCREMENT		0x40

struct{
	QWORD *base;
	QWORD *top;
	QWORD stacksize;
}__P_STACK_STRUCT__={0};
#define S (&__P_STACK_STRUCT__)

int InitStack()
{
	S->base=malloc(STACK_INIT_SIZE*sizeof(QWORD));
	if(!S->base)
		return -1;
	S->top=S->base;
	S->stacksize=STACK_INIT_SIZE-1;
	return 0;
}

void DestroyStack()
{
	free(S->base);
}

int StackSize()
{
	return S->top-S->base;
}

QWORD* GetSTP()
{
	return S->top;
}

void SetSTP(void *p)
{
	S->top=p;
}

int EnoughStack(QWORD _)
{
	void* p;
	QWORD size=(_+sizeof(QWORD)-1)/sizeof(QWORD);
	*S->base=S->top-S->base;
	if(*S->base+size>S->stacksize){
		p=(void*)realloc(S->base, (DWORD)( sizeof(QWORD)*(S->stacksize+1+STACKINCREMENT+size) ) );
		if(!p)
			return -1;
		S->base=(QWORD*)p;
		S->top=S->base+*S->base;
		S->stacksize+=(STACKINCREMENT+size);
		return 1;
	}
	return 0;
}

#define __S_push(value, S)( \
		EnoughStack(sizeof(value))>=0 ? \
		( \
			*++S.top=0, \
			memcpy(S.top, &value, (int)sizeof(value)), \
			S.top+=( (sizeof(value)+sizeof(QWORD)-1)/sizeof(QWORD)-1 ), \
			(sizeof(value)+sizeof(QWORD)-1)/sizeof(QWORD) \
		) \
: -1 )

#define push(value) __S_push(value, __P_STACK_STRUCT__)

int __S_pop(QWORD _, void *address)
{

	QWORD size=(_+sizeof(QWORD)-1)/sizeof(QWORD);
	if(S->top-S->base<size)
		return -1;
	memcpy(address, S->top-size+1, (DWORD)_);
	S->top-=size;
	return 0;
}

#define pop(address) __S_pop(sizeof(*(address)), address)

int PrintStack()
{
	QWORD *p=S->top;
	printf("---->>>TOP<<<<----\n");
	while(p!=S->base)
		printf("0x%016llX\n", *p--);
	printf("---->>>BASE<<<----\n");
}

#undef S
#endif
