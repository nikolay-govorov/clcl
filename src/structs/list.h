#ifndef _LIST_H_INCLUDED_
#define _LIST_H_INCLUDED_

struct list_node {
  void *payload;
  struct list_node *next;
};
typedef struct list_node list_node_t;

struct list {
  unsigned int size;
  struct list_node *head, *tail;
};
typedef struct list list_t;

list_t *list_create();

void list_append(list_t*, void*);
void list_traverse(list_t*, void (*callback)(const list_node_t*));
void list_free(list_t*);

#endif /* _LIST_H_INCLUDED_ */

