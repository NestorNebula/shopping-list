#ifndef ITEMHELPERS_H
#define ITEMHELPERS_H

#include <stdbool.h>
#include "types.h"

/*
 * encrypt_item:
 * Encrypts itm's name and type using encrypt_str function.
 */
void encrypt_item(Item itm);

/*
 * decrypt_item:
 * Decrypts itm's name and type using decrypt_str function.
 */
void decrypt_item(Item itm);

/*
 * set_active_item:
 * Set itm as active item.
 */
void set_active_item(Item itm);

/*
 * is_item:
 * Returns true if itm has the same name as active item, 
 * else returns false.
 */
bool is_item(Item itm);

/*
 * compare_items:
 * Compare itm1 and itm2 by their type.
 * Returns a negative number if itm1 is "less than" itm2,
 * a positive number if itm1 is "greater than" itm2,
 * else returns 0.
 */
int compare_items(const void *itm1, const void *itm2);

#endif
