#include <string.h>
#include <stdlib.h>
#include "list.h"

void list_init(_List *pL, void (*destroy)(void *pdata))
{
   pL->size = 0;
   pL->destroy = destroy;
   pL->phead = NULL;
   pL->ptail = NULL;
   return;
}

void list_destroy(_List *pL)
{
      void *pdata;
      while (LIST_size(pL) > 0)
          if (list_rem_next(pL, NULL, (void **)&pdata) == 0 && pL->destroy != NULL)
                  pL->destroy(pdata);
      memset(pL, 0, sizeof(_List));
      return;
}

int list_ins_next(_List *pL, _Elem *p_left_e, const void *p)
{
      _Elem *pnE;
      if ((pnE = malloc(sizeof(_Elem))) == NULL)
      {
          return -1;
      }
      pnE->pdata = (void *)p;
      if (p_left_e == NULL)
      {
            pnE->pnext = pL->phead; // clever - covers zero and nonzero cases
            pL->phead = pnE;
            if (LIST_size(pL) == 0)
            {
                pL->ptail = pnE;
            }
      }

      else
      {
          pnE->pnext = p_left_e->pnext;
          p_left_e->pnext = pnE;
          if (p_left_e->pnext == NULL)
          {
                  pL->ptail = pnE;
          }
      }
      pL->size++;
      return 0;
}



int list_rem_next(_List *pL, _Elem *p_left_e, void **pp)
{
      if (LIST_size(pL) == 0)
        return -1;
      _Elem *p_target_e;
      if (p_left_e == NULL)
      {
            *pp = pL->phead->pdata;
            p_target_e = pL->phead;
            pL->phead = pL->phead->pnext;
            if (LIST_size(pL) == 1) pL->ptail = NULL;
      }
      else
      {
            if (p_left_e->pnext == NULL) return -1;
            *pp = p_left_e->pnext->pdata;
            p_target_e = p_left_e->pnext;
            p_left_e->pnext = p_left_e->pnext->pnext;
            if (p_left_e->pnext == NULL) pL->ptail = p_left_e;
      }
      free(p_target_e);
      pL->size--;
      return 0;
}

