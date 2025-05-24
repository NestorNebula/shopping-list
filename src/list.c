#include <stdlib.h>
#include "list.h"

#define DEF_SIZE 1

struct list_type {
  Item *items;
  int length, size;
};

/*
 * find_item:
 * Searches for an item inside the list using the is_item function.
 * Returns the item's index if it was found, else returns -1.
 */
static int find_item(List list, bool (*is_item)(Item itm));

List new_list(void) {
  List list = malloc(sizeof(struct list_type));
  if (list == NULL) return list;
  list->items = malloc(sizeof(Item) * DEF_SIZE);
  if (list->items == NULL) {
    free(list);
    return NULL;
  }
  list->length = 0;
  list->size = DEF_SIZE;
  return list;
}

void delete_list(List list) {
  free(list->items);
  free(list);
}

int add_item(List list, Item itm) {
  if (list->length == list->size) {
    Item *larger_list = realloc(list->items, sizeof(Item) * list->size * 2);
    if (larger_list == NULL) return -1;
    list->items = larger_list;
    list->size *= 2;
  }
  list->items[list->length++] = itm;
  return list->length;
}

Item remove_item(List list, bool (*is_item)(Item itm)) {
  int index = find_item(list, is_item);
  if (index == -1) return NULL;
  Item removed_item = list->items[index];
  for (; index < list->length; index++) {
    list->items[index] = list->items[index + 1];
  }
  list->length--;
  return removed_item;
}

Item get_item(List list, bool (*is_item)(Item itm)) {
  int index = find_item(list, is_item);
  return index == -1 ? NULL : list->items[index];
}

void for_each(List list, void (*func)(Item itm)) {
  for (int i = 0; i < list->length; i++) {
    (*func)(list->items[i]);
  }
}

void order_list(List list, 
                int (*compare_items)(const void *itm1, const void *itm2)) {
  qsort(list->items, list->length, sizeof(Item), compare_items);
}

static int find_item(List list, bool (*is_item)(Item itm)) {
  int i;
  for (i = 0; i < list->length; i++) {
    if ((*is_item)(list->items[i])) break;
  }
  return i == list->length ? -1 : i;
}
