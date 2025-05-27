#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "item.h"
#include "list.h"
#include "listio.h"
#include "itemhelpers.h"
#include "helpers.h"

// Used in listio functions
extern struct env_type env;

// Used in itemhelpers functions
extern Item active_item;
extern int key;

List inventory, needs, shopping_list;

/*
 * make_inventory:
 * Creates a list called list_name with previous file and user inputs.
 * Returns the list if no error occurred, else exits program prematurely.
 */
List make_list(const char *list_name);

/*
 * handle_lists_saving:
 * Offers the user to save the list called list_name in a file 
 * to be able to reuse it later.
 */
void handle_list_saving(List list, const char *list_name);

/*
 * handle_new_item:
 * Prompts the user for informations about a new item.
 * Returns the item if no error occurred, else returns a null pointer.
 */
Item handle_new_item(void);

/*
 * add_item_to_shopping_list:
 * Add need_itm to shopping_list based on the value of corresponding item
 * in inventory list.
 * If the inventory item has enough quantity to handle the quantity of
 * need_itm, doesn't add it to the list, else adds it with a quantity
 * of need_itm quantity - inventory quantity.
 */
void add_item_to_shopping_list(Item need_itm);

int main(void) {
  printf("\nThis program will create a shopping-list based on "
         "an inventory of what you already have and on a list "
         "of what you need.\n"
         "First, the program will help you create your inventory, "
         "consisting of items you already have.\n"
         "Then, the program will let you create a list of items "
         "you need, called the \"Needs\".\n"
         "Finally, based on inventory and needs, the program will "
         "create a shopping list of the items needed to complete the "
         "inventory and meet the needs.\n"
         "You will then have the possibility to save the shopping list "
         "as a text file and to save inventory and needs as files "
         "that can be reused for another run of the program.\n");

  inventory = make_list("inventory");

  env.stream = stdout;
  printf("\nInventory:\n");
  write_list(inventory);

  env.stream = NULL;
  needs = make_list("needs");

  env.stream = stdout;
  printf("\nNeeds:\n");
  write_list(needs);

  shopping_list = new_list();
  if (shopping_list == NULL) {
    printf("Not enough space to create shopping list.\n");
    exit(EXIT_FAILURE);
  }
  for_each(needs, add_item_to_shopping_list);

  order_list(shopping_list, compare_items);

  printf("\nShopping List:\n");
  write_list(shopping_list);

  if (ask_question("\nDo you want the shopping list to be "
                   "written to a file?")) {
    env.visual = true;
    char filename[FILENAME_MAX+1];
    filename[0] = '\0';
    printf("\nEnter filename: ");
    scan_line("%s", filename);
    env.stream = fopen(filename, "wb");
    if (env.stream == NULL) {
      printf("Couldn't open %s\n", filename);
    } else {
      write_list(shopping_list);
      printf("\nShopping List written in %s\n", filename);
    }
  }

  handle_list_saving(inventory, "inventory");
  handle_list_saving(needs, "needs");
}




List make_list(const char *list_name) {
  printf("\n");
  for (const char *p = list_name; *p != '\0'; p++) {
    printf("%c", toupper(*p));
  }
  printf("\n");
  if (ask_question("\nDo you want to load a previous %s file?", list_name)) {
    char filename[FILENAME_MAX+1];
    filename[0] = '\0';
    printf("\nEnter %s filename: ", list_name);
    scan_line("%s", filename);
    env.stream = fopen(filename, "rb");
    if (env.stream == NULL) {
      printf("Couldn't open %s\n", filename);
    }
  }

  // If env.stream set read list from the file, else create a new one
  List list = env.stream == NULL ? new_list() : read_list();
  if (list == NULL) {
    printf("Error during %s creation.\n", list_name);
    exit(EXIT_FAILURE);
  }
  env.visual = true;
  if (env.stream != NULL) {
    if (ask_question("\nDid you use encryption for the loaded file?")) {
      printf("Enter encryption key: ");
      scan_line("%d", &key);
      for_each(list, decrypt_item);
    }
    env.stream = stdout;
    printf("\nLoaded %s:\n", list_name);
    write_list(list);
  } else env.stream = stdout;

  env.stream = stdin;
  
  // Add items in list while user doesn't ask to stop and no error occur
  for (;;) {
    if (!ask_question("\nDo you want to enter a new item in your %s?", 
                      list_name)) break;
    Item itm = handle_new_item();
    if (itm == NULL) break;
    Item existing_item = get_item(list, is_item);

    // If item already exists in the list, update it
    if (existing_item != NULL) {
      printf("%s already exists, updating item.\n", get_item_name(itm));
      set_item_quantity(existing_item, get_item_quantity(itm));
      set_item_type(existing_item, get_item_type(itm));
      free(itm);
    } else {
      if (add_item(list, itm) == -1) {
        printf("Couldn't add item to the \"%s\" list.\n", list_name);
      } else printf("Item added\n");
    }
  }

  return list;
}

void handle_list_saving(List list, const char *list_name) {
  if (ask_question("\nDo you want to save your \"%s\" list to be able to "
                   "reuse it later?", list_name)) {
    char filename[FILENAME_MAX+1];
    filename[0] = '\0';
    printf("Enter filename to store %s: ", list_name);
    scan_line(" %s", filename);
    env.stream = fopen(filename, "wb");
    if (env.stream == NULL) {
      printf("Can't open %s\n", filename);
    } else {
      env.visual = false;
      if (ask_question("\nDo you want to encrypt data?")) {
        printf("Enter an encryption key (number): ");
        scan_line("%d", &key);
        printf("You've set the key to %d. You'll need to remember that key "
               "to decrypt the file if you want to reuse it later.\n", key);
        for_each(list, encrypt_item);
      }
      write_list(list);
      printf("\n%s saved in %s\n", list_name, filename);
    }
  }
}

Item handle_new_item(void) {
  Item itm = new_item();
  set_active_item(itm);
  if (itm == NULL) {
    printf("Not enough space for storing one more item\n");
    return itm;
  }
  char *name = NULL;

  // Prompt the user for a name until a non-emtpy name is set or an error occur
  do {
    free(name);
    printf("Enter item's name: ");
    name = read_str('\n');
    if (name == NULL) {
      printf("Error when reading name.\n");
      free(itm);
      return NULL;
    }
  } while (!strlen(name));
  
  if (set_item_name(itm, name) == NULL) {
    printf("Error when reading name.\n");
    free(name);
    free(itm);
    return NULL;
  }
  free(name);
  int quantity;
  
  // Prompt the user for a positive quantity
  do {
    printf("Enter item's quantity: ");
    scan_line("%d", &quantity);
  } while (quantity <= 0);
  set_item_quantity(itm, quantity);

  printf("Enter item's type (optional): ");
  char *type = read_str('\n');
  if (type == NULL) {
    printf("Error when reading type.\n");
    free(itm);
    return NULL;
  }
  if (set_item_type(itm, type) == NULL) {
    printf("Error when reading type.\n");
    free(type);
    free(itm);
    return NULL;
  }
  free(type);
  return itm;
}

void add_item_to_shopping_list(Item need_itm) {
  set_active_item(need_itm);
  Item inventory_itm = get_item(inventory, is_item);

  // If item isn't in inventory, add need_itm as is in the list
  if (inventory_itm == NULL) {
    add_item(shopping_list, need_itm);
    return;
  }
  int inventory_quantity = get_item_quantity(inventory_itm),
      needs_quantity = get_item_quantity(need_itm);

  /* If need_itm quantity is more than quantity in inventory,
     add item to the list with a quantity corresponding to the difference
     between need and inventory. */
  if (needs_quantity > inventory_quantity) {
    Item itm = new_item();
    if (itm == NULL) {
      printf("Couldn't add %s to shopping list.\n", get_item_name(need_itm));
    }
    set_item_name(itm, get_item_name(need_itm));
    set_item_type(itm, get_item_type(need_itm));
    set_item_quantity(itm, needs_quantity - inventory_quantity);
    if (add_item(shopping_list, itm) == -1) {
      printf("Couldn't add %s to shopping list.\n", get_item_name(need_itm));
    } 
  }
}
