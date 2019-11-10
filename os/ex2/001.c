#include <stdio.h>
#include <memory.h>

#define ResetIn()	while(getchar() != '\n'){}
#define CLEAR()		system("clear")
#define SLEEP()		printf("\n按回车键继续..."); ResetIn()

#define	MP	100	//max进程
#define MR	50	//max资源

int avail[MR];
int max[MP][MR];
int alloc[MP][MR];
int need[MP][MR];

int request[MP][MR];

int work[MR];
int finish[MP];

int np;	//进程数
int nr;	//资源数

int init();
int is_safe();
int select();
void print_data();

int main()
{
	int i, pid;

	init();
	if ( ! is_safe() ) {
		printf("不安全\n");
	}

	for (;;) {
		printf("\n");
		print_data();
start:		printf("请输入要申请资源的进程号[0,%d]: ", np-1);
		{
			int r = scanf("%d", &pid);
			ResetIn();
			if (r < 1 || pid<0 || pid>=np)
				continue;
		}

		printf("请输入进程所请求的各资源的数量: \n");
		for (i=0; i<nr; ++i)
			scanf("%d", request[pid]+i);
		ResetIn();
		for (i=0; i<nr; ++i)
			if (request[pid][i] < 0 || request[pid][i] > need[pid][i] || request[pid][i] > avail[i]) {
				printf("您输入的请求数量超标!!!\n进程[%d]等待\n", pid);
				goto start;
			}
		for (i=0; i<nr; ++i) {
			avail[i] -= request[pid][i];
			alloc[pid][i] += request[pid][i];
			need[pid][i] -= request[pid][i];
		}
		if ( is_safe() )
			printf("alloc OK\n");
		else {
			printf("Bad alloc\n");
			for (i=0; i<nr; ++i) {
				avail[i] += request[pid][i];
				alloc[pid][i] -= request[pid][i];
				need[pid][i] += request[pid][i];
			}
		}
	}
}

int
init()
{
	int i, j;

	printf("请输入进程总数: ");
	scanf("%d", &np);
	ResetIn();

	printf("请输入资源种类数: ");
	scanf("%d", &nr);
	ResetIn();

	printf("请输入%d类资源现有的数目: \n", nr);
	for (i=0; i<nr; ++i)
		scanf("%d", avail+i);
	ResetIn();

	printf("最大需求矩阵(每个进程最多所需的各资源数)[%d*%d]输入: \n", np, nr);
	for (i=0; i<np; ++i)
		for (j=0; j<nr; ++j)
			scanf("%d", max[i]+j);
	ResetIn();

#if 0
	memset(alloc, 0, sizeof(int)*MP*MR);
#else
	printf("分配矩阵(每个进程已分配的各资源数)[%d*%d]输入: \n", np, nr);
	for (i=0; i<np; ++i)
		for (j=0; j<nr; ++j)
			scanf("%d", alloc[i]+j);
	ResetIn();
#endif

	for (i=0; i<np; ++i)
		for (j=0; j<nr; ++j)
			need[i][j] = max[i][j] - alloc[i][j];
	return 1;
}

int
select()
{
	int i, j;
	for (i=0; i<np; ++i) {
		if ( finish[i] )
			continue;
		for (j=0; j<nr; ++j)
			if (need[i][j] > work[j])
				break;
		if (j == nr)
			return i;
	}
	return -1;
}

int
is_safe()
{
	int i, j;

	for (i=0; i<nr; ++i)
		work[i] = avail[i];
	memset(finish, 0, sizeof(int)*np);

	while ( (i = select()) >= 0 ) {
		for (j=0; j<nr; ++j)
			work[j] += alloc[i][j];
		finish[i] = 1;
	}

	for (i=0; i<np; ++i)
		if ( ! finish[i] )
			return 0;
	return 1;
}

void
print_mat(int (*mat)[MR])
{
	int i, j;
	for (i=0; i<np; ++i) {
		for (j=0; j<nr; ++j)
			printf("%2d ", mat[i][j]);
		puts("");
	}
}

void
print_data()
{
	int i;
	printf("\nmax:\n");
	print_mat(max);
	printf("\nalloc:\n");
	print_mat(alloc);
	printf("\nneed:\n");
	print_mat(need);
	printf("\navail\n");
	for (i=0; i<nr; ++i)
		printf("%2d ", avail[i]);
	puts("");
}

