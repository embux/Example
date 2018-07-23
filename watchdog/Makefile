CC=arm-linux-gnueabihf-gcc
STRIP=arm-linux-gnueabihf-strip
TARGET=watchdog.o


all:watchdog

watchdog:$(TARGET)
	$(CC) -o $@ $(TARGET)
	$(STRIP) $@
	
clean:
	rm -rf *~ $(TARGET) a.out watchdog