#ifndef _P_SCAN_H_
#define _P_SCAN_H_

#ifndef _CTYPE_H
#include <ctype.h>
#endif

#ifndef _PCTYPE_H_
#include </home/lxll/c/git/include/pctype.h>
#endif

int _P_SCAN_;

#define PLF_SIGN	0x0010
#define PLF_INT		0x0020
#define PLF_POINT	0x0040
#define PLF_DECIMAL	0x0080

#define _lf_scan(buffer, address) _p_lf_scan(buffer, address, (_P_SCAN_&=0|=sizeof(*(address))>>3, &_P_SCAN_))
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
