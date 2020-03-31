#!/bin/sh


value=`cat /sys/class/gpio/gpio38/value`

if [ $value -eq 0 ];then
	/data/auto_send &
fi

while [ $value -eq 0 ]
do
	ping_value=`ping -c 1 -W 1 192.168.1.11 | grep "64 bytes from 192.168.1.11"`

	if [ -n "$ping_value" ]; then
		while [ 1 -gt 0 ]
		do
			echo 1 > /sys/class/gpio/gpio34/value
			echo 1 > /sys/class/gpio/gpio35/value
			usleep 50000
			echo 0 > /sys/class/gpio/gpio34/value
			echo 0 > /sys/class/gpio/gpio35/value
			usleep 50000
		done
	else
		echo 1 > /sys/class/gpio/gpio34/value
		echo 1 > /sys/class/gpio/gpio35/value
		sleep 1
		echo 0 > /sys/class/gpio/gpio34/value
		echo 0 > /sys/class/gpio/gpio35/value
		sleep 1
	fi


done
