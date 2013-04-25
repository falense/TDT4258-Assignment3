#!/bin/sh
cd /dev
cp /game/driver.ko ./
rmmod driver
insmod driver.ko
mknod driver c 252 0 

