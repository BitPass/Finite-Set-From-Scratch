/* 
C89-Compatible Minimalist Set
Inspired by Kyle Loudon's Implementation
*/

#ifndef SET_H
#define SET_H
#include <stdlib.h>
#include "list.h"

typedef _List Set;

/* Public Interface */
void set_init(Set *pset, int (*match)(const void *key1, const void *key2), void (*destroy)(void *data));

#define set_destroy list_destroy
int set_insert(Set *pset, const void *pdata);
int set_remove(Set *pset, void **ppdata);
int set_union(Set *psetu, const Set *pset1, const Set *pset2);
int set_intersection(Set *pseti, const Set *pset1, const Set *pset2);
int set_difference(Set *psetd, const Set *pset1, const Set *pset2);
int set_is_member(const Set *pset, const void *pdata);
int set_is_subset(const Set *pset1, const Set *pset2);
int set_is_equal(const Set *pset1, const Set *pset2);
#define set_size(pset) ((pset)->size)
#endif
