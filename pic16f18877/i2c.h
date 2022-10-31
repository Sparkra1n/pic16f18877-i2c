#ifndef _I2C_H
#define _I2C_H

#include <pic16f18877.h>

void i2cInit();
void i2cStart();
void i2cStop();
void i2cWrite(unsigned char);
unsigned char i2cRead(unsigned char);

#endif
