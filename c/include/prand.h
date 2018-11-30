#ifndef _PRAND_H_
#define _PRAND_H_

#ifndef _TIME_H
#include <time.h>
#endif

#ifndef __PINK__
#define __PINK__	-0x50494E4BL
#endif

#define PRAND_MAX	0x7FFFFFFFL

/* 16807=7^5, 127773=PRAND_MAX/16807, 2836=PRAND_MAX%127773 */
int prand()
{
	static unsigned long seed=__PINK__;
	if(seed==__PINK__)
		seed=(unsigned)time(NULL);
	long a, b;
	a=seed/127773L;
	b=seed%127773L;
	seed=16807L*b-2836L*a;
	if(seed>PRAND_MAX)
		seed+=PRAND_MAX;
	return seed;
}
















#endif
