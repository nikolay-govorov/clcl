#include <stdio.h>

#include "log.h"

void calc_log(LogLevel_t level, char *message)
{
  printf("[LOG] %s\n", message);
}

