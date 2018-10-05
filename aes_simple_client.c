#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "aes.h"
#include "ucsp.h"

//#define len 64
#define TEXT_SIZE 512

void pnhex(uint8_t u[], int len){
    for (int i=0; i < len; i++){
        printf("%02x", u[i]);
    }
    printf("\n"); 
}

void puhex(uint8_t u[]){
    pnhex(u, strlen(u));
}



void phex(uint8_t u[]){
	pnhex(u, AES_BLOCKLEN);
}

short cal_padding_num(char text[]){
	int plainLen = strlen(text);
	short remainder = plainLen % AES_BLOCKLEN;
	short padding_num = AES_BLOCKLEN - remainder;
	
	return padding_num;
}
/**
 * @brief String length must be evenly divisible by 16byte (str_len % 16 == 0)
        You should pad the end of the string with zeros if this is not the case.
        For AES192/256 the key size is proportionally larger.
 * @param padded_text: pointer allocated with a correct number of char
 * @param base64_text: base64_text without ending '\0'
 */
void pad(char* padded_text, char base64_text[]){
	short padding_num = cal_padding_num(base64_text);
	short plainLen = strlen(base64_text);
    if(!padding_num){
        printf("input %s: length %d, no need padding.\n", base64_text, plainLen);
        padded_text = base64_text;
		return;
    }
	
//	printf("input of pad: %s\n\t length:%d, need %d pad.\n", base64_text, plainLen, padding_num);

	memcpy(padded_text, base64_text, plainLen);
	char padding = padding_num + '0';
	int i = 0;
	for (; i < padding_num; i++){
		padded_text[plainLen + i] = padding;
	}  
}

char* depad(char padded_text[]){
    int padding_num = (int) padded_text[strlen(padded_text) - 1] - '0';
	int depadded_len = strlen(padded_text) - padding_num;
	char* dapadded_text = malloc(sizeof(char) * (strlen(padded_text) - padding_num));
	strncpy(dapadded_text, padded_text, depadded_len);
	
//	printf("depadded plaintext: %s\n", dapadded_text);
	return dapadded_text;
}

/**
 * @brief base64 encode an entity needed by encryption.
 * @param argc
 * @param argv
 * @return specified length of uint*_t array in base64; if @ret_len = 0, return uint8_t array w/l '\0' at the end.
 */
char* base64_encode_entity(char entity[], int ret_len){
	int entity_len = strlen(entity);
	if (!entity_len){
		fprintf(stderr, "len of entiry for base64is zero.\n");
		exit(-1);
	}
	
	int base64_len = Base64encode_len(entity_len);
	if (ret_len > base64_len){
		fprintf(stderr, "ret length larger than entity base64 length.\n");
		exit(-1);
	}
	
	if (ret_len == 0){
		ret_len = Base64encode_len(entity_len) - 1;
	}
		 
    char* encoded_text = malloc(sizeof(char) * base64_len);
    int textLen = Base64encode(encoded_text, entity, entity_len);
//    printf("base64 encoded entity: \n\t%s, \n\treturn len: %d\n\tentity base64 array len: %lu\n", encoded_text, textLen, strlen(encoded_text));;
    
	return encoded_text;
}

uint8_t* base64_encode_aes_key(char key[]){
	return base64_encode_entity(key, (int)AES_BLOCKLEN);
}

uint8_t* base64_encode_cbc_iv(char iv[]){
	return base64_encode_entity(iv, (int)AES_BLOCKLEN);
}

char* base64_decode(char txt[]){
    char* decoded_text = malloc(sizeof(char) * Base64decode_len(txt));
    int pRet = Base64decode(decoded_text, txt);

    return decoded_text;
}

/**
 * @brief 
 * @param key
 * @param iv
 * @param plaintext
 * @return ciphertext_len + cipher_text  + IV
 */
uint8_t* ucsp_encrypt(uint8_t key[], char* plaintext){
	//make a base64 encoded text without ending '\0'
	uint8_t* base64_text = base64_encode_entity(plaintext, 0);
	printf("\nbase64 encoded plaintext: \n\t%s\n", base64_text);
	
	//padding
	short padding_num = cal_padding_num(base64_text);
	short padded_len = strlen(base64_text) + padding_num;
	char* padded_text = malloc(sizeof(char) * padded_len);
	pad(padded_text, base64_text);
	printf("\npadded base64: \n\t%s\n\t", padded_text);
	puhex(padded_text);
	
	//encryption
	uint8_t iv[]  = "112456789012345";
	struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_encrypt_buffer(&ctx, padded_text, padded_len);
    printf("--after encryption--\n encrypted value len: %d\nencrypted value\n\t", padded_len);
    puhex(padded_text);

	//concat length and encrypted_text
	uint8_t* encrypted_value = (uint8_t*)malloc(sizeof(char) * (2 + padded_len + AES_BLOCKLEN));
	
	memcpy(encrypted_value, &padded_len, 2);
	memcpy(encrypted_value + 2, padded_text, padded_len);
	memcpy(encrypted_value + 2 + padded_len, iv, AES_BLOCKLEN);
	
    printf("--after concation--\n encrypted value\n\t");
    puhex(encrypted_value);
	return encrypted_value;
}

/**
 * @brief 
 * @param encryption_return: ciphertext_len + cipher_text  + IV
 * @return 
 */
char* ucsp_decrypt(uint8_t key[], uint8_t* encryption_return){
	int encrypted_value_len	= encryption_return[0] | encryption_return[1] << 8;
	char* encrypted_value		= malloc(sizeof(char) * encrypted_value_len);
	memcpy(encrypted_value, encryption_return + 2, encrypted_value_len);
	printf("encrypted_value in main: length: %d \n\t", encrypted_value_len);
	puhex(encrypted_value);
	
	char* iv = malloc(sizeof(char) * AES_BLOCKLEN);
	memcpy(iv, encryption_return + 2 + encrypted_value_len, AES_BLOCKLEN);
	
	struct AES_ctx de_ctx;
    AES_init_ctx_iv(&de_ctx, key, iv);
	
    AES_CBC_decrypt_buffer(&de_ctx, encrypted_value, encrypted_value_len);
    printf("--after decryption--\n\t");
    pnhex(encrypted_value, encrypted_value_len);
	printf("iv\n\t");
	phex(iv);
	
	return base64_decode(encrypted_value);
}

int main(int argc, char** argv){
	printf("program input: \n\t%s\n", argv[1]);
	uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };

	
	char* value_to_encryption = argv[1];
	char* encryption_return	= ucsp_encrypt(key, value_to_encryption);
	printf("--encryption output in main()--\n\t");
	puhex(encryption_return);
	
	char* decryption_return	= ucsp_decrypt(key, encryption_return);
	printf("decrypted value: \n\t%s\n", decryption_return);

	exit(-1);
}