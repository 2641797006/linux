#include <stdio.h>
#include "string"

int
main()
{
	int i;
	string s;

	string_init(&s);

	string_assign(&s, "c string by 24k >_<");
	puts( string_c_str(&s) );

	string_pop_back(&s);
	string_pop_back(&s);
	puts( string_c_str(&s) );

	for (i=0; i<24; ++i)
		string_push_back(&s, '6');
	puts( string_c_str(&s) );

	string_destroy(&s);
}
