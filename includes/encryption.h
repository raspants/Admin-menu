#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#pragma once
#include <stddef.h>
#include <sodium.h>
#include "cardStructure.h"


typedef struct {
    unsigned char salt[crypto_pwhash_SALTBYTES];
    unsigned char nonce[crypto_secretbox_NONCEBYTES];
    unsigned char key[crypto_secretbox_KEYBYTES];
} CryptoContext;



int encryptFile(const char *plainText, size_t len, const char *filename, const char *password);

int decryptFile( char **plainText, size_t *len, const char *filename, const char *password);

int deriveKey(unsigned char key[crypto_secretbox_KEYBYTES],const char *password, const unsigned char salt[crypto_pwhash_SALTBYTES]);

int encryptFileFromBuffer(const char *buff, size_t length, const char *filename, const char *password);

void saveEncryptedCardList(const char *filename, CARDLIST *cardList, const char *password);
    

#endif
