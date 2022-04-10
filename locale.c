#include <stdio.h>
#include <locale.h>
#include <libintl.h>

#include "locale.h"

#define LOCALE_BASE_DIR "."
#define TEXT_DOMAIN "clcl"

void setup_locale()
{
  setlocale(LC_CTYPE, "");
  setlocale(LC_MESSAGES, "");
  bindtextdomain(TEXT_DOMAIN, LOCALE_BASE_DIR);
  textdomain(TEXT_DOMAIN);
}

