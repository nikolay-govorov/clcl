#include <stdio.h>
#include <locale.h>
#include <libintl.h>

#include "locale.h"

#define LOCALEBASEDIR "."
#define TEXTDOMAIN "calculator"

void setup_locale()
{
  setlocale(LC_CTYPE, "");
  setlocale(LC_MESSAGES, "");
  bindtextdomain(TEXTDOMAIN, LOCALEBASEDIR);
  textdomain(TEXTDOMAIN);
}

