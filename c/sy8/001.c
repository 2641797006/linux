#include <stdio.h>
#include </home/lxll/c/sy8/pSort.h>
#define NUM 10

int main()
{
	int a[NUM], b[NUM], n=NUM, cmp, mov;
	pranda(a,n,NUM);

	CopyArray(b, a, NUM);
	PrintArray_ln(a,n);
	BubbleSort_O(a,n,&cmp,&mov);
	PrintArray_ln(a,n);
	printf("BubbleSort:: cmp=%d, mov=%d\n", cmp, mov);
	ln();

	CopyArray(a, b, NUM);
	PrintArray_ln(b,n);
	InsertSort_O(b,n,&cmp,&mov);
	PrintArray_ln(b,n);
	printf("InsertSort:: cmp=%d, mov=%d\n", cmp, mov);
	ln();

	CopyArray(b, a, NUM);
	PrintArray_ln(a,n);
	SelectSort_O(a,n,&cmp,&mov);
	PrintArray_ln(a,n);
	printf("SelectSort:: cmp=%d, mov=%d\n", cmp, mov);
	ln();

	CopyArray(a, b, NUM);
	PrintArray_ln(b,n);
	QuickSort_O(b,n,&cmp,&mov);
	PrintArray_ln(b,n);
	printf("QuickSort:: cmp=%d, mov=%d\n", cmp, mov);
	ln();

	CopyArray(b, a, NUM);
	PrintArray_ln(a,n);
	ShellSort_O(a,n,&cmp,&mov);
	PrintArray_ln(a,n);
	printf("ShellSort:: cmp=%d, mov=%d\n", cmp, mov);
	ln();



ln();
}
