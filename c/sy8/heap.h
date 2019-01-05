#define l_c(i) (2*(i)+1)
#define r_c(i) (2*(i)+2)

void __HeapSort(int *a, int n)
{
	int parent, child, tmp;
	void HeapAdjust(int start, int end)
	{
		parent=start, tmp=a[start];
		while(l_c(parent)<=end)
		{
			child=l_c(parent);
			if((child+1<=end) && (a[child]<a[child+1]))
				child++;
			if(tmp>a[child])
				break;
			else
				a[parent]=a[child];
			parent=child;
		}
		a[parent]=tmp;
	}
	int i;
	for(i=n/2-1;i>=0;i--)
		HeapAdjust(i,n-1);
	for(i=n-1;i>0;i--){
		tmp=a[i], a[i]=a[0], a[0]=tmp;
		HeapAdjust(0,i-1);
	}
}


void MaxHeap(int *a, int n)
{
	int parent, child, tmp;
	void HeapAdjust(int start, int end)
	{
		parent=start, tmp=a[start];
		while(l_c(parent)<=end)
		{
			child=l_c(parent);
			if((child+1<=end) && (a[child]<a[child+1]))
				child++;
			if(tmp>a[child])
				break;
			else
				a[parent]=a[child];
			parent=child;
		}
		a[parent]=tmp;
	}
	int i;
	for(i=n/2-1;i>=0;i--)
		HeapAdjust(i,n-1);
}

void PrintHeap(int *a, int n)
{
	int i, level;
	for(level=1;level<n;level*=2){
		for(i=0;i<level;i++){
			printf("%2d ", a[i]);
			if(i%2!=0&&i!=level-1)
				putchar('\b'), putchar(','), putchar(' ');
		}
		putchar('\n');
		a+=level;
		n-=level;
	}
	for(i=0;i<n;i++){
		printf("%2d ", a[i]);
		if(i%2!=0&&i!=level-1)
			putchar('\b'), putchar(','), putchar(' ');
	}
}
#define PrintHeap_ln(a,n) (PrintHeap(a,n), putchar('\n'))

#undef l_c
#undef r_c
