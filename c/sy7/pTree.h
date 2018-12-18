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

typedef struct Tree{
	TElemType *data;
	struct Tree *child;
	int num;
}Tree;


































#endif
