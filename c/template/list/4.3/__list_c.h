
#ifdef __TEMPLATE_ERROR

void
_(fatal_error) (const char *file, const char *func, size_t line, const char *fmt, ...) {
#ifndef _24K_NOT_PRINT_ERR_MSG
	va_list ap;
	va_start(ap, fmt);
	fprintf(stderr, "_::error> in file `%s`, in function `%s` line %ld: \n\t(*/ω＼*): ", file, func, line);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
#endif
#ifndef _24K_NOT_EXIT
	exit(24);
#endif
}

#endif


static void (*_(copyer)) (__list_t*, const __list_t*) = NULL;
static void (*_(destructor)) (__list_t*) = NULL;

void
_(set_copyer) ( void (*copyer) (__list_t*, const __list_t*) )
{
	_(copyer) = copyer;
}

void
_(set_destructor) ( void (*destructor) (__list_t*) )
{
	_(destructor) = destructor;
}

void
_(destroy) (__list *list)
{
	_(node) *p = list->head->next, *tmp = p;

	while (p != list->tail) {
		tmp = p->next;
		if ( _(destructor) )
			_(destructor)(&p->data);
		free(p);
		p = tmp;
	}

	free(list->head);
	free(list->tail);

	list->head = NULL;
	list->tail = NULL;
	list->_size = 0;
}

__list_t
_(front) (__list *list)
{
	if ( ! list->_size )
		__error("read data from an empty list\n", 0);
	return list->head->next->data;
}

__list_t
_(back) (__list *list)
{
	if ( ! list->_size )
		__error("read data from an empty list\n", 0);
	return list->tail->prev->data;
}

_(iterator)
_(first) (__list *list)
{
	return &list->head->next->data;
}

_(iterator)
_(last) (__list *list)
{
	return &list->tail->prev->data;
}

_(iterator)
_(head) (__list *list)
{
	return &list->head->data;
}

_(iterator)
_(tail) (__list *list)
{
	return &list->tail->data;
}

_(iterator)
_(prev) (__list *list, _(iterator) it)
{
	_(node) *p = __sptr( _(node), data, it );
	if ( ! p->prev ) {
		__error("iterator out of bound\n", 0);
		return NULL;
	}
	return &p->prev->data;
}

_(iterator)
_(next) (__list *list, _(iterator) it)
{
	_(node) *p = __sptr( _(node), data, it );
	if ( ! p->next ) {
		__error("iterator out of bound\n", 0);
		return NULL;
	}
	return &p->next->data;
}

int
_(empty) (__list *list)
{
	if ( list->_size )
		return 0;
	return 1;
}

size_t
_(size) (__list *list)
{
	return list->_size;
}

void
_(clear) (__list *list)
{
	_(destroy)(list);
	_(init)(list);
}

int
_(insert) (__list *list, _(iterator) it, const __list_t *t)
{
	_(node) *p = __sptr( _(node), data, it );
	_(node) *p1 = (_(node)*) malloc ( sizeof(_(node)) );
	if ( p == list->head ) {
		free(p1);
		__error("insert pos error\n", 0);
		return 0;
	}
	if ( ! p1 ) {
		free(p1);
		return 0;
	}

/*	memcpy(&p1->data, t, sizeof(__list_t)); */
	if ( _(copyer) )
		_(copyer)(&p1->data, t);
	else
		p1->data = *t;

	p1->next = p;
	p1->prev = p->prev;
	p->prev = p1;
	p1->prev->next = p1;
	++list->_size;
	return 1;
}

int
_(erase) (__list *list, _(iterator) it)
{
	_(node) *p = __sptr( _(node), data, it );
	if ( p == list->head || p == list->tail ) {
		__error("erase pos error\n", 0);
		return 0;
	}
	p->next->prev = p->prev;
	p->prev->next = p->next;
	if ( _(destructor) )
		_(destructor)(it);
	free(p);
	--list->_size;
	return 1;
}


int
_(push_back) (__list *list, const __list_t *t)
{
	return _(insert)(list, _(tail)(list), t);
}

int
_(push_front) (__list *list, const __list_t *t)
{
	return _(insert)(list, _(first)(list), t);
}

int
_(pop_back) (__list *list)
{
	return _(erase)(list, _(last)(list));
}

int
_(pop_front) (__list *list)
{
	return _(erase)(list, _(first)(list));
}

int
_(assign) (__list *list, size_t count, const __list_t *t)
{
	size_t i;

	_(clear)(list);
	for (i=0; i<count; ++i)
		if ( ! _(push_back)(list, t) )
			return 0;
	return 1;
}

void
_(write) (__list *list, FILE *fp)
{
	_(iterator) it = _(first)(list);

	fwrite(&list->_size, sizeof(size_t), 1, fp);
	while (it != _(tail)(list)) {
		fwrite(it, sizeof(__list_t), 1, fp);
		it = _(next)(list, it);
	}
}

void
_(read) (__list *list, FILE *fp)
{
	size_t i, _size;
	__list_t t;

/*	_(init)(list); */
	fread(&_size, sizeof(size_t), 1, fp);
	for (i=0; i<_size; ++i) {
		fread(&t, sizeof(__list_t), 1, fp);
		_(push_back)(list, &t);
	}
}

int
_(save) (__list *list, const char *fname)
{
	FILE *fp;
	fp = fopen(fname, "w");
	if ( ! fp )
		return 0;
	_(write)(list, fp);
	fclose(fp);
	return 1;
}

int
_(load) (__list *list, const char *fname)
{
	FILE *fp;
	fp = fopen(fname, "r");
	if ( ! fp )
		return 0;
	_(read)(list, fp);
	fclose(fp);
	return 1;
}

int
_(traverse) (__list *list, int (*f)(__list_t*))
{
	int ret;
	_(iterator) it;

	it = list->begin(list);
	while (it != list->end(list)) {
		ret = f(it);
		if ( ret )
			return ret;
		it = list->next(list, it);
	}
	return 0;
}

int
_(rtraverse) (__list *list, int (*f)(__list_t*))
{
	int ret;
	_(iterator) it;

	it = list->rbegin(list);
	while (it != list->rend(list)) {
		ret = f(it);
		if ( ret )
			return ret;
		it = list->prev(list, it);
	}
	return 0;
}

__list*
_(find_if) (__list *list, int (*f)(const __list_t*))
{
	int ret;
	__list *L=(__list*)malloc(sizeof(__list));
	_(iterator) it;

	_(init)(L);

	it = list->begin(list);
	while (it != list->end(list)) {
		ret = f(it);
		if ( ret )
			L->push_back(L, it);
		it = list->next(list, it);
	}

	return L;
}

int
_(remove_if) (__list *list, int (*f)(const __list_t*))
{
	int n=0;
	_(iterator) it, it1;

	it = list->begin(list);
	while (it != list->end(list)) {
		it1 = list->next(list, it);
		if ( f(it) )
			++n, list->erase(list, it);
		it = it1;
	}
	return n;
}

int
_(init) (__list *list)
{
	list->head = (_(node)*) malloc ( sizeof(_(node)) );
	if ( ! list->head )
		return 0;
	list->tail = (_(node)*) malloc ( sizeof(_(node)) );
	if ( ! list->tail ) {
		free ( list->head );
		return 0;
	}
	list->head->prev = NULL;
	list->head->next = list->tail;
	list->tail->prev = list->head;
	list->tail->next = NULL;
	list->_size = 0;

	list->front = _(front);
	list->back = _(back);

	list->begin = _(first);
	list->end = _(tail);
	list->rbegin = _(last);
	list->rend = _(head);
	list->prev = _(prev);
	list->next = _(next);

	list->empty = _(empty);
	list->size = _(size);
	list->clear = _(clear);
	list->assign = _(assign);

	list->insert = _(insert);
	list->erase = _(erase);
	list->push_back = _(push_back);
	list->push_front = _(push_front);
	list->pop_back = _(pop_back);
	list->pop_front = _(pop_front);

	list->write = _(write);
	list->read = _(read);
	list->save = _(save);
	list->load = _(load);

	list->traverse = _(traverse);
	list->rtraverse = _(rtraverse);
	list->find_if = _(find_if);
	list->remove_if = _(remove_if);

	list->destroy = _(destroy);

	list->set_copyer = _(set_copyer);
	list->set_destructor = _(set_destructor);

	return 1;
}

