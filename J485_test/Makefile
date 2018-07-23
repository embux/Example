CC = arm-linux-gnueabihf-gcc
STRIP = arm-linux-gnueabihf-strip
EXEC = J485_test
SRC = J485_test.c

all:	$(EXEC)

$(EXEC): $(OBJS)
	$(CC)  -o $(EXEC) $(SRC)
	$(STRIP) $(EXEC)

clean:
	rm -f $(EXEC)
