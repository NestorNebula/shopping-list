#ifndef CIPHER_H
#define CIPHER_H

/*
 * encrypt_str:
 * Encrypts str using the Caesar Cipher technique.
 * The encryption is done in-place, thus modifying the original string.
 * Returns a pointer to the encrypted string.
 */
char *encrypt_str(char *str, int key);

/*
 * decrypt_str:
 * Decrypts str using the Caesar Cipher technique.
 * The decryption is done in-place, thus modifying the original string.
 * Returns a pointer to the decrypted string.
 */
char *decrypt_str(char *str, int key);

#endif
