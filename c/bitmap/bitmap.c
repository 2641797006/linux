
#include "bitmap.h"

BitMap*
bitmap_init(BitMap *this, QWORD n) {
	this->qsize = (n>>6) + ((n&0x3f) ? 1 : 0);
	this->data = (QWORD*)malloc(this->qsize << 3);
	if ( ! this->data )
		return NULL;
	this->size = n;
	return this;
}

void
bitmap_clear(BitMap *this)
{
	memset(this->data, 0, this->qsize << 3);
}

void
bitmap_set_all(BitMap *this)
{
	memset(this->data, 0xff, this->qsize << 3);
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
	QWORD q = ((QWORD)1) << (pos&0x3f);
	return (this->data[pos>>6] & q) ? true : false;
}

void
bitmap_set(BitMap *this, QWORD pos)
{
	--pos;
	QWORD q = ((QWORD)1) << (pos&0x3f);
	this->data[pos>>6] |= q;
}

void
bitmap_reset(BitMap *this, QWORD pos)
{
	--pos;
	QWORD q = ((QWORD)1) << (pos&0x3f);
	this->data[pos>>6] &= ~q;
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
	QWORD i, res;
	for (i=0; i<this->qsize; ++i)
		if ( this->data[i] ^ 0xffffffffffffffff )
			break;
	if (i == this->qsize) {
		if (is_ok)
			*is_ok = false;
		return i;
	}
	if (is_ok)
		*is_ok = true;
	res = (i<<6) + qword_lowest_bit( ~ this->data[i] ) + 1;
	if (is_ok) {
		if ( res <= this->size )
			*is_ok = true;
		else
			*is_ok = false;
	}
	return res;
}

