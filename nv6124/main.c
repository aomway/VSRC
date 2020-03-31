/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "user_i2c.h"
#include "video.h"
//#include "video.h"


extern int hdmi_fd;

int chip_id[4];


unsigned int nvp6124_cnt = 0;

unsigned int nvp6124_slave_addr[4];




int check_rev(unsigned int dec)
{
        int ret;
        gpio_i2c_write(dec, 0xFF, 0x00);
        ret = gpio_i2c_read(dec, 0xf5);
        return ret;
}

int check_id(unsigned int dec)
{
        int ret;
        gpio_i2c_write(dec, 0xFF, 0x00);
        ret = gpio_i2c_read(dec, 0xf4);
        return ret;
}




int main()
{
	unsigned char value;
	int Status;
	int ch;
	nvp6124_slave_addr[0] = 0x60;
	hdmi_fd = user_i2c_open("/dev/i2c-1"); 

	value=check_id(0x60);
    	printf("chip id %x \n\r",value);

	chip_id[0]=value;
	
	nvp6124_common_init();

	for(ch=0;ch<4;ch++)
    {
	  nvp6124_set_chnmode(ch, PAL, NVP6124_VI_1080P_2530);
	}

	nvp6124b_set_portmode(0x60, 0, NVP6124_OUTMODE_1MUX_FHD, 0); //chip 0  portsel 1  vin 0 

	user_i2c_close(hdmi_fd);

    return 0;
}
