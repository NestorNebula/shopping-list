#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "list.h"
#include "listio.h"

struct env_type env = { NULL, false };

List read_list(void) {
  List list = new_list();
  if (list == NULL) return list;
  while (!ferror(env.stream) && !feof(env.stream)) {
    Item itm = read_item();
    if (itm == NULL) break;
    add_item(list, itm);
  }
  return list;
}

Item read_item(void) {
  Item itm = new_item();
  if (itm == NULL) return NULL;
  char *name = read_str('\n');
  if (name == NULL) {
    delete_item(itm);
    return NULL;
  }
  set_item_name(itm, name);
  free(name);
  int quantity;
  if (!fscanf(env.stream, "%d", &quantity)) {
    delete_item(itm);
    return NULL;
  }
  set_item_quantity(itm, quantity);
  getc(env.stream);
  char *type = read_str('\n');
  if (type == NULL) {
    delete_item(itm);
    return NULL;
  }
  set_item_type(itm, type);
  free(type);
  return itm;
}

int write_list(List list) {
  if (env.visual) {
    fprintf(env.stream, "%-*.*s | %s | %s\n",
            MAX_NAME_LEN, MAX_NAME_LEN, "Name",
            "Quantity",
            "Type");
    int line_len = MAX_NAME_LEN + strlen("Quantity") + 
      MAX_TYPE_LEN + (strlen(" | ") * 2);
    for (int i = 0; i < line_len; i++) fprintf(env.stream, "-");
    fprintf(env.stream, "\n");
  }

  for_each(list, write_item);
  return !feof(env.stream) && !ferror(env.stream);
}


void write_item(Item itm) {
  char *name = get_item_name(itm), *type = get_item_type(itm);
  int quantity = get_item_quantity(itm);
  if (env.visual) {
    fprintf(env.stream, "%-*.*s | %8d | %-*.*s\n",
            MAX_NAME_LEN, MAX_NAME_LEN, name,
            quantity,
            MAX_TYPE_LEN, MAX_TYPE_LEN, type);
  } else {
    fprintf(env.stream, "%s\n%d\n%s\n", name, quantity, type);
  }
}

char *read_str(char end_char) {
  int size = 1, length = 0, ch;
  char *str = malloc(size);
  if (str == NULL) return str;
  str[0] = '\0';
  while ((ch = getc(env.stream)) != end_char && ch != EOF) {
    if (length + 1 == size) {
      str = realloc(str, size * 2);
      if (str == NULL) return str;
      size *= 2;
    }
    str[length++] = ch;
  };
  if (ch == end_char) return str;
  free(str);
  return NULL;
}
