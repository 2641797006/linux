#ifndef _PMACRO_H_
#define _PMACRO_H_

#define __lk_suffix(name, suffix)	name##_##suffix
#define lk_suffix(name, suffix)		__lk_suffix(name, suffix)

#define ln()				putchar('\n')
#define PRINT_STR(str)			printf("%s", str)



































#endif
