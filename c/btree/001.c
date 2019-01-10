#include <stdio.h>
#include <stdarg.h>
#include </home/cpplay/c/btree/btree.h>

int setkey(BTNode *btnode, int n, ...);
int addchild(BTNode *btnode, int n, ...);
int print(BTNode *btnode);

int main()
{
	int i=0, tmp;
	BTNode *T;
	T=CreateBTN(NULL);
	setkey(T, 0);
	PrintBtree(T,&print);
	ln();
	for(;;){
		scanf("%d", &tmp);
		BtreeInsert(T, &tmp);
		ln();
		PrintBtree(T, &print);
		ln();
		ln();
	}
	putchar('\n');
}

int print(BTNode *btnode)
{
	int i;
	putchar('<');
	for(i=0;i<btnode->keynum;i++)
		printf("%d ", btnode->key[i]);
//	printf("%08X ", btnode->parent);
	printf("\b> ");
	return 0;
}

int setkey_o(BTNode *btnode, int keynum, va_list ap)
{
	int i;
	btnode->keynum=keynum;
	for(i=0;i<keynum;i++)
		btnode->key[i]=va_arg(ap, int);
	va_end(ap);
	return 0;
}

int setkey(BTNode *btnode, int keynum, ...)
{
	va_list ap;
	va_start(ap, keynum);
	return setkey_o(btnode, keynum, ap);
}

int addchild(BTNode *btnode, int keynum, ...)
{
	int i;
	va_list ap;
	va_start(ap, keynum);
	for(i=0;i<MAX_T;i++)
		if(!btnode->child[i])
			break;
	if(i>=MAX_T)
		return -1;
	btnode->child[i]=CreateBTN(btnode);
	return setkey_o(btnode->child[i], keynum, ap);
}
