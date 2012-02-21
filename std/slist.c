#include "std/memory.h"
#include "std/slist.h"
#include "std/atompool.h"

typedef struct SNode {
  struct SNode *prev;
  struct SNode *next;
  void *item;
} SNodeT;

struct SList {
  SNodeT *first;
  SNodeT *last;
  int items;

  AtomPoolT *pool;
};

SListT *NewSList() {
  SListT *list = NEW_S(SListT);

  list->pool = NewAtomPool(sizeof(SNodeT), 32);
  
  return list;
}

void ResetSList(SListT *list) {
  ResetAtomPool(list->pool);

  list->first = NULL;
  list->last = NULL;
  list->items = 0;
}

void DeleteSList(SListT *list) {
  if (list) {
    DeleteAtomPool(list->pool);
    DELETE(list);
  }
}

void *SL_ForEach(SListT *list, IterFuncT func, void *data) {
  SNodeT *node = list->first;

  while (node) {
    if (!func(node->item, data))
      break;

    node = node->next;
  }

  return node ? node->item : NULL;
}

void *SL_GetNth(SListT *list, size_t index) {
  if (index < list->items) {
    SNodeT *node = list->first;

    while (index--)
      node = node->next;

    return node->item;
  }

  return NULL;
}

static SNodeT *NodePopBack(SListT *list) {
  SNodeT *node = list->last;

  if (node) {
    if (list->first == node)
      list->first = NULL;
    else
      node->prev->next = NULL;

    list->last = node->prev;
    list->items--;
  }

  return node;
}

static SNodeT *NodePopFront(SListT *list) {
  SNodeT *node = list->first;

  if (node) {
    if (list->last == node)
      list->last = NULL;
    else
      node->next->prev = NULL;

    list->first = node->next;
    list->items--;
  }

  return node;
}

static void NodePushBack(SListT *list, SNodeT *node) {
  node->prev = list->last;
  node->next = NULL;

  if (!list->first)
    list->first = node;

  list->last = node;
  list->items++;
}

static void NodePushFront(SListT *list, SNodeT *node) {
  node->prev = NULL;
  node->next = list->first;
  
  if (!list->last)
    list->last = node;

  list->first = node;
  list->items++;
}

void *SL_PopBack(SListT *list) {
  SNodeT *node = NodePopBack(list);

  void *item = (node) ? (node->item) : NULL;

  AtomFree(list->pool, node);

  return item;
}

void *SL_PopFront(SListT *list) {
  SNodeT *node = NodePopFront(list);

  void *item = (node) ? (node->item) : NULL;

  AtomFree(list->pool, node);

  return item;
}

void SL_PushBack(SListT *list, void *item) {
  SNodeT *node = AtomNew(list->pool);

  node->item = item;

  NodePushBack(list, node);
}

void SL_PushFront(SListT *list, void *item) {
  SNodeT *node = AtomNew(list->pool);

  node->item = item;

  NodePushFront(list, node);
}

size_t SL_Size(SListT *list) {
  return list->items;
}
