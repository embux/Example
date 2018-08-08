PATH := $(PATH):/opt/toolchian/gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux/bin/ 
SHELL := env PATH=$(PATH) /bin/bash

CC = arm-linux-gnueabihf-gcc
STRIP = arm-linux-gnueabihf-strip
EXEC = watchdog
SRC = watchdog.c

all:	$(EXEC)

$(EXEC): $(SRC)
	$(CC)  -o $(EXEC) $(SRC)
	$(STRIP) $(EXEC)

clean:
	rm -f $(EXEC)