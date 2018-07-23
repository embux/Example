#!/bin/bash

DIR=/sys/class/gpio

if [ $# -lt 1 ] ; then
	echo "Using command: gpio_in.sh [00-07]"
	exit 0
fi

GPIO_NUM=$( printf "%02d" $1)

echo "in" > ${DIR}/gpio${GPIO_NUM}/direction

echo " Get gpio${GPIO_NUM} : $(cat ${DIR}/gpio${GPIO_NUM}/value)"
