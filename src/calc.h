#ifndef _CALC_H_INCLUDED_
#define _CALC_H_INCLUDED_

enum {
  error_parse   = 1,
  error_convert = 2,
  error_eval    = 3
};

int calc(const char*, double*);

#endif /* _CALC_H_INCLUDED_ */

