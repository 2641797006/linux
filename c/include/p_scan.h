#ifndef _P_SCAN_H_
#define _P_SCAN_H_

#ifndef _CTYPE_H
#include <ctype.h>
#endif

#ifndef _PCTYPE_H_
#include </home/lxll/c/git/include/pctype.h>
#endif

#define SC_OK		0x0001
#define SC_SIGNOK	0x0002
#define SC_SIGN		0x0010
#define SC_DIGIT	0x0020
#define SC_POINT	0x0040
#define SC_DECIM	0x0080

#ifndef _DW_SCAN_H_
#include </home/lxll/c/git/include/__scan/_dw_scan.h>
#endif

int _P_SCAN_;

#define PLF_SIGN	0x0010
#define PLF_INT		0x0020
#define PLF_POINT	0x0040
#define PLF_DECIMAL	0x0080

#define _lf_scan(buffer, address) _p_lf_scan(buffer, address, (_P_SCAN_&=0|=sizeof(*(address))>>3, &_P_SCAN_))

#ifdef _P_lf_scan
int _p_lf_scan(const char* buffer0, void* address, int* flags)
{
	const BYTE *buffer=buffer0;
	int c;
	double d=0;
	for(;;){
		c=(BYTE)*buffer++;
		if(c==0)
			return buffer-buffer0-1;
		if(isspace(c))
			continue;
		switch(c){
		case '+': case '-':
			if(*flags>PLF_SIGN){
				*flags|=PLF_SIGN<<8;
				return buffer-buffer0-1;
			}
			if(c=='-')
				flags&=~(flags&PLF_SIGN^PLF_SIGN);
		break;
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			





}
#endif














#endif
