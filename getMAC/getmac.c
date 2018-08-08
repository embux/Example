#include <stdio.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <fcntl.h>
#include <string.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <linux/sockios.h>

typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned long u64;

int main(void)
{
	struct ifreq ifr;
	int fd;
	
	strcpy(ifr.ifr_name, "eth0");

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if(ioctl(fd, SIOCGIFHWADDR, &ifr) >= 0)
	{
		printf("eth0 MAC %02x:%02x:%02x:%02x:%02x:%02x\n",\
		ifr.ifr_hwaddr.sa_data[0],ifr.ifr_hwaddr.sa_data[1],ifr.ifr_hwaddr.sa_data[2],ifr.ifr_hwaddr.sa_data[3],ifr.ifr_hwaddr.sa_data[4],ifr.ifr_hwaddr.sa_data[5]);
	}

	close(fd);

	return 1;
}

