#include <stdio.h>
#define vector_t int
#include "vector.h"

int
main()
{
	int i;
	vector *vec = malloc(sizeof(vector));

	vector_init(vec);

	for(i=0; i<100; ++i)
		vector_push_back(vec, &i);

	for(i=0; i<20; ++i)
		vector_erase(vec, vector_first(vec));

	vector_iterator it = vector_first(vec);

	while(it != vector_tail(vec)) {
		printf("%d ", *it);
		it = vector_next(it);
	}

	puts("");

	vector_destroy(vec);

}
