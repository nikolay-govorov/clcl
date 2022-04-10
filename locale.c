#include <stdio.h>
#include <locale.h>
#include <libintl.h>

#include "locale.h"

#ifndef LOCALE_BASE_DIR
#define LOCALE_BASE_DIR "."
#endif

#define TEXT_DOMAIN "clcl"

void setup_locale(int is_relative)
{
  setlocale(LC_CTYPE, "");
  setlocale(LC_MESSAGES, "");
  bindtextdomain(TEXT_DOMAIN, is_relative ? "." : LOCALE_BASE_DIR);
  textdomain(TEXT_DOMAIN);
}

