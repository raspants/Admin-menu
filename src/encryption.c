// encryption.c
#include "encryption.h"
#include "cardStructure.h"
#include "fileHandeling.h"
#include "timeDelay.h"
#include <sodium.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int encryptFile(const char *plainText, size_t len, const char *filename, const char *password){

    CryptoContext ctx;

    randombytes_buf(ctx.salt, sizeof ctx.salt); // Generate salt

    if (deriveKey(ctx.key, password, ctx.salt) != 0) {  //Derive key from password + salt
        return -1;
    }
 
    randombytes_buf(ctx.nonce, sizeof ctx.nonce); //Generate  random nonce


    size_t cipher_size = len + crypto_secretbox_MACBYTES;
    unsigned char *ciphertext = malloc(cipher_size);
    
    if (!ciphertext) {
        return -1;
    }

    if (crypto_secretbox_easy(ciphertext, (const unsigned char *)plainText, len, //encrypt
                              ctx.nonce, ctx.key) != 0)
    {
        free(ciphertext);
        return -1; // Should not occur unless libsodium fails
    }

    FILE *fp = fopen(filename, "wb"); //Write salt + nonce + ciphertext to file
    if (!fp) {
        free(ciphertext);
        return -1;
    }

    fwrite(ctx.salt, 1, sizeof ctx.salt, fp);
    fwrite(ctx.nonce, 1, sizeof ctx.nonce, fp);
    fwrite(ciphertext, 1, cipher_size, fp);
    fclose(fp);

    sodium_memzero(ctx.key, sizeof ctx.key); //Cleanup sensitive data
    free(ciphertext);

    return 0; // Success
}

int decryptFile( char **plainText, size_t *len, const char *filename, const char *password){

    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        return -1; // Missing file
    }

    CryptoContext ctx;

    if (fread(ctx.salt, 1, sizeof ctx.salt, fp) != sizeof ctx.salt) {
        fclose(fp);
        return -1;
    }

    if (fread(ctx.nonce, 1, sizeof ctx.nonce, fp) != sizeof ctx.nonce) {
        fclose(fp);
        return -1;
    }

    if (deriveKey(ctx.key, password, ctx.salt) != 0) { // Derive the key from password + salt
        fclose(fp);
        return -1;
    }

    fseek(fp, 0, SEEK_END);//  Determine the text size
    long file_size = ftell(fp);
    long cipher_size = file_size - sizeof ctx.salt - sizeof ctx.nonce;
    fseek(fp, sizeof ctx.salt + sizeof ctx.nonce, SEEK_SET);

    if (cipher_size <= 0) {
        fclose(fp);
        return -1; // Corrupt file
    }

    unsigned char *ciphertext = malloc(cipher_size); //Allocate ciphertext buffer
    if (!ciphertext) {
        fclose(fp);
        return -1;
    }

    fread(ciphertext, 1, cipher_size, fp);
    fclose(fp);

    *plainText = malloc(cipher_size - crypto_secretbox_MACBYTES); //Allocate plaintext buffer for output
    if (!*plainText) {
        free(ciphertext);
        return -1;
    }

    if (crypto_secretbox_open_easy((unsigned char *)*plainText, ciphertext, cipher_size, ctx.nonce, ctx.key) != 0){ //Decrypt
        
        // Wrong password or corrupted file
        free(ciphertext);
        free(*plainText);
        *plainText = NULL;
        return -1;
    }

    *len = cipher_size - crypto_secretbox_MACBYTES;

    free(ciphertext);
    return 0; 
}

int deriveKey(unsigned char key[crypto_secretbox_KEYBYTES],const char *password, const unsigned char salt[crypto_pwhash_SALTBYTES]){
    if(crypto_pwhash(key, crypto_secretbox_KEYBYTES, password, strlen(password), salt, crypto_pwhash_OPSLIMIT_INTERACTIVE, 
                          crypto_pwhash_MEMLIMIT_INTERACTIVE, crypto_pwhash_ALG_DEFAULT) !=0){

        printf("Failed to derive key");
        timeDelay(2);
        return -1;
    }
    return 0;
}

int encryptFileFromBuffer(const char *buff, size_t length, const char *filename, const char *password){
    return encryptFile(buff, length, filename, password);
}


void saveEncryptedCardList(const char *filename, CARDLIST *cardList, const char *password){
    char *buff = NULL;
    size_t length = 0;
    buff = wrightToFileBuffer(cardList, &length);

    if(encryptFileFromBuffer(buff, length, filename, password) != 0){
        printf("Failed to store encrypted data!\n");
        timeDelay(2);
    }
    free(buff);
    return;
}



