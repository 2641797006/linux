#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t QWORD;

typedef struct BitMap {
	QWORD *data;
	QWORD qsize; // QWORD array size
	QWORD size; // bit num;
}BitMap;

BitMap* bitmap_init (BitMap*, QWORD);
void bitmap_destroy (BitMap*);
void bitmap_clear (BitMap*);
void bitmap_set_all (BitMap*);

BitMap* create_bitmap (QWORD);
bool bitmap_is_set (BitMap*, QWORD);
void bitmap_set (BitMap*, QWORD);
void bitmap_reset (BitMap*, QWORD);
QWORD bitmap_find_first (BitMap*, bool*);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _BITMAP_H_

