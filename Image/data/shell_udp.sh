#!/bin/sh

count=0
while [ 1 -gt 0 ]
do

value=`ping -c 1 -W 1 192.168.1.11 | grep "64 bytes from 192.168.1.11"`

if [ -n "${value}" ] && [ $count -eq 0 ]; then
        /data/udp_dump_armhf 192.168.1.11 /dev/mpegts &
        count=1
fi


if [ -z "${value}" ] && [ $count -eq 1 ]; then
        echo "++++++++++++++++++++++++++++++++"
        ID=`ps -ef | grep "udp_dump_armhf" | grep -v "grep" | awk '{print $1}'`
        echo $ID
        count=0
        for id in $ID
        do
                kill -9 $id
        done
	echo 1 > /sys/class/gpio/gpio34/value
fi
sleep 5
done
