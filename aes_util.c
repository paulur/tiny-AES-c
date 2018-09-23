#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "aes.h"

#define BLOCK_SIZE 16

char padding[BLOCK_SIZE];


/**
 * @brief 
 * 	String length must be evenly divisible by 16byte (str_len % 16 == 0)
        You should pad the end of the string with zeros if this is not the case.
        For AES192/256 the key size is proportionally larger.
 * @param plaintext
 * @return 
 */
char* pad(char plaintext[]){
	int textLen = strlen(plaintext);
	if (!textLen){
		printf("textlen is zero");
		exit(0);
	}
		
	int remainder = textLen % BLOCK_SIZE;
	int numPad = BLOCK_SIZE - remainder;
	printf("remainder of %s is %d, need %d pad.\n", plaintext, remainder, numPad);

	char* paddedPlaintext = malloc(sizeof(char) * (textLen + numPad));
	memcpy(paddedPlaintext,  plaintext, textLen);
	int i = 0;
	
	memcpy(paddedPlaintext + textLen + i++, " ", 1);
	for (; i < numPad; i++){
		memcpy(paddedPlaintext + textLen + i, "0", 1);
	}  
	

	printf("padded plaintext: %s\n", paddedPlaintext);
	return paddedPlaintext;
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
	char* pText = argv[2];	

	char* padPlainttext = pad(pText);

	printf("depad.. after padPlainttext: %s\n", padPlainttext);
	depad(padPlainttext);
	
	free(padPlainttext);
//	free(paddedText);
}
