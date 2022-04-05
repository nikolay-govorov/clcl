#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_MAX_SIZE 255

typedef char* list_value;

struct list_node {
  char value[TOKEN_MAX_SIZE];
  struct list_node *next;
};
typedef struct list_node list_node_t;

struct list {
  list_node_t *head, *tail;
};
typedef struct list list_t;

void list_append(list_t *list, char *value) {
  list_node_t *item = malloc(sizeof(list_node_t));
  strcpy(item->value, value);
  item->next = NULL;

  if (list->head == NULL) {
    list->head = list->tail = item;
  } else {
    list->tail->next = item;
    list->tail = item;
  }
}

void list_print(list_t *list) {
  list_node_t *ptr = list->head;

  for (; ptr; ptr = ptr->next) {
    printf("-> %s\n", ptr->value);
  }
}

void calc(const char *expression, double *result, int *error)
{
  list_t *head = NULL;
  const char *cur = NULL;

  head = malloc(sizeof(list_t));
  head->head = NULL;
  head->tail = NULL;

  /* 1. Parse on tokens */
  for (cur = expression; *cur; cur++)
  {
    char token[TOKEN_MAX_SIZE] = { 0 };

    /* skip space */
    if (*cur == ' ' || *cur == '\n' || *cur == '\t')
    {
      continue;
    }

    /* 1-9 */
    if ((*cur >= '0' && *cur <= '9') || *cur == '.')
    {
      int size = 0;

      while (*cur && ((*cur >= '0' && *cur <= '9') || *cur == '.'))
      {
        if (size >= (TOKEN_MAX_SIZE - 1)) {
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

      list_append(head, token);

      continue;
    }

    if (
      *cur == '(' || *cur == ')' ||
      *cur == '+' || *cur == '-' ||
      *cur == '*' || *cur == '/' || *cur == '^'
    )
    {
      token[0] = *cur;
      token[1] = '\0';

      list_append(head, token);

      continue;
    }
  }

  /* 2. Convert to RPN */
  /* 3. Calc */

  list_print(head);

  *error = 0;
  *result = 1.0;
}

