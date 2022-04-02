#ifndef CALLS_H
#define CALLS_H

typedef enum { Info, Error } LogLevel_t;

void calc_log(LogLevel_t level, char *message);

#endif

