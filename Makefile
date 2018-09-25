#CC           = avr-gcc
#CFLAGS       = -Wall -mmcu=atmega16 -Os -Wl,-Map,test.map
#OBJCOPY      = avr-objcopy
CC           = gcc
LD           = gcc
CFLAGS       = -Wall -Os -c
LDFLAGS      = -Wall -Os -Wl,-Map,test.map
ifdef AES192
CFLAGS += -DAES192=1
endif
ifdef AES256
CFLAGS += -DAES256=1
endif

OBJCOPYFLAFS = -j .text -O ihex
OBJCOPY      = objcopy

# include path to AVR library
INCLUDE_PATH = /usr/lib/avr/include
# splint static check
SPLINT       = splint test.c aes.c -I$(INCLUDE_PATH) +charindex -unrecog



client.o : aes_client.c aes.h aes.o
	echo [CC] $@ $(CFLAGS)
	$(CC) $(CFLAGS) -o  $@ $<

aes.o : aes.c aes.h
	echo [CC] $@ $(CFLAGS)
	$(CC) $(CFLAGS) -o $@ $<

client : aes.o test.o
	$(CC) aes.o test.o -o client


clean :
	@rm -f *.o
	@echo "== cleaned =="
