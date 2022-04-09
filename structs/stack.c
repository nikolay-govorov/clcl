#include <stdlib.h>

#include "stack.h"

stack_t *stack_create()
{
  stack_t *stack = malloc(sizeof(stack_t));
  stack->size = 0;
  stack->head = NULL;

  return stack;
}

unsigned int stack_size(stack_t *stack)
{
  return stack->size;
}

void stack_push(stack_t *stack, void *payload)
{
  stack_node_t *item = malloc(sizeof(stack_node_t));

  item->payload = payload;
  item->next = stack->head;
  stack->head = item;

  stack->size++;
}

void* stack_get(stack_t *stack)
{
  if (stack->size == 0) {
    return NULL;
  }

  return stack->head->payload;
}

void* stack_pop(stack_t *stack)
{
  void *payload;
  stack_node_t *item;

  if (stack->size == 0) {
    return NULL;
  }

  item = stack->head;
  payload = item->payload;

  stack->head = item->next;

  free(item);

  stack->size--;

  return payload;
}

