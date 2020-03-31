#!/bin/sh

value=`uci get wireless.radio0.distance`
echo $value


if [ $value -eq $1 ];then
        echo "ok"
else
        echo "error"
        uci set wireless.radio0.distance=$1
        uci commit wireless
        wifi up
fi
