#ifndef _DW_SCAN_H_
#define _DW_SCAN_H_

#ifndef _PCTYPE_H_
#include </home/lxll/c/git/include/pctype.h>
#endif

#define SCAN_OK		0x0001
#define SCAN_SIGNED	0x0002
#define SCAN_SIGN	0x0004
#define SCAN_OVER	0x0008
#define DW_MAX		0xffffffff

int _dw_numscan(const char* buf0, DWORD* pdwr, DWORD* flagr)
{
	const char *buf=buf0;
	DWORD c;
	QWORD qw=0;
	for(;;){
		c=*buf++;
		if(!c||!isdigit(c))
			break;
		qw=qw*10+c-'0';
	}
	if(pdwr)
		*pdwr=(DWORD)qw;
	if(flagr&&qw-(qw&(QWORD)DW_MAX))
		*flagr|=SCAN_OVER;
	return buf-buf0-1;
}

int _dw_scan(const char* buf0, DWORD* pdwr, DWORD* flagr)
{
	const char* buf=buf0;
	DWORD c, dw=0, flag=0;
	for(;;){
		c=*buf++;
		if(isspace(c))
			continue;
		if(!(flag&SCAN_SIGNED) && (c=='+'||c=='-')){
			flag|=SCAN_SIGNED, c=='+' ? 0 : (flag|=SCAN_SIGN);
			continue;
		}
		break;
	}
	c=_dw_numscan(buf-1, &dw, &flag);
	if(c)
		flag|=SCAN_OK;
	if(pdwr)
		*pdwr = flag&SCAN_SIGN ? -dw : dw;
	if(flagr)
		*flagr=flag;
	return buf-buf0+c-1;
}













#endif
