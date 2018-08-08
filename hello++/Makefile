PATH := $(PATH):/opt/toolchian/gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux/bin/ 
SHELL := env PATH=$(PATH) /bin/bash

CPP = arm-linux-gnueabihf-g++
STRIP = arm-linux-gnueabihf-strip
EXEC = hello
SRC = hello.cpp
CFLAGS = -Wno-deprecated

all:	$(EXEC)

$(EXEC): $(SRC)
	$(CPP)  $(SRC) -o $(EXEC)
	$(STRIP) $(EXEC)

clean:
	rm -f $(EXEC)
