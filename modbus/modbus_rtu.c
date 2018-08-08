#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "include/modbus.h"

#define SERVER_ID 1

int main( int argc,char *argv[] )
{
	modbus_t *ctx;
	uint16_t tab_reg[64];
	int ret;
	int count;
	int addr;

	ctx = modbus_new_rtu("/dev/ttyUSB0", 115200, 'N', 8, 1);
	if (ctx == NULL) 
	{
	    printf("Unable to allocate libmodbus context\n");
	    return -1;
	}

	/* set slave device ID */
	modbus_set_slave(ctx, SERVER_ID);

	/* Debug mode */
    modbus_set_debug(ctx, TRUE);

	/* open serial interface */
	if (modbus_connect(ctx) == -1) 
	{
	    printf("Connection failed: %s\n", modbus_strerror(errno));
	    modbus_free(ctx);
	    return -1;
	}

	/* read modbus address 0, 2 register values. */
	addr = 0;
	count = 2;

	ret = modbus_read_registers(ctx, addr, count, tab_reg);
	if(ret != -1)
	{
		for (count=0; count < ret; count++) 
		{
		    printf("reg[%d]=%d (0x%X)\n", count, tab_reg[count], tab_reg[count]);
		}
	}

	modbus_close(ctx);
	modbus_free(ctx);

    return 0;
}