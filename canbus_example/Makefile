PATH := $(PATH):/opt/toolchian/gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux/bin/ 
SHELL := env PATH=$(PATH) /bin/bash

CC = arm-linux-gnueabihf-gcc
STRIP = arm-linux-gnueabihf-strip
EXEC1 = can_send 
EXEC2 = can_recv
SRC1 = can_send.c 
SRC2 = can_recv.c

all:	$(EXEC1) $(EXEC2)

$(EXEC1): $(SRC1)
	$(CC)  -o $(EXEC1) $(SRC1)
	$(STRIP) $(EXEC1)

$(EXEC2): $(SRC2)
	$(CC)  -o $(EXEC2) $(SRC2)
	$(STRIP) $(EXEC2)

clean:
	rm -f $(EXEC1) $(EXEC2)	
