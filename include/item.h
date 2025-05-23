#ifndef ITEM_H
#define ITEM_H

#include "types.h"

/*
 * Item:
 * Item is a type defined in the "types.h" header file.
 * Item is a pointer that points to a structure representing an item.
 * In this header file's comments, the word "item" will be used to
 * desribe the item's structure pointed by an Item argument.
 */

/*
 * new_item:
 * Creates a new item and returns a pointer to it.
 * Returns a null pointer if an error occurred.
 */
Item new_item(void);

/*
 * delete_item:
 * Releases memory taken by the item.
 */
void delete_item(Item itm);

/*
 * set_item_name:
 * Sets item's name to name.
 * Returns name if it was set correctly, else returns a null pointer.
 */
char *set_item_name(Item itm, const char *name);

/*
 * set_item_quantity:
 * Sets item's quantity to qty.
 * Returns qty.
 */
unsigned int set_item_quantity(Item itm, unsigned int qty);

/*
 * set_item_type:
 * Sets item's type to type.
 * Returns type if it was set correctly, else returns a null pointer.
 */
char *set_item_type(Item itm, const char *type);

/*
 * get_item_name:
 * Returns item's name.
 */
char *get_item_name(Item itm);

/*
 * get_item_quantity:
 * Returns item's quantity.
 */
unsigned int get_item_quantity(Item itm);

/*
 * get_item_type:
 * Returns item's type.
 */
char *get_item_type(Item itm);

#endif
