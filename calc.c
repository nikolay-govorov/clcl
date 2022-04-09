#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calc.h"
#include "structs/stack.h"
#include "structs/list.h"

/* 1. Parse the expression */
enum { token_max_size = 255 };

enum token_type {
  number    = 1,
  bracket   = 2,
  operation = 3
};

union expr_token_data {
  double number;
  char   bracket;   /* () {} [] */
  char   operation; /* + - * / ^ */
};

struct expr_token {
  enum token_type type;
  union expr_token_data data;
};
typedef struct expr_token expr_token_t;

int expr_to_tokens(const char *expression, list_t *expr_list)
{
  const char *cur = NULL;

  for (cur = expression; *cur; cur++) {
    expr_token_t *token;

    /* skip space */
    if (*cur == ' ' || *cur == '\n' || *cur == '\t') {
      continue;
    }

    token = malloc(sizeof(expr_token_t));

    /* 1-9 */
    if ((*cur >= '0' && *cur <= '9')) {
      int size = 0;
      char buffer[token_max_size];
      memset(buffer, 0, sizeof(buffer));

      token->type = number;

      while (*cur && ((*cur >= '0' && *cur <= '9') || *cur == '.')) {
        if (size >= (token_max_size - 1)) {
          return 1;
        }

        buffer[size] = *cur;

        size++;
        cur++;
      }
      cur--;

      sscanf(buffer, "%le", &token->data.number);
      list_append(expr_list, token);

      continue;
    }

    /* brackets */
    if (*cur == '(' || *cur == ')') {
      token->type = bracket;
      token->data.bracket = *cur;

      list_append(expr_list, token);

      continue;
    }

    /* brackets and signs of arithmetic operations */
    if (
      *cur == '+' || *cur == '-' ||
      *cur == '*' || *cur == '/' || *cur == '^'
    ) {
      token->type = operation;
      token->data.operation = *cur;

      list_append(expr_list, token);

      continue;
    }

    /* Unknown symbol */
    return 1;
  }

  return 0;
}

/* 2. Convert expression to RPN */
int operator_priority(char operator)
{
  switch(operator) {
    case '^':
      return 3;

    case '*':
    case '/':
      return 2;

    case '-':
    case '+':
      return 1;
  }

  return -1;
}

int tokens_to_rpn(const list_t *tokens, list_t *rpn)
{
  expr_token_t *current;
  list_node_t *ptr;
  stack_t *st = stack_create();

  for (ptr = tokens->head; ptr; ptr = ptr->next) {
    expr_token_t *token = ptr->payload, *copy;

    switch(token->type) {
      case number:
        copy = malloc(sizeof(expr_token_t));
        copy->type = token->type;
        copy->data.number = token->data.number;

        list_append(rpn, copy);

        break;

      case bracket:
        if (token->data.bracket == '(') {
          copy = malloc(sizeof(expr_token_t));
          copy->type = token->type;
          copy->data.bracket = token->data.bracket;

          stack_push(st, copy);
        } else {

          while (stack_size(st) != 0) {
            current = stack_pop(st);

            if (current->type == bracket) {
              break;
            }

            list_append(rpn, current);
          }
        }

        break;

      case operation:
        while (
          stack_size(st) > 0 &&
          (current = stack_get(st))->type == operation
        ) {
          if (
            operator_priority(current->data.operation) >= operator_priority(token->data.operation)
          ) {
            list_append(rpn, current);
            stack_pop(st);
            continue;
          }

          break;
        }

        copy = malloc(sizeof(expr_token_t));
        copy->type = token->type;
        copy->data.operation = token->data.operation;

        stack_push(st, copy);

        break;
    }
  }

  while(stack_size(st) != 0) {
    current = stack_pop(st);

    if (current->type == bracket) {
      return 1;
    }

    list_append(rpn, current);
  }

  return 0;
}

/* 3. Evaluate expression */
int eval_rpn()
{
  return 0;
}

/* utils */
void print_token(const list_node_t *node)
{
  expr_token_t *token = node->payload;
  switch (token->type) {
    case number:
      printf("'[%i] %g' ", token->type, token->data.number);
      break;

    case bracket:
      printf("'[%i] %c' ", token->type, token->data.bracket);
      break;

    case operation:
      printf("'[%i] %c' ", token->type, token->data.operation);
      break;
  }
}

void print_rpn(const list_node_t *node)
{
  expr_token_t *token = node->payload;
  switch (token->type) {
    case number:
      printf("%g ", token->data.number);
      break;

    case bracket:
      printf("%c ", token->data.bracket);
      break;

    case operation:
      printf("%c ", token->data.operation);
      break;
  }
}

int calc(const char *expression, double *result)
{
  int step_error;

  list_t *expr_list = list_create();
  list_t *rpn_list = list_create();

  /*********************************************************/
  /* Parse to tokens */
  step_error = expr_to_tokens(expression, expr_list);
  if (step_error != 0) {
    return error_parse;
  }

  printf("\nTokens: \n\t");
  list_traverse(expr_list, &print_token);
  printf("\n");

  /*********************************************************/
  /* Convert infix notation to RPN */
  step_error = tokens_to_rpn(expr_list, rpn_list);
  if (step_error != 0) {
    return error_convert;
  }

  printf("\nRPN: \n\t");
  list_traverse(rpn_list, &print_rpn);
  printf("\n");

  /*********************************************************/
  /* Eval RPN to result */
  step_error = eval_rpn();
  if (step_error != 0) {
    return error_eval;
  }

  /* 4. Free memory */
  list_free(expr_list);
  list_free(rpn_list);

  *result = 1.0;
  return 0;
}

