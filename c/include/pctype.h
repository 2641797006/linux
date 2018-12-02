#ifndef _PCTYPE_H_
#define _PCTYPE_H_

#ifndef _CTYPE_H
#include <ctype.h>
#endif

#ifndef _MEMORY_H
#include <memory.h>
#endif

#ifndef _pctype_macro_
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned long long QWORD;
#else
#define BYTE	unsigned char
#define WORD	unsigned short
#define DWORD	unsigned int
#define QWORD	unsigned long long
#endif

#define CopyElem(dest, src) memcpy(dest, src, sizeof(src))
#define CmpaElem_O(x, y) (x<y ? -1 : (x==y ? 0 : 1))
#define CmpaElem(x, y) CmpaElem_O((x), (y))


















#endif
