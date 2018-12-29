#ifndef _PSORT_H_
#define _PSORT_H_

#ifndef _PRAND_H_
#include </home/lxll/c/git/include/prand.h>
#endif

#ifndef _PMACRO_H_
#include </home/lxll/c/git/include/pMacro.h>
#endif

void pranda(int *arr, int n, int max)
{
	int i;
	if(max<0)
		max=PRAND_MAX;
	else
		max++;
	for(i=0;i<n;i++)
		arr[i]=prand()%max;
}

void PrintArray(int *arr, int n)
{
	int i;
	for(i=0;i<n;i++)
		printf("%d ", arr[i]);
	putchar('\b');
}
#define PrintArray_ln(a,n) (PrintArray(a,n), ln())

void BubbleSort_O(int *a, int n, int *cmp, int *mov)
{
	int _cmp=0, _mov=0;
	int i, j, tmp;
	n--, _mov++;
	for(i=0,_mov++;(_cmp++,i<n);i++,_mov++)
		for(j=0,_mov++;(_cmp++,j<n-i);j++,_mov++)
			if((_cmp++, a[j]>a[j+1]))
				tmp=a[j], a[j]=a[j+1], a[j+1]=tmp, _mov+=3;
	if(cmp)
		*cmp=_cmp;
	if(mov)
		*mov=_mov;
}
#define BubbleSort(a,n) BubbleSort_O(a,n,NULL,NULL)

#endif
