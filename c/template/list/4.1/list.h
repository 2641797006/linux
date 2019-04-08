#ifndef list_t
# error: 24k macro: No define list_t
#else

#include <stdlib.h>
#include <string.h>

#define _24k_sptr(s, m, mptr)	( (s*) ( (char*)mptr - (char*)&(((s*)0)->m) ) )

typedef struct node{
	list_t data;
	struct node *prev;
	struct node *next;
}node;

typedef struct{
	node *head;
	node *tail;
	size_t size;
}list;

typedef list_t* list_iterator;

int
list_init (list *L)
{
	L->head = (node*) malloc (sizeof(node));
	if ( ! L->head )
		return 0;
	L->tail = (node*) malloc (sizeof(node));
	if ( ! L->tail ) {
		free( L->head );
		return 0;
	}
	L->head->prev = NULL;
	L->head->next = L->tail;
	L->tail->prev = L->head;
	L->tail->next = NULL;
	L->size = 0;
	return 1;
}

void
list_destroy (list *L)
{
	node *p = L->head;

	while (p) {
		L->head = L->head->next;
		free(p);
		p = L->head;
	}
	L->head = NULL;
	L->tail = NULL;
	L->size = 0;
}

list_t
list_front (list *L)
{
	return L->head->next->data;
}

list_t
list_back (list *L)
{
	return L->tail->prev->data;
}

list_iterator
list_first (list *L)
{
	return & L->head->next->data;
}

list_iterator
list_last (list *L)
{
	return & L->tail->prev->data;
}

list_iterator
list_head (list *L)
{
	return & L->head->data;
}

list_iterator
list_tail (list *L)
{
	return & L->tail->data;
}

list_iterator
list_prev (list_iterator it)
{
	node *p = _24k_sptr ( node, data, it );
	if ( ! p->prev )
		return NULL;
	return & p->prev->data;
}

list_iterator
list_next (list_iterator it)
{
	node *p = _24k_sptr ( node, data, it );
	if ( ! p->next )
		return NULL;
	return & p->next->data;
}

int
list_empty (list *L)
{
	return L->size ? 0 : 1;
}

size_t
list_size (list *L)
{
	return L->size;
}

void
list_clear (list *L)
{
	list_destroy(L);
	list_init(L);
}

int
list_insert (list *L, list_iterator it, const list_t *t)
{
	node *p = _24k_sptr( node, data, it );
	if ( p == L->head )
		return 0;
	node *p1 = (node*) malloc (sizeof(node));
	if ( ! p1 )
		return 0;
	memcpy(&p1->data, t, sizeof(list_t));
	p1->next = p;
	p1->prev = p->prev;
	p->prev = p1;
	p1->prev->next = p1;
	++L->size;
	return 1;
}

int
list_erase (list *L, list_iterator it)
{
	node *p = _24k_sptr( node, data, it );
	if ( p == L->head || p == L->tail )
		return 0;
	p->next->prev = p->prev;
	p->prev->next = p->next;
	free(p);
	--L->size;
	return 1;
}

int
list_push_back (list *L, const list_t *t)
{
	return list_insert(L, list_tail(L), t);
}

int
list_push_front (list *L, const list_t *t)
{
	return list_insert(L, list_first(L), t);
}

int
list_pop_back (list *L)
{
	return list_erase(L, list_last(L));
}

int
list_pop_front (list *L)
{
	return list_erase(L, list_first(L));
}

int
list_assign (list *L, size_t count, const list_t *t)
{
	size_t i;

	list_clear(L);
	for (i=0; i<count; ++i)
		if ( ! list_push_back(L, t) )
			return 0;
	return 1;
}

void
list_write (list *L, FILE *fp)
{
	list_iterator it = list_first(L);

	fwrite(&L->size, sizeof(L->size), 1, fp);
	while (it != list_tail(L)) {
		fwrite(it, sizeof(list_t), 1, fp);
		it = list_next(it);
	}
}

void
list_read (list *L, FILE *fp)
{
	int i=0;
	size_t size;
	list_t t;

	list_init(L);
	fread(&size, sizeof(size_t), 1, fp);
	while (i < size) {
		fread(&t, sizeof(list_t), 1, fp);
		list_push_back(L, &t);
		++i;
	}
}

int
list_save (list *L, const char *fname)
{
	FILE *fp;
	fp = fopen(fname, "w");
	if ( ! fp )
		return 0;
	list_write(L, fp);
	fclose(fp);
	return 1;
}

int
list_load (list *L, const char *fname)
{
	FILE *fp;
	fp = fopen(fname, "r");
	if ( ! fp )
		return 0;
	list_read(L, fp);
	fclose(fp);
	return 1;
}

#undef _24k_sptr
#undef list_t

#endif
