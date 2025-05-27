#include <string.h>
#include "item.h"
#include "cipher.h"
#include "itemhelpers.h"

Item active_item;
int key;

void encrypt_item(Item itm) {
  encrypt_str(get_item_name(itm), key);
  encrypt_str(get_item_type(itm), key);
}

void decrypt_item(Item itm) {
  decrypt_str(get_item_name(itm), key);
  decrypt_str(get_item_type(itm), key);
}

void set_active_item(Item itm) {
  active_item = itm;
}

bool is_item(Item itm) {
  return !strcmp(get_item_name(active_item), get_item_name(itm));
}

int compare_items(const void *itm1, const void *itm2) {
  Item i1 = *(Item *)itm1, i2 = *(Item *)itm2;
  return strcmp(get_item_type(i1), get_item_type(i2));
}
