#include <stdio.h>
#include "bitmap.h"

int main()
{
	bool f;
	BitMap *bmap = create_bitmap(64);

	bitmap_set(bmap, 3);
	bitmap_set(bmap, 64);

	printf("%016lX\n", bmap->data[0]);
	printf("first: %lu\n", bitmap_find_first(bmap, &f));

	printf("bit3: %d\n", bitmap_is_set(bmap, 3));
	bitmap_reset(bmap, 3);
	printf("%016lX\n", bmap->data[0]);
	printf("bit3: %d\n", bitmap_is_set(bmap, 3));

	printf("first: %lu\n", bitmap_find_first(bmap, &f));
}

