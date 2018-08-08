#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <asm/types.h>
#include <linux/watchdog.h>

int main () 
{
	int fd ;
	int timeout;
	int value;
	fd = open("/dev/watchdog",O_RDWR);/*when open watchdog , enable watchdog*/
	if(fd < 0) 
	{
		perror("watchdog");
		exit(1);
	}

	ioctl(fd , WDIOC_GETTIMEOUT,&timeout);
	printf("Get Default Watchdog Time : %d\n", timeout);
			
	timeout = 5;
	if(ioctl(fd , WDIOC_SETTIMEOUT ,&timeout) != 0) 
	{
		perror("SET");
		close (fd);
		exit(1);
	}
	
	printf("IF use Ctrl + c , after %d Sec , System will Reboot!\n", timeout);
	while(1) 
	{
		ioctl(fd , WDIOC_KEEPALIVE); /* Pat the watchdog */
		sleep(1);
	}

	close (fd);

}