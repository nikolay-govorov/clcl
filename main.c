#include <stdio.h>

#include "locale.h"
#include "calc.h"

void log_error(const char *message)
{
  fprintf(stderr, "[%s]: %s\n", _("ERROR"), message);
}

int main(int argc, char **argv)
{
  int error;
  double result;

  setup_locale();

  if (argc != 2) {
    log_error(_("one argument is required and must be an arithmetic expression"));
    return 1;
  }

  error = calc(argv[1], &result);
  if (error != 0) {
    switch(error) {
      case error_parse:
        log_error(_("invalid expression"));
        break;

      case error_convert:
        log_error(_("invalid expression"));
        break;

      case error_eval:
        log_error(_("invalid expression"));
        break;
    }

    return 2;
  }

  printf("%g\n", result);

  return 0;
}

