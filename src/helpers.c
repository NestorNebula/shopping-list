#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include "helpers.h"

int scan_line(char *format, ...) {
  va_list ap;
  va_start(ap, format);
  int result = vscanf(format, ap);
  va_end(ap);
  while (getchar() != '\n');
  return result;
}

bool ask_question(const char *question, ...) {
  char ch;
  va_list ap;
  do {
    va_start(ap, question);
    vprintf(question, ap);
    va_end(ap);
    printf(" (y/n) ");
    scan_line(" %c", &ch);
  } while (ch != 'y' && ch != 'n');
  return tolower(ch) == 'y';
}
