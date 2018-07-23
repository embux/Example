#!/bin/bash

DIR=/sys/class/gpio

if [ $# -lt 2 ] ; then
	echo "Using command: gpio_out.sh [00-07] [h/l]"
	exit 0
fi

GPIO_NUM=$( printf "%02d" $1)

echo "out" > ${DIR}/gpio${GPIO_NUM}/direction

if [ $2=="h" ] ; then
	echo "1" > ${DIR}/gpio${GPIO_NUM}/value
else
	echo "0" > ${DIR}/gpio${GPIO_NUM}/value
fi
