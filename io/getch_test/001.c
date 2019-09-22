#include<stdio.h>
#ifdef __linux__
#include "getch.h"
#else
#include <conio.h>
#endif
 
int main()
{
	int c;

	puts("getchar() begin:");
	for (;;) {
		c = getchar();
		printf("getchar() = %c\n", c);
		if (c == '\n')
			break;
	}

	puts("getche() begin:");
	for (;;) {
		c = getche();
		printf("getche() = %c\n", c);
		if (c == '\n')
			break;
	}

	puts("getch() begin:");
	for (;;) {
		c = getch();
		printf("getch() = %c\n", c);
		if (c == '\n')
			break;
	}
}
