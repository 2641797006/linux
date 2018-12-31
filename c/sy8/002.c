#include <stdio.h>
#include </home/lxll/c/sy8/pSort.h>
#define NUM 20

int main()
{
	int a[NUM], n=NUM, cmp, mov;
	pranda(a,n,NUM);
	PrintArray_ln(a,n);
	BubbleSort_O(a,n,&cmp,&mov);
	PrintArray_ln(a,n);
	printf("cmp=%d, mov=%d\n", cmp, mov);
}
