#ifndef CALC_H
#define CALC_H

enum {
  error_parse   = 1,
  error_convert = 2,
  error_eval    = 3
};

int calc(const char*, double*);

#endif

