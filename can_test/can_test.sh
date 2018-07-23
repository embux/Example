#!/bin/bash

#interface up
ip link set can0 type can bitrate 125000 triple-sampling on
ifconfig can0 up

ip link set can1 type can bitrate 125000 triple-sampling on
ifconfig can1 up

echo "Test CAN 0 send to CAN 1 :"
candump can1 -a -T 2000 > can1dump &
msleep 200
cansend can0 5A1#43.41.4E.31.74.65.73.74 
sleep 2
cat can1dump

sleep 1

echo "Test CAN 1 send to CAN 0 :"
candump can0 -a -T 2000 > can2dump &
msleep 200
cansend can1 6B2#43.41.4E.32.74.65.73.74
sleep 2
cat can2dump


