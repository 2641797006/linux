#ifndef _CCOLOR_H_
#define _CCOLOR_H_

#define CC_E		"\e["
#define CE(x)		CC_E#x
#define CC(x)		CE(x)"m"
#define ENDCC		CC(0)

#define BLACK		CC(0;30)
#define L_BLACK		CC(1;30)
#define RED		CC(0;31)
#define L_RED		CC(1;31)
#define GREEN		CC(0;32)
#define L_GREEN		CC(1;32)
#define BROWN		CC(0;33)
#define YELLOW		CC(1;33)
#define BLUE		CC(0;34)
#define L_BLUE		CC(1;34)
#define PURPLE		CC(0;35)
#define L_PURPLE	CC(1;35)
#define CYAN		CC(0;36)
#define L_CYAN		CC(1;36)
#define GRAY		CC(0;37)
#define WHITE		CC(1;37)

#define BLACK_S(s)	CC(0;30) s CC(0)
#define L_BLACK_S(s)	CC(1;30) s CC(0)
#define RED_S(s)	CC(0;31) s CC(0)
#define L_RED_S(s)	CC(1;31) s CC(0)
#define GREEN_S(s)	CC(0;32) s CC(0)
#define L_GREEN_S(s)	CC(1;32) s CC(0)
#define BROWN_S(s)	CC(0;33) s CC(0)
#define YELLOW_S(s)	CC(1;33) s CC(0)
#define BLUE_S(s)	CC(0;34) s CC(0)
#define L_BLUE_S(s)	CC(1;34) s CC(0)
#define PURPLE_S(s)	CC(0;35) s CC(0)
#define L_PURPLE_S(s)	CC(1;35) s CC(0)
#define CYAN_S(s)	CC(0;36) s CC(0)
#define L_CYAN_S(s)	CC(1;36) s CC(0)
#define GRAY_S(s)	CC(0;37) s CC(0)
#define WHITE_S(s)	CC(1;37) s CC(0)

#define BG_BLACK	CC(40)
#define BG_RED		CC(41)
#define BG_GREEN	CC(42)
#define BG_YELLOE	CC(43)
#define BG_BLUE		CC(44)
#define BG_PURPLE	CC(45)
#define BG_CYAN		CC(46)
#define BG_WHITE	CC(47)

#define BOLD		CC(1)
#define UNDERLINE	CC(4)
#define BLINK		CC(5)
#define REVERSE		CC(7)
#define HIDE		CC(8)
#define CLEAR		CE(2J)
#define CLRLINE		CE(K)

#define cursor_up(n)	CE(nA)
#define cursor_down(n)	CE(nB)
#define cursor_right(n)	CE(nC)
#define cursor_left(n)	CE(nD)

#define set_cursor(y,x)	CE(y;xH)
#define save_cursor()	CE(s)
#define unsave_cursor()	CE(u)
#define hide_cursor()	CE(?25l)
#define unhide_cursor()	CE(?25h)

#endif

