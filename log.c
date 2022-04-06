#include <stdio.h>

#include "log.h"
#include "locale.h"

void calc_log(LogLevel_t level, char *message)
{
  FILE *stream;
  const char *prefix;

  char *prefix_info = _("INFO");
  char *prefix_error = _("ERROR");

  switch (level)
  {
    case Info:
      stream = stdout;
      prefix = prefix_info;
      break;

    case Error:
      stream = stderr;
      prefix = prefix_error;
      break;
  }

  fprintf(stream, "[%s]: %s\n", prefix, message);
}

