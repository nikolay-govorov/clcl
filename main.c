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

  error = calc(argv[1], &result);
  if (error != 0) {
    switch(error) {
      case error_parse:
        calc_log(Error, _("invalid expression"));
        break;

      case error_convert:
        calc_log(Error, _("invalid expression"));
        break;

      case error_eval:
        calc_log(Error, _("invalid expression"));
        break;
    }

    return 2;
  }

  printf("%f\n", result);

  return 0;
}

