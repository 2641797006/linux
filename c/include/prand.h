#ifndef _PRAND_H_
#define _PRAND_H_

#ifndef _TIME_H
#include <time.h>
#endif

#ifndef _PMACRO_H_
#include </home/lxll/c/git/include/pMacro.h>
#endif

#ifndef _PCTYPE_H_
#include </home/lxll/c/git/include/pctype.h>
#endif

#ifndef __PINK__
#define __PINK__	-0x50494E4B
#endif

#define PRAND_MAX	0x7FFFFFFF
#define PRAND(seed)	(16807*((seed)%127773)-2836*((seed)/127773))

/* 16807=7^5, 127773=PRAND_MAX/16807, 2836=PRAND_MAX%127773 */
int prand()
{
	static DWORD seed=__PINK__;
	seed==(DWORD)__PINK__ ? (seed=PRAND(time(NULL))) : 0;
	DWORD a, b;
	a=seed/127773;
	b=seed%127773;
	seed=16807*b-2836*a;
	if(seed>PRAND_MAX)
		seed+=PRAND_MAX;
	return seed;
}

#endif
