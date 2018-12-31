#ifndef _EXPRESS_H_
#define _EXPRESS_H_

#ifndef _PBITNODE_H_
#include </home/lxll/c/sy6/pBiTNode.h>
#endif

#ifndef _PCTYPE_H_
#include </home/lxll/c/pctype.h>
#endif

int precede(char c)
{
	int ret;
	switch(c)
	{
		case '(':
			ret=1;
		break;
		case ')':
			ret=2;
		break;
		case '+': case '-':
			ret=3;
		break;
		case '*': case '/':
			ret=4;
		break;
		case '\2': case '\7':
			ret=5;
		break;
		case '^':
			ret=6;
		break;
		case '!':
			ret=7;
		break;
		default:
			ret=-1;
	}
	return ret;
}		

BiTNode* InfixBiTree(const char* infix0)
{
	int c, n, flag=0, yx1=0xffff, yx2, brackets=0;
	double d;
	const char *infix=infix0;
	TElemType TE_e, *e=&TE_e;
	BiTNode BTN_To, *T=NULL, *To=&BTN_To, *Tn=NULL;
	
	for(;;){
		c=*infix++;
		if(c==0)
			break;
		if(isspace(c))
			continue;
		if(c=='('){
			brackets++;
			continue;
		}
		if(c==')'){
			brackets--;
			continue;
		}
		if(isdigit(c)){
			n=0, sscanf(infix-1, "%lf%n", &d, &n);
			if(!n)
				break;
			e->dt.d=d, e->tag=NUM;
			Tn=CreateBiTNode(e, NULL, NULL);
			infix+=(n-1);
			continue;
		}
		yx2=precede(c);
		e->dt.c=c, e->tag=OPT;
		if(yx2>yx1||brackets){
			To->rchild=CreateBiTNode(e, Tn, NULL);
			To=To->rchild;
			Tn=NULL;
		}
		else{
			To->rchild=Tn;
			if(!T)
				T=Tn;
			T=CreateBiTNode(e, T, NULL);
			To=T, Tn=NULL;
		}
		yx1=yx2;
	}
	To->rchild=Tn;
	return T;
}

double DealInfixTree(BiTNode* T)
{
	int i=0;
	double d[2], result=0;
	int deal(BiTNode* T)
	{
		if(T->data.tag==NUM)
			return 0;
		d[0]=T->lchild->data.dt.d;
		d[1]=T->rchild->data.dt.d;
		switch(T->data.dt.c)
		{
			case '+':
				result=d[0]+d[1];
			break;
			case '-':
				result=d[0]-d[1];
			break;
			case '*':
				result=d[0]*d[1];
			break;
			case '/':
				result=d[0]/d[1];
			break;
			default:;
		}
		T->data.tag=NUM;
		T->data.dt.d=result;
		return 0;
	}
	PostOrderTraverse(T, &deal);
	return T->data.dt.d;
}











#endif
