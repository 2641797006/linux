#ifndef _GETCH_H_
#define _GETCH_H_

#ifndef _STDIO_H
#include <stdio.h>
#endif

#include <unistd.h>
#include <termios.h>

static struct termios term_save, term_getch, term_getche;

void init_getch();
void end_getch();
void set_getch();
void set_getche();
int getch();
int getche();

static unsigned int getch_is_init = 0;

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

void
end_getch()
{
	tcsetattr(0, TCSANOW, &term_save);
}

void
set_getch()
{
	tcsetattr(0, TCSANOW, &term_getch);
}

void
set_getche()
{
	tcsetattr(0, TCSANOW, &term_getche);
}

int
getch()
{
	if ( ! getch_is_init ) {
		init_getch();
		getch_is_init = 1;
	}
	int c;
	tcsetattr(0, TCSANOW, &term_getch);
	c = getchar();
	tcsetattr(0, TCSANOW, &term_save);
	return c;
}

int
getche()
{
	if ( ! getch_is_init ) {
		init_getch();
		getch_is_init = 1;
	}
	int c;
	tcsetattr(0, TCSANOW, &term_getche);
	c = getchar();
	tcsetattr(0, TCSANOW, &term_save);
	return c;
}

#endif

