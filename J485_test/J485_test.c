#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stropts.h>
#include <termios.h>

#include <sys/ioctl.h>
#include <asm/ioctls.h>
#include <linux/ioctl.h>

#include <stdio.h>
#include <stdlib.h>

#define DEVICE_NODE   "/dev/ttymxc1"

/*
 * Get baudrate value
 */
long baudrate(long speed) {
    if(speed ==  0)
        return  B0;
    if(speed ==  50)
        return B50;
    if(speed ==  75)            
        return B75;
    if(speed ==  110)           
            return B110;
    if(speed ==  134)           
            return B134;
    if(speed ==  150)           
            return B150;
    if(speed ==  200)           
            return B200;
    if(speed ==  300)           
            return B300;
    if(speed ==  600)           
            return B600;
    if(speed ==  1200)          
            return B1200;
    if(speed ==  1800)          
            return B1800;
    if(speed ==  2400)          
            return B2400;
    if(speed ==  4800)          
            return B4800;
    if(speed ==  9600)          
            return B9600;
    if(speed ==  19200)         
            return B19200;
    if(speed ==  38400)         
            return B38400;
    if(speed ==  57600)         
            return B57600;
    if(speed ==  115200)            
            return B115200;
    if(speed ==  230400)            
            return B230400;
    if(speed ==  460800)            
            return B460800;
    if(speed ==  921600)            
            return B921600;
            
    return speed;
    
}

/*
embux_uart_Config : example to config uart port

fd : file descriptor
baud : baudrate
serial_mode : n81 , o81 , e81 , n71 , o71 .........
serial_type : set to RS232 , RS485 , RS422
*/
int embux_uart_Config (int fd, int baud , char * serial_mode , int serial_type){
    struct termios term;
    long BAUD , DATABITS , STOPBITS , PARITYON , PARITY;
    int flag = 0 , i , j = 0 , interface;
    
    BAUD = baudrate(baud);
    
    if(tcgetattr(fd,&term) != 0) {
        close(fd);
        perror("embux_uart_Config");
        return -1;
    }
    
    switch (serial_mode[1])
    {
        case '8':
            DATABITS = CS8;
        break;
        case '7':
            DATABITS = CS7;
        break;
        case '6':
            DATABITS = CS6;
        break;
        case '5':
            DATABITS = CS5;
        break;
        default :
            flag = 1;
        break;
    }  //end of switch data_bits
    
    switch (serial_mode[2])
    {
        case '1':
            STOPBITS = 0;
        break;
        case '2':
            STOPBITS = CSTOPB;
        break;
        default :
            flag = 1;
        break;
    }  //end of switch stop bits
    
    switch (serial_mode[0])
    {
        case 'N':
        case 'n':
            PARITYON = 0;
            PARITY = 0;
        break;
        case 'O': 
        case 'o': //odd
            PARITYON = PARENB;
            PARITY = PARODD;
        break;
        case 'E': //even
        case 'e':
            PARITYON = PARENB;
            PARITY = 0;
        break;
        default :
            flag = 1;
        break;
    }  //end of switch parity
    
    if(serial_type != 232) {
        term.c_iflag &= ~(IXON|IXOFF|IXANY);
        term.c_cflag &= ~CRTSCTS;
    }
    
    if(flag == 1) {
        printf("embux_uart_Config : Error config %s.\n",serial_mode);
        close(fd);
        return -1;
    }
    
    term.c_cflag = BAUD | DATABITS | STOPBITS | PARITYON | PARITY | CLOCAL | CREAD | HUPCL;
    term.c_iflag = IGNPAR;
    term.c_oflag = 0;
    term.c_lflag = 0;       //ICANON;
    term.c_cc[VMIN]= 0;
    term.c_cc[VTIME]= 0;
    
    tcflush(fd, TCIFLUSH); // clean recv
       
    if(tcsetattr(fd,TCSANOW,&term) != 0) {
        perror("embux_uart_Config");
        close(fd);
        return -1;
    } 
    
    tcflush(fd, TCIFLUSH); // clean recv
    return fd;
}

/**************************************************
AHT-503  Temperature & Humidity Transmitter
RS485 define
Baud rate:9600
Word length=8
Parity=none
Stop bits=1

Read format
+----------------+----+---------+---------+-----------+-----------+-------+
| Hardware addr  | op | addr(H) | addr(L) | length(H) | length(L) | CRC16 |
+----------------+----+---------+---------+-----------+-----------+-------+
|   by setting   |0x03|  0x00   |  0x00   |  0x00     |   0x02    |  XXXX |
+----------------+----+---------+---------+-----------+-----------+-------+


Responding format
+----------------+----+------------+---------+---------+---------+---------+-------+
| Hardware addr  | op | data count | data(H) | data(L) | data(H) | data(L) | CRC16 |
+----------------+----+------------+---------+---------+---------+---------+-------+
|   by setting   |0x03|   0x04     |  0x09   |  0x34   |  0x13   |  0x0B   | XXXX  |
+----------------+----+------------+---------+---------+---------+---------+-------+

EX:
0x0934(Hex) = 2356,  2356/100 = 23.56 C
0x130B(HEX) = 4875,  4875/100 = 48.75 %RH

***************************************************/

struct modbus_data
{
    unsigned char hw_addr;
    unsigned char op_code;
    unsigned char num_of_data;
    unsigned char val1[2];
    unsigned char val2[2];
    unsigned char checksum[2];
};

int main(void)
{
    int fd;
    unsigned char test_cmd[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xc4, 0x0b};
    unsigned char buffer[32];
    int read_size;
    int i;

    fd = open(DEVICE_NODE, O_RDWR);

    if(fd)
    {
        if(embux_uart_Config(fd, 9600, "n81", 485) == -1)
            return -1;

        write(fd, test_cmd, sizeof(test_cmd));

        /* Waiting for send data completed. */
        sleep(1);

        read_size = read(fd, buffer, sizeof(buffer));

        printf("Read %d bytes\n", read_size);

        close(fd);

        for(i = 0; i< read_size; i++)
        {
            printf("%02X ", buffer[i]);
        }
        printf("\n");

        if(read_size == 9)
        {
            struct modbus_data *rsp = (struct modbus_data *)buffer;
            unsigned short int val1, val2;

            val1 = rsp->val1[0];
            val1 = (val1 << 8) + rsp->val1[1];
            
            val2 = rsp->val2[0];
            val2 = (val2 << 8) + rsp->val2[1];

            printf("val1: %.2f (%04X), val2: %.2f (%04X)\n", (float)val1/100, val1, (float)val2/100, val2);

            return 0;
        }
    }

    return -1;
}