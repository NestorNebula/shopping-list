#include <stdlib.h>
#include <ctype.h>
#include "cipher.h"

#define LETTERS 26

/*
 * encrypt_letter:
 * Use key to encrypt character using Caesar Cipher technique.
 * The only characters that will be encrypted are letters,
 * other characters will be left unchanged.
 * Returns the encrypted character.
 */
static char encrypt_char(char ch, int key);

char *encrypt_str(char *str, int key) {
  key = abs(key) % LETTERS;
  for (char *p = str; *p != '\0'; p++) {
    *p = encrypt_char(*p, key);
  }
  return str;
}

char *decrypt_str(char *str, int key) {
  key = (LETTERS - abs(key) % LETTERS) % LETTERS;
  for (char *p = str; *p != '\0'; p++) {
    *p = encrypt_char(*p, key);
  }
  return str;
}

static char encrypt_char(char ch, int key) {
  if (isalpha(ch)) {
    if (isupper(ch)) ch = 'A' + (ch - 'A' + key) % LETTERS;
    else ch = 'a' + (ch - 'a' + key) % LETTERS;
  }
  return ch;
}
