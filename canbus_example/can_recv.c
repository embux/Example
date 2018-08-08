#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#define CAN_INTERFACE  "can1"

/****** can frame struct in can.h
struct can_frame {
    canid_t can_id;  // 32 bit CAN_ID + EFF/RTR/ERR flags 
    __u8    can_dlc; // frame payload length in byte (0 .. CAN_MAX_DLEN) 
    __u8    __pad;   // padding 
    __u8    __res0;  // reserved / padding 
    __u8    __res1;  // reserved / padding 
    __u8    data[CAN_MAX_DLEN] __attribute__((aligned(8)));
};

********************************************/

int main()
{
    struct ifreq ifr;
    struct sockaddr_can addr;
    int can_socket;
    struct can_frame frame;
    int i;

    can_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (can_socket < 0) 
    {
        printf("socket error!!\n");
        return -1;
    }

    addr.can_family = AF_CAN;
    strcpy(ifr.ifr_name, CAN_INTERFACE);
    if (ioctl(can_socket, SIOCGIFINDEX, &ifr)) 
    {
        printf("ioctl error!!\n");
        return -2;
    }
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(can_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0) 
    {
        printf("bind error!!\n");
        return -3;
    }

    //receive  frame
    if(read(can_socket, &frame, sizeof(frame)) < 0)
    {
        printf("read error!!\n");
        return -4;
    }

    if (frame.can_id & CAN_EFF_FLAG)
        printf("<0x%08x> ", frame.can_id & CAN_EFF_MASK);
    else
        printf("<0x%03x> ", frame.can_id & CAN_SFF_MASK);

    printf("[%d] ", frame.can_dlc);

    for (i = 0; i < frame.can_dlc; i++) 
    {
        printf("%02x ", frame.data[i]);
    }

    printf("\n");

    close(can_socket);

    return 0;   
}