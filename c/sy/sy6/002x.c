#include <stdio.h>
#include </home/lxll/c/pctype.h>

typedef enum{ OPT, NUM } ETYPE;
typedef struct{
	union{
		double d;
		char c;
	}dt;
	ETYPE tag;
}__TElemType;
#define TElemType __TElemType
#define CopyTElem_O(dest, src) (dest->dt.d=src->dt.d, dest->tag=src->tag)
#define CopyTElem(dest, src) CopyTElem_O((dest), (src))

#include </home/lxll/c/sy6/pBiTNode.h>
//#include </home/lxll/c/sy6/express.h>
#include </home/lxll/c/sy6/ex.h>
#define ResetCin() setbuf(stdin, NULL)

int PrintBiTNode(BiTNode* T);

int main()
{
	int i;
	char *buf;
	double d;
	BiTNode *T;
	buf=malloc(4096);
	if(!buf)
		return -1;
	printf("WH::Infix\n");
	for(;;){
		printf(">>> ");
		ResetCin();
		scanf("%4000[^\n]", buf);
		T=InfixBiTree(buf);
		InOrderTraverse(T, &PrintBiTNode), putchar('\n');
		PostOrderTraverse(T, &PrintBiTNode);
		d=DealInfixTree(T);
		printf("=%.20G\n", d);
	}

}



int PrintBiTNode(BiTNode* T)
{
	if(T->data.tag==NUM)
		printf("%.20G", T->data.dt.d);
	else
		printf("%c", T->data.dt.c);
//	printf("T->lchild=0x%016X \nT->rchild=0x%016X\n", T->lchild, T->rchild);
	return 0;
}

