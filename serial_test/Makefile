CC = arm-linux-gnueabihf-gcc
STRIP = arm-linux-gnueabihf-strip
EXEC = serial
OBJ = serial.o

all:	$(EXEC)
	$(CC) $(OBJ) -o $(EXEC)
	$(STRIP) $(EXEC)

$(EXEC): $(OBJ)
%o: %c
	$(CC) -c $< -o $@

clean:
	rm -f $(EXEC) $(OBJ)
