#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "aes.h"

#define BLOCK_SIZE 16

char padding[BLOCK_SIZE];

char* makePadding(int numPad){
	for (int i = 0; i < numPad -1; i++){
		padding[i] = 'a'; 
	}
	
	padding[numPad-1] = numPad;

	printf("make padding: %s", padding);
	return padding;
}

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
	for (int i = 0; i < numPad - 1; i++){
		memcpy(paddedPlaintext + textLen + i, "0", 1);
	}  
		
	memcpy(paddedPlaintext + textLen + numPad - 1, "?", 1);

	printf("padded plaintext: %s", paddedPlaintext);
}

int main(int argc, char** argv)
{
	char* pText = argv[2];	

	pad(pText);
	
}
