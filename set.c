#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "set.h"

void set_init(Set *pset,
   int (*match)(const void *key1, const void *key2),
   void (*destroy)(void *data)
   )
   {
      list_init(pset, destroy);
      pset->match = match;      /* We finally use the match functionality in _List*/
      return;
   }

int set_insert(Set *pset, const void *pdata)
{
   /* Do not allow the insertion of duplicates */
   if (set_is_member(pset, pdata))
      return 1;
   return list_ins_next(pset, LIST_tail(pset), pdata);
}

int set_remove(Set *pset, void **ppdata)
{
   _Elem *pmember, *p_prev;     // p_prev is used as p_left_e

   /*  Find the member to remove */
   p_prev = NULL;
   for (pmember = LIST_head(pset); pmember != NULL; pmember = ELEM_next(pmember))
   {
      if (pset->match(*ppdata, ELEM_data(pmember)))
      {
         break;
      }
      p_prev = pmember;
   }

   /*  Return if the member was not found */
   if (pmember == NULL)
      return -1;

   /*  Remove the member */
   return list_rem_next(pset, p_prev, ppdata);
}

int set_union(Set *psetu, const Set *pset1, const Set *pset2)
{

   _Elem *pmember;
   void *pdata;

   /*  Initialize the set for the union */
   set_init(psetu, pset1->match, NULL);

   /* Insert the members of the first set */
   for (pmember = LIST_head(pset1); pmember != NULL; pmember = ELEM_next(pmember))
   {
      pdata = ELEM_data(pmember);
      if (list_ins_next(psetu, LIST_tail(psetu), pdata) != 0)
      {
         set_destroy(psetu);
         return -1;
      }
   }

   /*Insert the members of the second set */
   for (pmember = LIST_head(pset2); pmember != NULL; pmember = ELEM_next(pmember))
   {
      if (set_is_member(pset1, ELEM_data(pmember)))
      {
         /*  Do not allow the insertion of duplicates */
         continue;
      }

      else {
         pdata = ELEM_data(pmember);
         if (list_ins_next(psetu, LIST_tail(psetu), pdata) != 0) {
            set_destroy(psetu);
            return -1;
         }
      }
   }
   return 0;
}

int set_intersection(Set *pseti, const Set *pset1, const Set *pset2)
{
   _Elem *pmember;
   void *pdata;

   /*  Initialize the set for the intersection */
   set_init(pseti, pset1->match, NULL);

   /*  Insert the members present in both sets */
   for (pmember = LIST_head(pset1); pmember != NULL; pmember = ELEM_next(pmember)) {
      if (set_is_member(pset2, ELEM_data(pmember))) {
         pdata = ELEM_data(pmember);
         if (list_ins_next(pseti, LIST_tail(pseti), pdata) != 0) {
            set_destroy(pseti);
            return -1;
         }
      }
   }
   return 0;
}

int set_difference(Set *psetd, const Set *pset1, const Set *pset2)
{
   _Elem *pmember;
   void *pdata;

   /*  Initialize the set for the difference */
   set_init(psetd, pset1->match, NULL);
   /*  Insert the members from set1 not in set2 */
   for (pmember = LIST_head(pset1); pmember != NULL; pmember = ELEM_next(pmember)) {
      if (!set_is_member(pset2, ELEM_data(pmember))) {
         pdata = ELEM_data(pmember);
         if (list_ins_next(psetd, LIST_tail(psetd), pdata) != 0) {
            set_destroy(psetd);
            return -1;
         }
      }
   }
   return 0;
}

int set_is_member(const Set *pset, const void *pdata)
{
   _Elem *pmember;

   /*  Determine if the data is a member of the set */
   for (pmember = LIST_head(pset); pmember != NULL; pmember = ELEM_next(pmember))
   {
      if (pset->match(pdata, ELEM_data(pmember)))
         return 1;
}

return 0;

}


int set_is_subset(const Set *pset1, const Set *pset2)
{
   _Elem *pmember;

   /*  Do a quick test to rule out some cases */
   if (set_size(pset1) > set_size(pset2))
      return 0;

   /*  Determine if set1 is a subset of set2 */
   for (pmember = LIST_head(pset1); pmember != NULL; pmember = ELEM_next(pmember)) {
      if (!set_is_member(pset2, ELEM_data(pmember)))
         return 0;
   }
   return 1;
}

int set_is_equal(const Set *pset1, const Set *pset2)
{

   /* Do a quick test to rule out some cases */
   if (set_size(pset1) != set_size(pset2))
      return 0;

   /*  Sets of the same size are equal if they are subsets */
   return set_is_subset(pset1, pset2);
}
