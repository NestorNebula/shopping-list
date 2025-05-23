#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include "item.h"
}

#define NAME "Item name"
#define QUANTITY 1
#define TYPE "Test item"

TEST(new_item, returns_item_pointer) {
  Item itm = new_item();
  EXPECT_THAT(itm, testing::NotNull());
  delete_item(itm);
}

TEST(set_item_name, returns_new_name) {
  Item itm = new_item();
  EXPECT_STREQ(set_item_name(itm, NAME), NAME);
  delete_item(itm);
}

TEST(set_item_quantity, returns_new_quantity) {
  Item itm = new_item();
  EXPECT_EQ(set_item_quantity(itm, QUANTITY), QUANTITY);
  delete_item(itm);
}

TEST(set_item_type, returns_new_type) {
  Item itm = new_item();
  EXPECT_STREQ(set_item_type(itm, TYPE), TYPE);
  delete_item(itm);
}

TEST(get_item_name, returns_empty_string_when_name_not_set) {
  Item itm = new_item();
  EXPECT_THAT((const char *) get_item_name(itm), testing::IsEmpty());
  delete_item(itm);
}

TEST(get_item_name, returns_item_name) {
  Item itm = new_item();
  set_item_name(itm, NAME);
  EXPECT_STREQ(get_item_name(itm), NAME);
  delete_item(itm);
}

TEST(get_item_quantity, returns_zero_when_quantity_not_set) {
  Item itm = new_item();
  EXPECT_EQ(get_item_quantity(itm), 0);
  delete_item(itm);
}

TEST(get_item_quantity, returns_item_quantity) {
  Item itm = new_item();
  set_item_quantity(itm, QUANTITY);
  EXPECT_EQ(get_item_quantity(itm), QUANTITY);
  delete_item(itm);
}

TEST(get_item_type, returns_empty_string_when_type_not_set) {
  Item itm = new_item();
  EXPECT_THAT((const char *) get_item_type(itm), testing::IsEmpty());
  delete_item(itm);
}

TEST(get_item_type, returns_item_type) {
  Item itm = new_item();
  set_item_type(itm, TYPE);
  EXPECT_STREQ(set_item_type(itm, TYPE), TYPE);
  delete_item(itm);
}
