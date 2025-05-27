#ifndef HELPERS_H
#define HELPERS_H

#include <stdbool.h>

/*
 * scan_line:
 * Calls scanf with format and arguments.
 * Clears every character following the scan_line call, up until the new line.
 * Returns return value of scanf call.
 */
int scan_line(char *format, ...);

/*
 * ask_question:
 * Prints question using printf using format and arguments, 
 * asking the user to answer by y (yes) or n (no).
 * Returns true if the user answered positively, false otherwise.
 */
bool ask_question(const char *question, ...);

#endif
