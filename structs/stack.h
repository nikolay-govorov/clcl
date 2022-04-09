#ifndef STACK_H
#define STACK_H

struct stack_node {
  void *payload;
  struct stack_node *next;
};
typedef struct stack_node stack_node_t;

struct stack {
  unsigned int size;
  struct stack_node *head;
};
typedef struct stack stack_t;

stack_t *stack_create();

unsigned int stack_size(stack_t*);
void stack_push(stack_t*, void*);
void *stack_get(stack_t*);
void *stack_pop(stack_t*);

#endif

