#ifndef LISTIO_H
#define LISTIO_H

#include <stdbool.h>
#include "types.h"

struct env_type {
  FILE *stream;
  bool visual;
};

#define MAX_NAME_LEN 30
#define MAX_TYPE_LEN 20

/*
 * read_list:
 * Reads list from file pointed by env.stream.
 * Returns the list if no error occurred, else returns a null pointer.
 */
List read_list(void);

/*
 * read_item:
 * Reads item from file pointed by env.stream.
 * Returns the item if no error occurred, else returns a null pointer.
 */
Item read_item(void);

/*
 * write_list:
 * Writes list into the file pointed by env.stream.
 * Returns 0 if no error occurred, else returns a non-zero value.
 */
int write_list(List list);

/*
 * write_item:
 * Writes item into the file pointed by env.stream.
 * If env.visual set to true, prints items in a more readable way.
 */
void write_item(Item itm);

/*
 * read_str:
 * Reads a string from stream until it meets end_char.
 * Returns a null pointer if an error occurred or if the string is empty, 
 * else returns the string read.
 */
char *read_str(char end_char);

#endif
