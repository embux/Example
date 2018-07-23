CC = arm-linux-gnueabihf-gcc
STRIP = arm-linux-gnueabihf-strip
EXEC = hello
SRC = hello.c

all:	$(EXEC)

$(EXEC): $(OBJS)
	$(CC)  -o $(EXEC) $(SRC)
	$(STRIP) $(EXEC)

clean:
	rm -f $(EXEC)
