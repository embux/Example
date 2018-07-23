CC = arm-linux-gnueabihf-gcc
STRIP = arm-linux-gnueabihf-strip
EXEC = i2c_example
SRC = i2c_example.c

all:	$(EXEC)

$(EXEC): $(OBJS)
	$(CC)  -o $(EXEC) $(SRC)
	$(STRIP) $(EXEC)

clean:
	rm -f $(EXEC)
