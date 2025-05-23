#include <stdlib.h>
#include <string.h>
#include "item.h"

struct item_type {
  char *name;
  unsigned int quantity;
  char *type;
};

/*
 * update_str:
 * Creates a new string with content of new_content, 
 * makes str_pt's pointed valued point to it and 
 * releases memory taken by old_str.
 * Returns new pointer pointed to by str_pt if no error occured,
 * else returns a null pointer.
 */
static char *update_str(char *old_str, const char *new_content, char **str_pt);

Item new_item(void) {
  Item itm = malloc(sizeof(struct item_type));
  if (itm == NULL) return itm;

  itm->name = malloc(1);
  if (itm->name == NULL) {
    free(itm);
    return NULL;
  }
  itm->name[0] = '\0';

  itm->quantity = 0;

  itm->type = malloc(1);
  if (itm->type == NULL) {
    free(itm);
    free(itm->name);
    return NULL;
  }
  itm->type[0] = '\0';

  return itm;
}

void delete_item(Item itm) {
  free(itm->type);
  free(itm->name);
  free(itm);
}

char *set_item_name(Item itm, const char *name) {
  update_str(itm->name, name, &itm->name);
  return itm->name;
}

unsigned int set_item_quantity(Item itm, unsigned int qty) {
  return (itm->quantity = qty);
}

char *set_item_type(Item itm, const char *type) {
  update_str(itm->type, type, &itm->type);
  return itm->type;
}

char *get_item_name(Item itm) {
  return itm->name;
}

unsigned int get_item_quantity(Item itm) {
  return itm->quantity;
}

char *get_item_type(Item itm) {
  return itm->type;
}

static char *update_str(char *old_str, const char *new_content, char **str_pt) {
  char *new_str = malloc(strlen(new_content + 1));
  if (new_str == NULL) return new_str;

  strcpy(new_str, new_content);
  free(old_str);
  *str_pt = new_str;

  return *str_pt;
}
