#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <err.h>
#include <errno.h>

#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static inline __s32 i2c_smbus_access(int fd, char read_write, __u8 command,
                                     int size, union i2c_smbus_data *data)
{
	struct i2c_smbus_ioctl_data args;

	args.read_write = read_write;
	args.command = command;
	args.size = size;
	args.data = data;
	
	return ioctl(fd,I2C_SMBUS,&args);
}


static inline __s32 i2c_smbus_read_byte_data(int fd, __u8 command)
{
	union i2c_smbus_data data;
	if (i2c_smbus_access(fd,I2C_SMBUS_READ,command,
	                     I2C_SMBUS_BYTE_DATA,&data))
		return -1;
	else
		return 0x0FF & data.byte;
}

int main(int argc, char **argv)
{
	uint8_t data, addr = 0x76, reg = 0x0d;
	const char *path = argv[1];
	int fd, rc;

	if (argc == 1)
		errx(-1, "path [i2c address] [register]");

	if (argc > 2)
		addr = strtoul(argv[2], NULL, 0);
	if (argc > 3)
		reg = strtoul(argv[3], NULL, 0);

	fd = open(path, O_RDWR);
	if (fd < 0)
	{
		err(errno, "Tried to open '%s'", path); 
		return 1;
	}

	rc = ioctl(fd, I2C_SLAVE, addr);
	if (rc < 0)
		err(errno, "Tried to set device address '0x%02x'", addr);

	data = i2c_smbus_read_byte_data(fd, reg);

	printf("%s: device 0x%02x at address 0x%02x: 0x%02x\n",
			path, addr, reg, data);

	close(fd);

	return 0;
}