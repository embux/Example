CC = arm-linux-gnueabihf-g++
STRIP = arm-linux-gnueabihf-strip
EXEC = hello
SRC = hello.cpp
CFLAGS = -Wno-deprecated

all:	$(EXEC)

$(EXEC): $(OBJS)
	$(CC)  $(SRC) -o $(EXEC)
	$(STRIP) $(EXEC)

clean:
	rm -f $(EXEC)
