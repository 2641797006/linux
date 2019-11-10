#include <stdio.h>

#define CLEAR()		system("clear")
#define SLEEP()		printf("\n按回车键继续..."); ResetIn()

#define N	10
#define ResetIn()	while(getchar() != '\n'){}

typedef int semaphore;
typedef int Product;

Product products[N];
int in=0, out=0;
semaphore s1=N, s2=0;

int P(semaphore*);
int V(semaphore*);
void menu();
void print_data();

int main()
{
	int i;

	for (;;) {
		print_data();
		menu();
		{
			int r = scanf("%d", &i);
			puts("");
			ResetIn();
			if (r < 1)
				continue;
		}
		switch (i) {
		case 0:
			return 0;
		case 1: //存放
			if ( P(&s1) ) {
				products[in%N] = 'a';
				++in;
				printf("总存+1, ");
				if ( V(&s2) ) {
					//c = products[out%N];
					printf("等待取走-1, ");
					++out;
					printf("总取+1, ");
					V(&s1);
				} else
					printf("缓冲器+1, ");
			} else
				printf("等待存放+1, ");
			puts("");
			break;
		case 2: //取走
			if ( P(&s2) ) {
				//c = products[out%N];
				++out;
				printf("总取+1, ");
				if ( V(&s1) ) {
					products[in%N] = 'a';
					printf("等待存放-1, ");
					++in;
					printf("总存+1, ");
					V(&s2);
				} else
					printf("缓冲器-1, ");
			} else
				printf("等待取走+1, ");
			puts("");
			break;
		}
	}
}


void
print_data()
{
	int c = in - out;
	printf("缓冲器:%d/10  等待存放:%d  等待取走:%d   [总存%d 取%d]\n",
		c, s1<0?-s1:0, s2<0?-s2:0, in, out);
}

int
P(semaphore *s)
{
	--*s;
	if (*s < 0) {
		//wait(s);
		return 0;
	}
	//release(s);
	return 1;
}

int
V(semaphore *s)
{
	++*s;
	if (*s <= 0) {
		//release(s);
		return 1;
	}
	//wait(s);
	return 0;
		;
}

void
menu()
{
	printf(
"1.存放\n"
"2.取走\n"
"0.退出\n"
	);
}

