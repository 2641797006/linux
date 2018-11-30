#ifndef _PCTYPE_H_
#define _PCTYPE_H_

#ifndef _MEMORY_H
#include <memory.h>
#endif

#ifndef _pctype_macro_
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned long long QWORD;
#else
#define BYTE	unsigned char
#define WORD	unsigned short
#define DWORD	unsigned long
#define QWORD	unsigned long long
#endif

#define CopyElem(dest, src) memcpy(dest, src, sizeof(src))



















#endif
