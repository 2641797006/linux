#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

typedef uint64_t QWORD;

typedef struct BitMap {
	QWORD *data;
	QWORD qsize; // QWORD array size
	QWORD size; // bit num;
}BitMap;

BitMap*
bitmap_init(BitMap *this, QWORD n) {
	this->qsize = n/64 + ((n%64) ? 1 : 0);
	this->data = (QWORD*)malloc(this->qsize * 8);
	if ( ! this->data )
		return NULL;
	this->size = n;
	return this;
}

void
bitmap_clear(BitMap *this)
{
	memset(this->data, 0, this->qsize*8);
}

void
bitmap_destroy(BitMap *this)
{
	free(this->data);
	this->size = 0;
}

BitMap*
create_bitmap(QWORD n)
{
	BitMap *bmap = (BitMap*)malloc(sizeof(BitMap));
	if ( ! bmap || ! bitmap_init(bmap, n) )
		return NULL;
	bitmap_clear(bmap);
	return bmap;
}

bool
bitmap_is_set(BitMap *this, QWORD pos)
{
	--pos;
	QWORD x = pos/64;
	QWORD y = pos%64;
	QWORD q = ((QWORD)1) << y;
	return (this->data[x] & q) ? true : false;
}

void
bitmap_set(BitMap *this, QWORD pos)
{
	--pos;
	QWORD x = pos/64;
	QWORD y = pos%64;
	QWORD q = ((QWORD)1) << y;
	this->data[x] |= q;
}

void
bitmap_reset(BitMap *this, QWORD pos)
{
	--pos;
	QWORD x = pos/64;
	QWORD y = pos%64;
	QWORD q = ((QWORD)1) << y;
	this->data[x] &= ~q;
}

QWORD
qword_lowest_bit(QWORD q) // 0 ~ 63
{
	QWORD n = 63;
	if (q & 0x00000000ffffffff) {
		n -= 32;
		q &= 0x00000000ffffffff;
	}
	if (q & 0x0000ffff0000ffff) {
		n -= 16;
		q &= 0x0000ffff0000ffff;
	}
	if (q & 0x00ff00ff00ff00ff) {
		n -= 8;
		q &= 0x00ff00ff00ff00ff;
	}
	if (q & 0x0f0f0f0f0f0f0f0f) {
		n -= 4;
		q &= 0x0f0f0f0f0f0f0f0f;
	}
	if (q & 0x3333333333333333) {
		n -= 2;
		q &= 0x3333333333333333;
	}
	if (q & 0x5555555555555555) {
		n -= 1;
	}
	return n;
}

QWORD
qword_highest_bit(QWORD q) // 0 ~ 63
{
	QWORD n = 0;
	if (q & 0xffffffff00000000) {
		n += 32;
		q &= 0xffffffff00000000;
	}
	if (q & 0xffff0000ffff0000) {
		n += 16;
		q &= 0xffff0000ffff0000;
	}
	if (q & 0xff00ff00ff00ff00) {
		n += 8;
		q &= 0xff00ff00ff00ff00;
	}
	if (q & 0xf0f0f0f0f0f0f0f0) {
		n += 4;
		q &= 0xf0f0f0f0f0f0f0f0;
	}
	if (q & 0xcccccccccccccccc) {
		n += 2;
		q &= 0xcccccccccccccccc;
	}
	if (q & 0xaaaaaaaaaaaaaaaa) {
		n += 1;
	}
	return n;
}

QWORD
bitmap_find_first(BitMap *this, bool *is_ok)
{
	QWORD i;
	for (i=0; i<this->qsize; ++i)
		if (this->data[i])
			break;
	if (i == this->qsize) {
		*is_ok = false;
		return i;
	}
	return i*64 + qword_lowest_bit(this->data[i]) + 1;
}

#endif // _BITMAP_H_

