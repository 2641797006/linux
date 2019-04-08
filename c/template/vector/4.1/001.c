#include <stdio.h>
#define vector_t int
#include "vector.h"

int
main()
{
	int i;
	const char *fname = "1.24k";
	vector *vec = malloc(sizeof(vector));
	vector *vec1 = malloc(sizeof(vector));

	vector_init(vec);

	for(i=0; i<100; ++i)
		vector_push_back(vec, &i);

	vector_save(vec, fname);
	vector_load(vec1, fname);

	for(i=0; i<20; ++i)
		vector_erase(vec1, vector_first(vec1));

	vector_iterator it = vector_first(vec);
	while(it != vector_tail(vec)) {
		printf("%d ", *it);
		it = vector_next(it);
	}
	puts("");

	it = vector_first(vec1);
	while(it != vector_tail(vec1)) {
		printf("%d ", *it);
		it = vector_next(it);
	}
	puts("");

	vector_destroy(vec);
	vector_destroy(vec1);

}
