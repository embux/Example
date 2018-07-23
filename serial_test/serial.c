/*
 *  Description: 
 *      serial port example
 *      Device set 19200bps, n81, RTS/CTS flow control. and echo back the received data.
 *
 *      What is shown in this example:
 *      1. How to open a serial port
 *      2. How to set interface
 *      3. How to set baudrate, flow control and other settings
 *      4. How to read and write a serial port
 *      
 */
#include <stdio.h>
#include <unistd.h>
#include <asm/termios.h>
#include <errno.h>
#include <fcntl.h>
#include <asm/ioctls.h>
#include <linux/serial.h>
#include <string.h>
#include <stropts.h>


#include <sys/stat.h>
#include <linux/ioctl.h>


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
    
    switch(serial_type) {
        case 422:
            interface = 422;
            break;
        case 485:
            interface = 485;
            break;
        default:
            interface = 232;
        break;
    }
    
    tcflush(fd, TCIFLUSH); // clean recv
    
    
    if(tcsetattr(fd,TCSANOW,&term) != 0) {
        perror("embux_uart_Config");
        close(fd);
        return -1;
    } 
    
    tcflush(fd, TCIFLUSH); // clean recv
    return fd;
}

int
main(argc, argv)
    int argc;
    char    *argv[];
{

    int fd, interface, ret , i;
    char    buf[1024];
    struct termios T_new;
    int mcr = 0;
    char dev[64]={0};

    if (argc != 2)
    {
        printf("\ncommand : serial [device]\n");
        return 0;
    }

    strcpy(dev, argv[1]);

             
    /*open tty port*/
    fd = open(dev, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        printf("open %s Failed, errno: %d\r\n", dev, errno);
        return 0;
    }
    printf("open %s OK!\n", dev);

    if(embux_uart_Config(fd, 9600, "n81", 232) == -1)
        return -1;
#if 0   
    /*set serial interface: RS-232*/
    interface = 232;
    if(ioctl(fd, UC500_SET_UART_TYPE, &interface) != 0) {
        printf("set UART type: %d...Failed, errno: %d\r\n", interface, errno);
        close(fd);
        return 0;
    }
#endif
    /* In normal case, you must enable hardware flow if you'll monitor CTS signal */
    /* But in hardware flow mode, RTS is controlled automatically by UART controller*/
    //tcgetattr(fd, &T_new);
    //T_new.c_cflag &= ~CRTSCTS;
    //tcsetattr(fd, TCSANOW, &T_new);
    /* Artila provides a specific command to enable CTS interrupt in normal mode */
    //ioctl(fd, 0xf001, &mcr);
    
    
    //memset(buf,'1',1024);

    i = 0;
    //mcr |= TIOCM_RTS;
    //ioctl(fd, TIOCMSET, &mcr);
    while(1) {
        
        sleep(1);
        //write(fd,buf,1024);
        //mcr = 0;
        #if 1
        ioctl(fd, TIOCMGET, &mcr);
        if(mcr & TIOCM_CTS){
            printf("CTS is ON\n");
                mcr |= TIOCM_RTS;
        }else{
            printf("CTS is OFF\n");
                mcr &= ~TIOCM_RTS;
        }
        if(mcr & TIOCM_DSR){
            printf("DSR is ON\n");
                mcr |= TIOCM_DTR;
        }else{
            printf("DSR is OFF\n");
                mcr &= ~TIOCM_DTR;
        }
        if(mcr & TIOCM_CD){
            printf("DCD is ON\n");
        }else {
            printf("DCD is OFF\n");
        }
        
            ioctl(fd, TIOCMSET, &mcr);
        #else
#if 1
        if(mcr & TIOCM_RTS) {
            mcr &= ~TIOCM_RTS;
            printf("RTS is OFF\n");
        }
        else {
            printf("RTS is ON\n");
            mcr |= TIOCM_RTS;
        }
#else
        if(i == 0){
            mcr &= ~TIOCM_RTS;
            printf("RTS is OFF\n");
            i=1;
        }else{
            printf("RTS is ON\n");
            mcr |= TIOCM_RTS;
            i=0;
        }
            
#endif
            ioctl(fd, TIOCMSET, &mcr);
        
        //ioctl(fd, TIOCMGET, &mcr);
        
        //if(mcr & TIOCM_CD){
        //  printf("DCD is ON\n");
        //}else {
        //  printf("DCD is OFF\n");
        //}
        //printf("\n");
        #endif
    }
    close(fd);
    return 0;
}
