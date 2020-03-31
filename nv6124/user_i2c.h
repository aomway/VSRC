#ifndef USER_I2C_H
#define USER_I2C_H

#include <stdint.h>

void user_i2c_write(int fd, uint8_t chip_addr, uint8_t reg_addr, uint8_t value);
uint8_t user_i2c_read(int fd, uint8_t chip_addr, uint8_t reg_addr);
int user_i2c_open(char *i2c_dev);
int user_i2c_close(int fd);


#endif
