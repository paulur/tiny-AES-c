#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "aes.h"
#include "ucsp.h"

//#define BLOCK_SIZE 16
#define TEXT_SIZE 8192
#define BLOCK_LEN 16
//
uint8_t encrypt_output[TEXT_SIZE];
//int concated_cipher_text_len;

struct padded_struct{
	uint8_t padded_text[TEXT_SIZE-BLOCK_LEN];
	uint32_t size;
} pPlaintText;


// prints string as hex
void phex(uint8_t* str){
	printf("uint8_t arch len: %d\n", BLOCK_LEN);
	
	printf("as %d hex chars:\n", strlen(str));
    int i;
    for (i = 0; i < BLOCK_LEN; ++i)
        printf("%.2x", str[i]);
    printf("\n");
    
	printf("as %d char chars:\n", strlen(str));
    
    for (i = 0; i < strlen(str); ++i)
        printf("%c", (char*)str[i]);
    printf("\n");
}

void pchar(char str[]){
    printf("print  %s in hex ==>", str);
    for (int i=0; i < strlen(str); i++){
        printf("%02x", (uint8_t)str[i]);
    }
    printf("\n");
}

void puhex(uint8_t u[]){
    for (int i=0; i < strlen(u); i++){
        printf("%02x", u[i]);
    }
    printf("\n");
}


/**
 * @brief 
 * 	String length must be evenly divisible by 16byte (str_len % 16 == 0)
        You should pad the end of the string with zeros if this is not the case.
        For AES192/256 the key size is proportionally larger.
 * @param plaintext
 * @return 
 */
void pad(char plaintext[]){

	int plainLen = strlen(plaintext);
	if (!plainLen){
		printf("plainLen is zero");
		exit(0);
	}
		 
    printf("do base64 for encoding..");
    char* encoded_text = malloc(sizeof(char) * Base64encode_len(plainLen));
    int textLen = Base64encode(encoded_text, plaintext, plainLen);
    printf("base64 encoded_text: %s, base64len: %d\n", encoded_text, Base64encode_len(plainLen));
    
    //remove the '\0' at the end of encoded input
	int remainder = (textLen - 1) % BLOCK_LEN;
    if(!remainder){
        printf("length %d, remainder of %s is %d, no need padding.\n", textLen -1 , encoded_text, remainder);
        memcpy(pPlaintText.padded_text, encoded_text, textLen - 1);
        pPlaintText.size = textLen - 1;
        return;
    }
    
	int numPad = BLOCK_LEN - remainder;
	printf("input of pad: %s\n\t length:%d, remainder %d, need %d pad.\n", encoded_text, textLen - 1, remainder, numPad);

	pPlaintText.size = textLen -1 + numPad;
	memcpy(pPlaintText.padded_text, encoded_text, textLen - 1);
	int i = 0;
	
	memcpy(pPlaintText.padded_text + textLen - 1 + i++, " ", 1);
	for (; i < numPad; i++){
		memcpy(pPlaintText.padded_text + textLen  - 1 + i, "0", 1);
	}  
}

char* depad(char paddedPlainText[]){
    int index = -1;
	
    for (int i = 0; i < strlen(paddedPlainText); i++)
        if (paddedPlainText[i] == ' ')
            index = i;
	printf("the index of last space of\n\t%s is %d\n", paddedPlainText, index);
	
	char* depaddedPlaintext = malloc(sizeof(char) * index);
	strncpy(depaddedPlaintext, paddedPlainText, index);
	
	
	printf("depadded plaintext: %s\n", depaddedPlaintext);
	return depaddedPlaintext;
}


uint8_t* build_iv(){
    uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    return iv;
    
//    int size = BLOCK_LEN;
//    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
//    srand(time(NULL));
//    if (size) {
//        for (size_t n = 0; n < size; n++) {
//            int key = rand() % (int) (sizeof charset - 1);
//            IV[n] = (uint8_t)charset[key];
//        }
//        --size;
//    }
//    memcpy(IV, iv, BLOCK_LEN);
//    
//    printf("build iv: ");
//    phex(IV);
}

/**
 * @brief 
 * @param key
 * @param plaintext
 * @return concated uint8_t: iv  + ciphertext 
 */
void encrypt(uint8_t key[], char* plaintext){
    printf("\n--AES cbc client encrypt--\n");
    
    printf("-key: length %d: \n\t", strlen(key));
    puhex(key);

    uint8_t iv[]  = { 0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    printf("-IV:\n\t");
    puhex(iv);
    
    
    uint8_t* iv_bk = (uint8_t*)malloc(sizeof(uint8_t) * strlen(iv));
    memcpy(iv_bk, iv, strlen(iv));

    printf("-iv_bk:\n\t");
    puhex(iv_bk);
    
    printf("padding...");
    pad(plaintext);
    printf("base64 to encrypte: \n\t%s\n\thex:\n\t", pPlaintText.padded_text);
    puhex(pPlaintText.padded_text);
 
    printf("\n--standalone encryp started--\n");
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv_bk);
    
    AES_CBC_encrypt_buffer(&ctx, (uint8_t*)pPlaintText.padded_text, pPlaintText.size);
    
    printf("after encryption; encrypted lenth %d\n\t", pPlaintText.size);
    puhex(pPlaintText.padded_text);
    
    memcpy(encrypt_output, iv, BLOCK_LEN);
    memcpy(encrypt_output + BLOCK_LEN, pPlaintText.padded_text, strlen(pPlaintText.padded_text));
    printf("encrypt_output:\n\t");
    puhex(encrypt_output);
//  
//    int concated_cipher_text_len = BLOCK_LEN + pPlaintText.size;
//    printf("encrypting: concated_cipher_text_len: %d", concated_cipher_text_len);
//    uint8_t* concated_cipher_text = (uint8_t*)malloc(sizeof(char) * concated_cipher_text_len);
//    memcpy(concated_cipher_text, iv, strlen(iv));
//    printf("concated cihper copy iv_bk:\n\t");
//    puhex(concated_cipher_text);
//    
//    memcpy(concated_cipher_text + strlen(iv), pPlaintText.padded_text, strlen(pPlaintText.padded_text));
//    printf("concated cihper copy ciphertext:\n\t");
//    puhex(concated_cipher_text);
//    
//    return concated_cipher_text;
}

/**
 * @brief 
 * @param concated_ciphertext: iv + ciphertext
 * @return 
 */
char* decrypt(uint8_t key[], uint8_t concated_ciphertext[]){
    if (strlen(concated_ciphertext) < 2 * BLOCK_LEN){
        fprintf(stderr, "!error: wrong concated_ciphertext size.");
        exit(-1);
    }
    
    printf("--standalon decrypt on len %d: --\n\t", BLOCK_LEN + pPlaintText.size);
    puhex(concated_ciphertext);
    
    int iv_len = BLOCK_LEN;
    int cipher_len = pPlaintText.size;
    printf("iv len: %d, cipher_ln: %d\n", iv_len, cipher_len);
//    
//    uint8_t* iv = malloc(sizeof(uint8_t) * iv_len);
//    memcpy(iv, concated_ciphertext, iv_len);
//    printf("decat decryption input: iv\n\t");
//    puhex(iv);
    
    
    uint8_t* ciphertext = malloc(sizeof(uint8_t) * cipher_len);
    memcpy(ciphertext, concated_ciphertext + iv_len, cipher_len);    
    printf("decat decryption input: ciphertext\n\t");
    puhex(ciphertext);
    
    uint8_t iv[]  = { 0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_decrypt_buffer(&ctx, ciphertext, cipher_len);
//    AES_CBC_decrypt_buffer(&ctx, ciphertext, 256);
    printf("decrypted value: \n\t");
    puhex(ciphertext);

    char* plaintext = depad(ciphertext);
    return plaintext;
}

int main(int argc, char** argv){
//#if defined(AES256)
//    BLOCK_LEN = 32;
//#elif defined(AES192)
//    BLOCK_LEN = 24;
//#elif defined(AES128)
//    BLOCK_LEN = 16;
//#endif

	uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };

    encrypt(key, argv[1]);
    printf("returned concated cipher text is:\n\t");
    puhex(encrypt_output);

    
    char* plaintext = decrypt(key, encrypt_output);
    printf("decrypted plaintext:\n%s", plaintext);
}
