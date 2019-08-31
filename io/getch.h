#ifndef _GETCH_H_
#define _GETCH_H_

#ifndef _STDIO_H
#include <stdio.h>
#endif

#include <unistd.h>
#include <termios.h>

static struct termios term_save, term_getch, term_getche;

void init_getch();
int getch();
int getche();

void
init_getch()
{
	tcgetattr(0, &term_save);

	term_getch = term_save;
	term_getch.c_lflag &= ~ICANON;
	term_getch.c_lflag &= ~ECHO;
	term_getch.c_cc[VMIN] = 1;
	term_getch.c_cc[VTIME] = 0;

	term_getche = term_getch;
	term_getche.c_lflag |= ECHO;
}

int
getch()
{
	int c;
	tcsetattr(0, TCSANOW, &term_getch);
	c = getchar();
	tcsetattr(0, TCSANOW, &term_save);
	return c;
}

int
getche()
{
	int c;
	tcsetattr(0, TCSANOW, &term_getche);
	c = getchar();
	tcsetattr(0, TCSANOW, &term_save);
	return c;
}

#endif

