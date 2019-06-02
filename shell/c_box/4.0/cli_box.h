#ifndef _CLI_BOX_H_
#define _CLI_BOX_H_

#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef _24K_STRING
#include "string24k.h"
#endif

typedef struct box{
//  public:
//	cli_box(char x='-', string a="+", string yl="| ", string yr=" |");
	struct box* (*set_align)(struct box*, int);

	struct box* (*buttom)(struct box*, size_t n);
	struct box* (*line)(struct box*, string*, size_t, size_t);
	struct box* (*box)(struct box*, string*);
	struct box* (*clear)(struct box*);
	struct box* (*box_cs)(struct box*, char*);

	size_t (*width_fix)(string*, size_t, size_t);
	size_t (*string_width)(struct box*, string*);

//  private:
	int flag;
	char px;
	string _pa, _pyl, _pyr;
	string *pa, *pyl, *pyr;
	int width;
	string _strbuf, *strbuf;
}BOX;

BOX*
box_init(BOX *box, char, const char*, const char*, const char*);

#endif // _CLI_BOX_H_

