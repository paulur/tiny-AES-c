#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "aes.h"

void puhex(uint8_t u[]){
    int len  = strlen(u);
    for (int i=0; i < len; i++){
        printf("%02x", u[i]);
    }
    printf("\n");
}

int main(int argc, char** argv){

	uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
    uint8_t iv[]  = { 0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    
//    uint8_t plaintext[16] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
    char plaintext[256] = "0123456789012345678901234567890101234567890123456789012345678901012345678901234567890123456789010123456789012345678901234567890101234567890123456789012345678901012345678901234567890123456789010123456789012345678901234567890101234567890123456789012345678901";
    printf("--before encryption--\n");
    puhex(plaintext);
    
    AES_CBC_encrypt_buffer(&ctx, plaintext, strlen(plaintext));
    printf("--after encryption--\n");
    puhex(plaintext);
    
    struct AES_ctx de_ctx;
	uint8_t de_key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
    uint8_t de_iv[]  = { 0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
//    uint8_t ciphertext[16];
//    memcpy(ciphertext, plaintext, 16);
    AES_init_ctx_iv(&de_ctx, de_key, de_iv);
    AES_CBC_decrypt_buffer(&ctx, plaintext, strlen(plaintext));
    printf("--after decryption--\n");
    puhex(plaintext);
    
       
    AES_CBC_encrypt_buffer(&ctx, plaintext, strlen(plaintext));
    printf("--after encryption--\n");
    puhex(plaintext);
}
