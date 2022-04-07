#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* generic linked list */

struct list_node {
  void* value;
  struct list_node *next;
};
typedef struct list_node list_node_t;

struct list {
  list_node_t *head, *tail;
};
typedef struct list list_t;

void list_append(list_t *list, void *value)
{
  list_node_t *item = malloc(sizeof(list_node_t));
  item->value = value;
  item->next = NULL;

  if (list->head == NULL) {
    list->head = list->tail = item;
  } else {
    list->tail->next = item;
    list->tail = item;
  }
}

void list_traverse(list_t *list, void (*callback)(list_node_t*))
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

    free(tmp->value);
    free(tmp);
  }

  list->head = NULL;
  list->tail = NULL;
}

/* calc specific modules */
enum { token_max_size = 255 };

void print_token_list_item(list_node_t *node)
{
    printf("-> %s\n", (char*)node->value);
}

void calc(const char *expression, double *result, int *error)
{
  list_t *head = NULL;
  const char *cur = NULL;

  head = malloc(sizeof(list_t));
  head->head = NULL;
  head->tail = NULL;

  /* 1. Parse on tokens */
  for (cur = expression; *cur; cur++) {
    char *str;
    char token[token_max_size] = { 0 };

    /* skip space */
    if (*cur == ' ' || *cur == '\n' || *cur == '\t') {
      continue;
    }

    /* 1-9 */
    if ((*cur >= '0' && *cur <= '9') || *cur == '.') {
      int size = 0;

      while (*cur && ((*cur >= '0' && *cur <= '9') || *cur == '.')) {
        if (size >= (token_max_size - 1)) {
          *error = 1;
          *result = 0;

          return;
        }

        token[size] = *cur;
        token[size + 1] = '\0';

        size++;
        cur++;
      }
      cur--;

      str = malloc(sizeof(char) * size + 1);
      strcpy(str, token);

      list_append(head, str);

      continue;
    }

    /* brackets and signs of arithmetic operations */
    if (
      *cur == '(' || *cur == ')' ||
      *cur == '+' || *cur == '-' ||
      *cur == '*' || *cur == '/' || *cur == '^'
    ) {
      str = malloc(sizeof(char) + 1);

      str[0] = *cur;
      str[1] = '\0';

      list_append(head, str);

      continue;
    }

    /* Unknown symbol */
    *error = 1;
    *result = 0;

    return;
  }

  /* 2. Convert to RPN */
  /* 3. Calc */

  list_traverse(head, &print_token_list_item);

  list_free(head);

  *error = 0;
  *result = 1.0;
}

