#ifndef _PLOGIC_H_
#define _PLOGIC_H_

#define and(x, y)	((x)&&(y))
#define or(x, y)	((x)||(y))
#define not(x)		(!(x))
#define xor(x, y)	(!(x)&&(y)||(x)&&!(y))
#define xnor(x, y)	((x)&&(y)||!(x)&&!(y))

#define imp(x, y)	(!(x)||(y))














#endif
