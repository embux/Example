CC=arm-linux-gnueabihf-gcc
STRIP=arm-linux-gnueabihf-strip

all:	getmac
getmac:	getmac.c
	$(CC) -o getmac getmac.c
	$(STRIP) getmac

clean:
	rm -f getmac *.o
