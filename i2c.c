#include "i2c.h"
#include <pic16f18877.h>

static void i2cWait();
static void i2cAck();
static void i2cNack();

static void i2cWait()
{
    while (SSP1CON2bits.SEN || SSP1CON2bits.RSEN || SSP1CON2bits.PEN || SSP1CON2bits.RCEN || SSP1STATbits.R_nW);
}								

static void i2cAck()
{
	SSP1CON2bits.ACKDT = 0;
	SSP1CON2bits.ACKEN = 1;
	while(SSP1CON2bits.ACKEN);
}

static void i2cNack()
{
	SSP1CON2bits.ACKDT = 1;
	SSP1CON2bits.ACKEN = 1;
	while(SSP1CON2bits.ACKEN);
}

void i2cRepStart()
{
	SSP1CON2bits.RSEN = 1;
	while(SSP1CON2bits.RSEN);
}

void i2cInit()
{
	TRISCbits.TRISC3 = 1;
	TRISCbits.TRISC4 = 1;

    ANSELC = 0x00;
    RC3PPS = 0X14; 
    RC4PPS = 0X15;
    SSP1CON3bits.SDAHT = 1;
    SSP1CON2bits.ACKEN = 1;
    
    SSP1STATbits.SMP = 1;
    SSP1STATbits.CKE = 0;
    
	SSP1STAT |= 0x80;
	SSP1CON1 = 0x28;
	SSP1ADD = 50;
}

void i2cStart()
{
	SSP1CON2bits.SEN = 1;
	while(SSP1CON2bits.SEN);

}

void i2cStop()
{
	SSP1CON2bits.PEN = 1;
	while(SSP1CON2bits.PEN);
}

void i2cWrite(unsigned char data)
{
    SSP1BUF = data;
    while(SSP1STATbits.BF);
    i2cWait();
}

unsigned char i2cRead(unsigned char ack)
{
	unsigned char data = 0x00;

	SSP1CON2bits.RCEN = 1;
	while (!SSP1STATbits.BF);
	data = SSP1BUF;
	i2cWait();
	if(ack)
		i2cAck();
	else
		i2cNack();

	return data;
}

