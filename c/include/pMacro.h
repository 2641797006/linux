#ifndef _PMACRO_H_
#define _PMACRO_H_

#define DWS_MAX				0x7fffffff
#define DWS_MIN				(-DWS_MAX-1)
#define DW_MAX				0xffffffff

#define __lk_suffix(name, suffix)	name##_##suffix
#define lk_suffix(name, suffix)		__lk_suffix(name, suffix)

#define CopyElem(dest, src) memcpy(dest, src, sizeof(*(src)))
#define CmpaElem_O(x, y) (x<y ? -1 : (x==y ? 0 : 1))
#define CmpaElem(x, y) CmpaElem_O((x), (y))

#define ln()				putchar('\n')
#define PRINT_STR(str)			printf("%s", str)
#define ResetCin() while(fgetc(stdin)!='\n'){}

#define FOPEN(fname) ( access(fname, F_OK) ? fopen(fname, "w+") : fopen(fname, "r+") )

#endif
