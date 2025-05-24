#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <stdlib.h>
#include "list.h"
}

#define ITEM_NUM 10

struct item_type {
  int value;
};

Item get_test_item(int value);

bool is_item(Item itm);

void populate_list(List list, unsigned int max);

void clear_list(List list);

void delete_item(Item itm);

TEST(new_list, returns_pointer_to_new_list) {
  List list = new_list();
  EXPECT_THAT(list, testing::NotNull());
  clear_list(list);
}

TEST(add_item, returns_number_of_items) {
  List list = new_list();
  EXPECT_EQ(add_item(list, get_test_item(1)), 1);
  EXPECT_EQ(add_item(list, get_test_item(2)), 2);
  clear_list(list);
}

TEST(remove_item, returns_and_delete_removed_item) {
  List list = new_list();
  populate_list(list, ITEM_NUM);
  EXPECT_THAT(remove_item(list, is_item), testing::NotNull());
  EXPECT_THAT(remove_item(list, is_item), testing::IsNull());
  clear_list(list);
}

TEST(remove_item, returns_null_pointer_when_not_found) {
  List list = new_list();
  populate_list(list, ITEM_NUM - 1);
  EXPECT_THAT(remove_item(list, is_item), testing::IsNull());
  clear_list(list);
}

TEST(get_item, returns_item_without_removing_it) {
  List list = new_list();
  populate_list(list, ITEM_NUM);
  EXPECT_THAT(get_item(list, is_item), testing::NotNull());
  EXPECT_THAT(get_item(list, is_item), testing::NotNull());
  clear_list(list);
}

TEST(get_item, returns_null_pointer_when_not_found) {
  List list = new_list();
  populate_list(list, ITEM_NUM - 1);
  EXPECT_THAT(get_item(list, is_item), testing::IsNull());
  clear_list(list);
}

Item get_test_item(int value) {
  Item itm = (struct item_type *) malloc(sizeof(struct item_type));
  if (itm == NULL) exit(EXIT_FAILURE);
  itm->value = value;
  return itm;
}


bool is_item(Item itm) {
  return itm->value == ITEM_NUM;
}

void populate_list(List list, unsigned int max) {
  for (int i = 1; i <= max; i++) {
    add_item(list, get_test_item(i));
  }
}

void clear_list(List list) {
  for_each(list, delete_item);
  delete_list(list);
}


void delete_item(Item itm) {
  free(itm);
}
