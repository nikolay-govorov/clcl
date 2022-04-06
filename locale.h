#ifndef LOCALE_H_HEADER
#define LOCALE_H_HEADER

#include <libintl.h>

#define _(STR) gettext(STR)
#define N_(STR) (STR)

void setup_locale();

#endif

