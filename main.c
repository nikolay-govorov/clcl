#include <stdio.h>

#include "log.h"
#include "calc.h"

int main(int argc, char **argv)
{
  int error;
  double result;

  if (argc != 2) {
    calc_log(Error, "required one arg with arithmetic expression");
    return 1;
  }

  calc(argv[1], &result, &error);

  if (error) {
    calc_log(Error, "invalid expression");
    return 2;
  }

  printf("%s = %f\n", argv[1], result);

  return 0;
}

