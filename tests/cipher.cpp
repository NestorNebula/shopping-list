#include <gtest/gtest.h>

extern "C" {
#include "cipher.h"
}

TEST(encrypt_str, works_on_normal_string) {
  char str[] = "test";
  EXPECT_STREQ(encrypt_str(str, 3), "whvw");
}

TEST(encrypt_str, keeps_letters_case) {
  char str[] = "TeSt";
  EXPECT_STREQ(encrypt_str(str, 3), "WhVw");
}

TEST(encrypt_str, lets_non_alphabetical_characters_unchanged) {
  char str[] = "Error: 418";
  EXPECT_STREQ(encrypt_str(str, 1), "Fssps: 418");
}

TEST(decrypt_str, works_on_normal_string) {
  char str[] = "whvw";
  EXPECT_STREQ(decrypt_str(str, 3), "test");
}

TEST(decrypt_str, keeps_letters_case) {
  char str[] = "WhVw";
  EXPECT_STREQ(decrypt_str(str, 3), "TeSt");
}

TEST(decrypt_str, lets_non_alphabetical_characters_unchanged) {
  char str[] = "Fssps: 418";
  EXPECT_STREQ(decrypt_str(str, 1), "Error: 418");
}
