#include <stdio.h>

#include "locale.h"
#include "log.h"
#include "calc.h"

int main(int argc, char **argv)
{
  int error;
  double result;

  setup_locale();

  if (argc != 2) {
    calc_log(Error, _("one argument is required and must be an arithmetic expression"));
    return 1;
  }

  calc(argv[1], &result, &error);

  if (error) {
    calc_log(Error, _("invalid expression"));
    return 2;
  }

  printf("%s = %f\n", argv[1], result);

  return 0;
}

