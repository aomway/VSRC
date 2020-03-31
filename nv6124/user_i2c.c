#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>


#define DEFAULT_I2C_BUS "/dev/i2c-1"
int hdmi_fd; 
int user_i2c_open(char *i2c_dev)
{
    int fd;
    if((fd=open(i2c_dev,O_RDWR))<0){
        fprintf(stderr,"Could not open i2c at %s\n",DEFAULT_I2C_BUS);
        perror(DEFAULT_I2C_BUS);
        exit(1);
    }
    return fd;
}

int user_i2c_close(int fd)
{
    close(fd);
    return 0;
}

void user_i2c_write(int fd, uint8_t chip_addr, uint8_t reg_addr, uint8_t value)
{
    struct i2c_rdwr_ioctl_data msg_rdwr;
    struct i2c_msg i2cmsgs[2];
    uint8_t buf[2];
    int i;

    msg_rdwr.msgs = &i2cmsgs[0];
    msg_rdwr.nmsgs = 1;

    buf[0] = reg_addr;
    buf[1] = value;

    //printf("wr:0x%02x,%02x,%02x\n", chip_addr, reg_addr, value);
    i2cmsgs[0].addr  = chip_addr >> 1; //chip_addr>>1 ???
    i2cmsgs[0].flags = 0;
    i2cmsgs[0].len   = 2;
    i2cmsgs[0].buf   = buf;

    if((i=ioctl(fd,I2C_RDWR,&msg_rdwr))<0){
        perror("wr:ioctl()");
        //fprintf(stderr,"ioctl returned %d\n",i);
        //return DIB_RETURN_ERROR;
    }

    //return DIB_RETURN_SUCCESS;

}

uint8_t user_i2c_read(int fd, uint8_t chip_addr, uint8_t reg_addr)
{
    struct i2c_rdwr_ioctl_data msg_rdwr;
    struct i2c_msg i2cmsgs[2];
    //uint8_t bufw[2];
    uint8_t bufr[2];
    int i;

    bufr[0] = 0;
    msg_rdwr.msgs = i2cmsgs;
    msg_rdwr.nmsgs = 2;

    //printf("rd:0x%02x,%02x\n", chip_addr,reg_addr);

    i2cmsgs[0].addr  = chip_addr >>1; //chip_addr>>1 ???
    i2cmsgs[0].flags = 0;
    i2cmsgs[0].len   = 1;
    i2cmsgs[0].buf   = &reg_addr;

    i2cmsgs[1].addr  = chip_addr>>1; //chip_addr>>1 ???
    i2cmsgs[1].flags = I2C_M_RD;
    i2cmsgs[1].len   = 1;
    i2cmsgs[1].buf   = bufr;

    if((i=ioctl(fd,I2C_RDWR,&msg_rdwr))<0){
        perror("rd:ioctl()");
        //fprintf(stderr,"ioctl returned %d\n",i);
        //return DIB_RETURN_ERROR;
    }
    return bufr[0];
}

void gpio_i2c_write(unsigned char chip_addr, unsigned char reg_addr, unsigned char value)
{
	user_i2c_write(hdmi_fd, chip_addr, reg_addr, value);
}

unsigned char gpio_i2c_read(unsigned char chip_addr, unsigned char reg_addr)
{
	return user_i2c_read(hdmi_fd, chip_addr,reg_addr);

}


