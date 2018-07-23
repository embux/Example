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

#define CAN_INTERFACE  "can0"

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
    int ret;
    struct can_frame frame;

    can_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (can_socket < 0) {
        printf("socket error!!\n");
        return -1;
    }

    addr.can_family = AF_CAN;
    strcpy(ifr.ifr_name, CAN_INTERFACE);
    if (ioctl(can_socket, SIOCGIFINDEX, &ifr)) {
        printf("ioctl error!!\n");
        return -2;
    }
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(can_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        printf("bind error!!\n");
        return -3;
    }

    //send frame
    frame.can_id = 0x05A1;

    frame.can_dlc = 8;
    frame.data[0] = 0x43;   //'C'
    frame.data[1] = 0x41;   //'A'
    frame.data[2] = 0x4E;   //'N'
    frame.data[3] = 0x31;   //'1'
    frame.data[4] = 0x74;   //'t'
    frame.data[5] = 0x65;   //'e'
    frame.data[6] = 0x73;   //'s'
    frame.data[7] = 0x74;   //'t'

    ret = write(can_socket, &frame, sizeof(frame));

    if(ret < 0){
        printf("send error!!\n");
        return -4;
    }

    close(can_socket);

    return 0;   
}