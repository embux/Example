#!/bin/bash

#format mtdblock0 as fat
mkfs.vfat /dev/mtdblock0

#create mount point in mnt
mkdir /mnt/mtdb0

#mount
mount /dev/mtdblock0 /mnt/mtdb0

#show partition table
df
