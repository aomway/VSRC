#! /bin/sh

flashcp -v ./BOOT.bin /dev/mtd0
flash_erase /dev/mtd1 0 0
./flashcp_bitstream ./system_wrapper.bit
flashcp -v /tmp/size_bitstream /dev/mtd2
flashcp -v ./uImage /dev/mtd3
flashcp -v ./devicetree.dtb /dev/mtd4
flashcp -v ./uramdisk.image.gz.jffs /dev/mtd5
umount /data
flash_erase -j /dev/mtd6 0 0
mount -t jffs2 /dev/mtdblock6 /data

tar -xvf data.tar -C /
#cp -rf data/* /data
sync


while [ 1 -gt 0 ]
do
	echo 1 > /sys/class/gpio/gpio34/value
	echo 1 > /sys/class/gpio/gpio35/value	
	usleep 50000
	echo 0 > /sys/class/gpio/gpio34/value
	echo 0 > /sys/class/gpio/gpio35/value
	usleep 50000
done

