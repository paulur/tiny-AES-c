#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "aes.h"
#include "ucsp.h"

//#define len 64
#define TEXT_SIZE 358

uint8_t plaintext[TEXT_SIZE];

void puhex(uint8_t u[]){
    for (int i=0; i < TEXT_SIZE; i++){
        printf("%02x", u[i]);
    }
    printf("\n");
    for (int i=0; i < TEXT_SIZE; i++){
        printf("%d", (char)u[i]);
    }
   
}

/**
 * @brief base64 encode an entity needed by encryption.
 * @param argc
 * @param argv
 * @return specified length of uint*_t array in base64; if @ret_len = -1, return uint8_t array w/l '\0' at the end.
 */
uint8_t* base64_encode_entity(char entity[], int ret_len){
	int entity_len = strlen(entity);
	if (!entity_len){
		fprintf(stderr, "len of entiry for base64is zero");
		exit(-1);
	}
	
	int base64_len = Base64encode_len(entity_len);
	if (ret_len > base64_len){
		fprintf(stderr, "ret length larger than entity base64 lenght");
		exit(-1);
	}
	
	if (ret_len == -1){
		ret_len = Base64encode_len(entity_len) - 1;
	}
		 
    char* encoded_text = malloc(sizeof(char) * base64_len);
    int textLen = Base64encode(encoded_text, entity, entity_len);
    printf("base64 encoded entity: \n\t%s, \n\treturn len: %d\n\tentity base64 array len: %lu\n", encoded_text, textLen, strlen(encoded_text));;
    
	//remove the '\0' from the end
	uint8_t* base64_uint8_array = (uint8_t*) malloc(ret_len);
	memcpy(base64_uint8_array, (uint8_t*)encoded_text, ret_len);
	printf("returned base64_uint8_array: \n\t%s, \n\tbase64_uint8_array base64 len: %lu\n", base64_uint8_array, strlen((char*)base64_uint8_array));
	
	return base64_encode_entity;
}

uint8_t* base64_encode_aes_key(char key[]){
	return base64_encode_entity(key, AES_BLOCKLEN);
}

uint8_t* base64_encode_cbc_iv(char iv[]){
	return base64_encode_entity(iv, AES_BLOCKLEN);
}

char* base64_decode(char txt[]){
    char* decoded_text = malloc(sizeof(char) * Base64decode_len(txt));
    int pRet = Base64decode(decoded_text, txt);

printf("to decode %s\n", txt);
printf("pRet %d\nconverted_text: %s\n", pRet, decoded_text);

    printf("%s", decoded_text);
    return decoded_text;
}

int main(int argc, char** argv){
	printf("input: len %lu: \n\t%s\n", strlen(argv[1]), argv[1]);
    int base64_len = atoi(argv[2]);
	uint8_t* plain = base64_encode_entity(argv[1], base64_len);

	memcpy(plaintext, plain, base64_len);
    
    char* decoded_plain = base64_decode((char*)plaintext);
    printf("base64 decoded: %s\n", decoded_plain);
//	printf("encoded as aes key:\n");
//	base64_encode_aes_key(argv[1]);
//	
//	printf("encoded as cbc iv:\n");
//	base64_encode_aes_key(argv[1]);

    uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
    uint8_t iv[]  = { 0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    
    printf("-before encyrption--\n");
    puhex(plaintext);
    
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    printf("--encryption started--\n");
   
    AES_CBC_encrypt_buffer(&ctx, plaintext, base64_len);
    printf("--after encryption--\n");
    puhex(plaintext);
    
    struct AES_ctx de_ctx;
	uint8_t de_key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
    uint8_t de_iv[]  = { 0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    AES_init_ctx_iv(&de_ctx, de_key, de_iv);
    AES_CBC_decrypt_buffer(&de_ctx, plaintext, base64_len);
    printf("--after decryption--\n");
    puhex(plaintext);
    
    struct AES_ctx re_ctx;
    uint8_t re_key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
    uint8_t re_iv[]  = { 0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    AES_init_ctx_iv(&re_ctx, re_key, re_iv);
    AES_CBC_encrypt_buffer(&re_ctx, plaintext, base64_len);
    printf("--after recryption--\n");
    puhex(plaintext);
}
