#ifndef _LOCALE_H_INCLUDED_
#define _LOCALE_H_INCLUDED_

#include <libintl.h>

#define _(STR) gettext(STR)
#define N_(STR) (STR)

void setup_locale(int);

#endif /* _LOCALE_H_INCLUDED_ */

