#ifndef LIST_H
#define LIST_H

#include "types.h"
#include <stdbool.h>

/*
 * List:
 * List is a type defined in the types.h header.
 * List is a pointer to a structure representing a list.
 * In this header file's comments, the word "list" will be used to
 * describe the list's structure pointed by a List argument.
 */

 /*
  * new_list:
  * Creates a new list and returns it if no error occurs,
  * else returns a null pointer.
  */
 List new_list(void);

 /*
  * delete_list:
  * Releases the memory taken by the list.
  * Note that it will not delete the items inside the list,
  * only the space taken by their pointers will be released.
  */
 void delete_list(List list);

 /*
  * add_item:
  * Adds itm to the list.
  * If no error occurred, returns the number of element in the list 
  * after adding itm, else returns -1.
  */
 int add_item(List list, Item itm);

 /*
  * remove_item:
  * Searches the item to remove from the list using the is_item function.
  * If item found, removes it from the list and returns it, otherwise
  * returns a null pointer.
  */
 Item remove_item(List list, bool (*is_item)(Item itm));

 /*
  * get_item:
  * Searches an item in the list using the is_item function.
  * If item found, returns it, otherwise returns a null pointer.
  */
 Item get_item(List list, bool (*is_item)(Item itm));

 /*
  * for_each:
  * Calls the func function once per item in the list, 
  * passing each one as the function's argument.
  */
 void for_each(List list, void (*func)(Item itm));

 /*
  * order_list:
  * Orders the list using the compare_items function, 
  * that takes two items pointers and returns an integer 
  * after comparing the items.
  */
 void order_list(List list, 
                 int (*compare_items)(const void *itm1, const void *itm2));

#endif
