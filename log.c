#include <stdio.h>

#include "log.h"

const char prefix_info[] = "INFO";
const char prefix_error[] = "ERROR";

void calc_log(LogLevel_t level, char *message)
{
  FILE *stream;
  const char *prefix;

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

