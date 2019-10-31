#include <stdio.h>
#include <stdbool.h>
#include "bitmap.h"

int main()
{
	bool is_ok;
	BitMap *bmap = create_bitmap(10000);
	bitmap_set_all(bmap);

	bitmap_reset(bmap, 3000);
	bitmap_reset(bmap, 6666);

	printf("first: %lu\n", bitmap_find_first(bmap, NULL));

	printf("bit3000: %d\n", bitmap_is_set(bmap, 3000));
	bitmap_set(bmap, 3000);
	printf("bit3000: %d\n", bitmap_is_set(bmap, 3000));

	printf("first: %lu ", bitmap_find_first(bmap, &is_ok));
	printf("is_ok = %s\n", is_ok ? "true" : "false");

	bitmap_set(bmap, 6666);
	printf("first: %lu ", bitmap_find_first(bmap, &is_ok));
	printf("is_ok = %s\n", is_ok ? "true" : "false");
}

