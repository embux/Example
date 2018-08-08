PATH := $(PATH):/opt/toolchian/gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux/bin/ 
SHELL := env PATH=$(PATH) /bin/bash

CC = arm-linux-gnueabihf-gcc
STRIP = arm-linux-gnueabihf-strip
EXEC1 = modbus_tcp 
EXEC2 = modbus_rtu
SRC1 = modbus_tcp.c 
SRC2 = modbus_rtu.c

all:	$(EXEC1) $(EXEC2)

$(EXEC1): $(SRC1)
	$(CC)  -o $(EXEC1) $(SRC1) lib/libmodbus.so
	$(STRIP) $(EXEC1)

$(EXEC2): $(SRC2)
	$(CC)  -o $(EXEC2) $(SRC2) lib/libmodbus.so
	$(STRIP) $(EXEC2)

clean:
	rm -f $(EXEC1) $(EXEC2)	
