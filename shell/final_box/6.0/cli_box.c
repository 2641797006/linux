#include "cli_box.h"


BOX*
box_set_align(BOX *box, int i)
{
	box->flag = i;
	return box;
}

BOX*
box_buttom(BOX *box, size_t n)
{
	int i, w;
	w = n + box->pyl_size + box->pyr_size - box->pal_size - box->par_size;
	string_add(box->strbuf, box->pal);
	for (i=0; i<w; ++i)
		string_push_back(box->strbuf, box->px);
	string_add(box->strbuf, box->par);
	string_push_back(box->strbuf, '\n');
	return box;
}

BOX*
box_line(BOX *box, string *s, size_t pos1, size_t pos2)
{
	int c;
	size_t i, wd, left, right;
	wd = box->width - box->width_fix(s, pos1, pos2);
	if (box->flag < 0)
		left = 0, right = wd;
	else if (box->flag > 0)
		left = wd, right = 0;
	else
		left = wd/2, right = wd - left;
	string_add(box->strbuf, box->pyl);
	for (i=0; i<left; ++i)
		string_push_back(box->strbuf, ' ');
	c = s->data(s)[pos2];
	s->data(s)[pos2] = 0;
	string_append(box->strbuf, s->c_str(s) + pos1);
	s->data(s)[pos2] = c;
	for (i=0; i<right; ++i)
		string_push_back(box->strbuf, ' ');
	string_add(box->strbuf, box->pyr);
	string_push_back(box->strbuf, '\n');
	return box;
}

// draw box on CLI
BOX*
box_box(BOX *box, string *s)
{
	size_t pos1=0, pos2;
	box->string_width(box, s);
	box->frame_width_fix(box);
	box->buttom(box, box->width);
	for ( ; pos1 < s->size(s); ) {
		pos2 = s->find(s, pos1, "\n");
		if (pos2 == -1)
			pos2 = s->size(s);
		box->line(box, s, pos1, pos2);
                pos1 = pos2 + 1;
	}
	box->buttom(box, box->width);
	return box;
}

// draw a table on CLI
BOX*
box_table(BOX *box, string *s)
{
	size_t pos1=0, pos2;
	box->string_width(box, s);
	box->frame_width_fix(box);
	box->buttom(box, box->width);
	for ( ; pos1 < s->size(s); ) {
		pos2 = s->find(s, pos1, "\n");
		if (pos2 == -1)
			pos2 = s->size(s);
		box->line(box, s, pos1, pos2);
                pos1 = pos2 + 1;
		box->buttom(box, box->width);
	}
	return box;
}

BOX*
box_box_cs(BOX *box, char *cs)
{
	string _s, *s=&_s;
	string_init(s);
	free(s->_data);
	s->_data = cs;
	s->_size = strlen(cs);
	s->_capacity = s->_size;
	return box->box(box, s);
}

// fix string width for chinese
size_t
box_width_fix(string *s, size_t pos1, size_t pos2)
{
	size_t i, width = pos2 - pos1;
	for (i=pos1; i<pos2; ++i)
		if ((unsigned char)s->at(s, i) > 0x7f)
			--width, i+=2;
	return width;
}

// get the max width of string
size_t
box_string_width(BOX *box, string *s)
{
	size_t pos1=0, pos2, subw, width=0;
	for ( ; pos1 < s->size(s); ) {
		pos2 = s->find(s, pos1, "\n");
		if (pos2 == -1)
			pos2 = s->size(s);
		subw = box_width_fix(s, pos1, pos2);
		if (subw > width)
			width = subw;
		pos1 = pos2 + 1;
	}
	box->width = width;
	return width;
}

BOX*
box_clear(BOX *box)
{
	string_clear(box->strbuf);
	return box;
}

BOX*
box_frame_width_fix(BOX *this)
{
	this->pyl_size = this->width_fix(this->pyl, 0, this->pyl->size(this->pyl));
	this->pyr_size = this->width_fix(this->pyr, 0, this->pyr->size(this->pyr));
	this->pal_size = this->width_fix(this->pal, 0, this->pal->size(this->pal));
	this->par_size = this->width_fix(this->par, 0, this->par->size(this->par));
	return this;
}

BOX*
box_init(BOX *box, char x, const char *al, const char *ar, const char *yl, const char *yr)
//	: flag(0), px(x), pal(al), par(ar), pyl(yl), pyr(yr){}
{
	box->flag = 0;
	box->px = x;

	box->pal = &box->_pal;
	box->par = &box->_par;
	box->pyl = &box->_pyl;
	box->pyr = &box->_pyr;
	box->strbuf = &box->_strbuf;

	string_init(box->pal)->append(box->pal, al);
	string_init(box->par)->append(box->par, ar);
	string_init(box->pyl)->append(box->pyl, yl);
	string_init(box->pyr)->append(box->pyr, yr);
	string_init(box->strbuf);

#define _24k(f)		box->f = box##_##f

	_24k(set_align);
	_24k(buttom);
	_24k(line);
	_24k(box);
	_24k(string_width);
	_24k(width_fix);
	_24k(clear);
	_24k(box_cs);
	_24k(frame_width_fix);
	_24k(table);

#undef _24k

	return box;
}

