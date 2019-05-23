



#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct _Elem_s {
	void *pdata;
	struct _Elem_s *pnext;
}
_Elem;

typedef struct _List_s {
	int size;
	int (*match)(const void *key1, const void *key2);
	void (*destroy)(void *p);
	_Elem *phead;
	_Elem *ptail;
}
_List;

void list_init(_List *pL, void (*destroy)(void *p));
void list_destroy(_List *pL);

int list_ins_next(_List *pL, _Elem *p_left_e, const void *p);
int list_rem_next(_List *pL, _Elem *pE, void **pp);

#define LIST_size(pL) ((pL)->size)
#define LIST_head(pL) ((pL)->phead)
#define LIST_tail(pL) ((pL)->ptail)

#define ELEM_data(pE) ((pE)->pdata)
#define ELEM_next(pE) ((pE)->pnext)
#define ELEM_is_tail(pE) ((pE)->pnext == NULL ? 1 : 0)
#define ELEM_is_head(pL, pE) ((pE) == (pL)->phead ? 1 : 0)

#endif




