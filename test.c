#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "aes.h"

#define BLOCK_SIZE 16

struct padded_text
{
	char* text;
	uint32_t size;
};

// prints string as hex
static void phex(uint8_t* str)
{

#if defined(AES256)
    uint8_t len = 32;
#elif defined(AES192)
    uint8_t len = 24;
#elif defined(AES128)
    uint8_t len = 16;
#endif
	printf("uint8_t len: %d\n", (char)len);
	
    unsigned char i;
    for (i = 0; i < len; ++i)
        printf("%.2x", str[i]);
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
struct padded_text* pad(char plaintext[]){
	int textLen = strlen(plaintext);
	if (!textLen){
		printf("textlen is zero");
		exit(0);
	}
		
	int remainder = textLen % BLOCK_SIZE;
	int numPad = BLOCK_SIZE - remainder;
	printf("remainder of %s is %d, need %d pad.\n", plaintext, remainder, numPad);

	short mem_size = textLen + numPad;
	char* paddedPlaintext = malloc(sizeof(char) * mem_size);
	memcpy(paddedPlaintext, plaintext, textLen);
	int i = 0;
	
	memcpy(paddedPlaintext + textLen + i++, " ", 1);
	for (; i < numPad; i++){
		memcpy(paddedPlaintext + textLen + i, "0", 1);
	}  
	
	printf("padded plaintext: %s\n", paddedPlaintext);
	
	struct padded_text* pTextStruct;
	pTextStruct->text = paddedPlaintext;
	pTextStruct->size = mem_size;
	
	return pTextStruct;
}

char* depad(char paddedPlainText[]){
    int index = -1;
	
    for (int i = 0; i < strlen(paddedPlainText); i++)
        if (paddedPlainText[i] == ' ')
            index = i;
	printf("the index of last space of %s is %d\n", paddedPlainText, index);
	
	char* depaddedPlaintext = malloc(sizeof(char) * index);
	strncpy(depaddedPlaintext, paddedPlainText, index);
	
	
	printf("depadded plaintext: %s\n", depaddedPlaintext);
	return depaddedPlaintext;
}

int main(int argc, char** argv)
{
	uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
	uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
	char* pText = argv[2];	

	struct padded_text* padPlainttext = pad(pText);
	printf("padtext size: %d: , value: %s: ", padPlainttext->size, padPlainttext->text);
	
	struct AES_ctx ctx;
//
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_encrypt_buffer(&ctx, padPlainttext, padPlainttext->size);
//
//
//	printf("depad.. after padPlainttext: %s\n", padPlainttext);
	depad(padPlainttext->text);
//	
//	free(padPlainttext);

}
