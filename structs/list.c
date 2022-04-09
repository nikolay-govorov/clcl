#include <stdlib.h>

#include "list.h"

list_t *list_create()
{
  list_t *list = malloc(sizeof(list_t));

  list->size = 0;
  list->head = NULL;
  list->tail = NULL;

  return list;
}

void list_append(list_t *list, void *payload)
{
  list_node_t *item = malloc(sizeof(list_node_t));
  item->payload = payload;
  item->next = NULL;

  if (list->head == NULL) {
    list->head = list->tail = item;
  } else {
    list->tail->next = item;
    list->tail = item;
  }
}

void list_traverse(list_t *list, void (*callback)(const list_node_t*))
{
  list_node_t *ptr = list->head;

  for (; ptr; ptr = ptr->next) {
    callback(ptr);
  }
}

void list_free(list_t *list)
{
  list_node_t *cur = list->head, *tmp;

  while (cur) {
    tmp = cur;
    cur = cur->next;

    free(tmp->payload);
    free(tmp);
  }

  list->size = 0;
  list->head = NULL;
  list->tail = NULL;

  free(list);
}

