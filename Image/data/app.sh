#! /bin/sh

cd /mnt
ifconfig lo up
ifconfig eth0 hw ether 00:0C:18:EF:FF:ED
ifconfig eth0 up
ifconfig eth0 192.168.1.22
#echo "performance" > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
#echo "1200000" > /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq
#echo 1 > /sys/class/leds/led1/brightness
cp memtool /usr/bin/
mount /dev/mmcblk0p1 /media/
cd /data

#cp /media/bin/* /bin
#cp /media/lib/* /lib

tar -xvf ffmpeg_lib.tar -C /tmp

export LD_LIBRARY_PATH="/tmp/lib"

cp ./ffmpeg  /usr/bin
tar xf lmatio.tar.gz -C /root
cp -rf /root/lmatio/* /usr/lib/
tar xf rtp_opus_install.tar -C /tmp
cp /tmp/rtp_opus_install/lib/* /usr/lib
cp /tmp/rtp_opus_install/opus_tx* /data/
echo 54 > /sys/class/gpio/export
echo 56 > /sys/class/gpio/export
echo 55 > /sys/class/gpio/export
echo 62 > /sys/class/gpio/export
echo 63 > /sys/class/gpio/export
echo 64 > /sys/class/gpio/export
echo 65 > /sys/class/gpio/export
echo 66 > /sys/class/gpio/export
echo 67 > /sys/class/gpio/export
echo 68 > /sys/class/gpio/export
echo 69 > /sys/class/gpio/export
echo 70 > /sys/class/gpio/export
echo 57 > /sys/class/gpio/export
echo 74 > /sys/class/gpio/export
echo 75 > /sys/class/gpio/export
echo 75 > /sys/class/gpio/export
echo 38 > /sys/class/gpio/export
#OLED

./ethtool -s eth0 autoneg off speed 100 duplex full

echo 2 > /proc/sys/kernel/printk

echo 29 > /sys/class/gpio/export
echo 31 > /sys/class/gpio/export
echo 34 > /sys/class/gpio/export
echo 35 > /sys/class/gpio/export
echo 36 > /sys/class/gpio/export
echo 37 > /sys/class/gpio/export

echo out > /sys/class/gpio/gpio29/direction
echo out > /sys/class/gpio/gpio34/direction
echo out > /sys/class/gpio/gpio35/direction
echo out > /sys/class/gpio/gpio36/direction
echo out > /sys/class/gpio/gpio37/direction
echo out > /sys/class/gpio/gpio31/direction
echo out > /sys/class/gpio/gpio55/direction
echo out > /sys/class/gpio/gpio62/direction
echo out > /sys/class/gpio/gpio63/direction
echo out > /sys/class/gpio/gpio64/direction
echo out > /sys/class/gpio/gpio65/direction
echo out > /sys/class/gpio/gpio66/direction
echo out > /sys/class/gpio/gpio67/direction
echo out > /sys/class/gpio/gpio68/direction
echo out > /sys/class/gpio/gpio69/direction
echo out > /sys/class/gpio/gpio70/direction
echo out > /sys/class/gpio/gpio57/direction
echo out > /sys/class/gpio/gpio74/direction
echo out > /sys/class/gpio/gpio75/direction
echo in  > /sys/class/gpio/gpio38/direction
echo 0 > /sys/class/gpio/gpio74/value
echo 1 > /sys/class/gpio/gpio34/value
echo 1 > /sys/class/gpio/gpio35/value
echo 1 > /sys/class/gpio/gpio36/value
echo 1 > /sys/class/gpio/gpio37/value


cd /media

#./update_qspi.sh

./assoc_tx.sh

echo 0 > /sys/class/gpio/gpio37/value
./upload_tx.sh
./nv6124b_init &
./sz7035_tx_ctrl &
./shell_udp.sh &
./udp_get_iwinfo 8050 > /dev/null &
./mavlink_proxy_vsrc 192.168.1.11 8070 > /dev/null &
./write_ts &
