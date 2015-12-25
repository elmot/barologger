#include "ms5534.h"
#include <stm32f1xx_hal.h>
	/*
		Pin Nb	PINs	FUNCTIONs
		34	PA0	SPI2_SCK
		35	PA1	SPI2_MISO
		36	PA2	SPI2_MOSI
 */

/** set SCLK to the specified state (0/1) */
void setSCLK (unsigned char state) {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, (GPIO_PinState)state);
}

/** set DIN to the specified state (0/1) */
void setDIN (unsigned char state) {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, (GPIO_PinState) state);
}

/** returns the current state of DOUT */
unsigned char getDOUT (void) {
	return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1);
}

void WaitOnePulse (void) {
//	__nop();
//	__nop();
//	__nop();
//	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
}
/** Read the corresponding calibration word of the IC (index [1:4]) */
unsigned short getW (unsigned char index);
/** Start a D1 acquisition, wait for end of conversion and return the value */
unsigned short getD1 (void);
/** Start a D2 acquisition, wait for end of conversion and return the value */
unsigned short getD2 (void);
/* ===================================================================== */
/* waitOnDoutFall */
/* ===================================================================== */
void waitOnDoutFall(void)
{
unsigned char working;
working = 1;
while(working)
working = getDOUT();
}

/* ===================================================================== */
/* SerialGet16 */
/* ===================================================================== */
unsigned short SerialGet16(void)
{
	char i;
	unsigned short v;
	v = 0;
	setSCLK(0);
	WaitOnePulse();
	for (i=0; i<16; i++)	{
		setSCLK(1);
		WaitOnePulse();
		setSCLK(0);
		v = v << 1;
		if (getDOUT()==1)
		v = v | 1;
		WaitOnePulse();
	}
	return(v);
}

/* ===================================================================== */
/* SerialSendLsbFirst */
/* ===================================================================== */
void SerialSendLsbFirst(unsigned char pattern, unsigned char nbr_clock)
{
	unsigned char i;
	unsigned char c;
	setSCLK(0);
	WaitOnePulse();
	for (i=0; i<nbr_clock; i++) {
		c = pattern & 1;
		setDIN(c);
		WaitOnePulse();
		setSCLK(1);
		WaitOnePulse();
		setSCLK(0);
		pattern = pattern >> 1;
	}
}
/* ===================================================================== */
/* reset */
/* ===================================================================== */
void MS55Reset(void)
{
	SerialSendLsbFirst(0x55, 8);
	SerialSendLsbFirst(0x55, 8);
	SerialSendLsbFirst(0x00, 5);
}
/* ===================================================================== */
/* getW */
/* ===================================================================== */
unsigned short getW (unsigned char index) // 1 to 4
{
	unsigned short data;
	switch(index)
	{
		case 1:
			SerialSendLsbFirst(0x57, 8);
			SerialSendLsbFirst(0x01, 5);
			data = SerialGet16();
			break;
		case 2:
			SerialSendLsbFirst(0xD7, 8);
			SerialSendLsbFirst(0x00, 5);
			data = SerialGet16();
			break;
		case 3:
			SerialSendLsbFirst(0x37, 8);
			SerialSendLsbFirst(0x01, 5);
			data = SerialGet16();
			break;
		case 4:
			SerialSendLsbFirst(0xB7, 8);
			SerialSendLsbFirst(0x00, 5);
			data = SerialGet16();
			break;
	}
	SerialSendLsbFirst(0x00, 1); // to be compliant with the data sheet
	return(data);
}
/* ===================================================================== */
/* getD1 */
/* ===================================================================== */
unsigned short getD1 (void)
{
	unsigned short d1;
	SerialSendLsbFirst(0x2F, 8);
	SerialSendLsbFirst(0x00, 4);
	waitOnDoutFall();
	d1 = SerialGet16();
	SerialSendLsbFirst(0x00, 1); // to be compliant with the data sheet
	return(d1);
}
/* ===================================================================== */
/* getD2 */
/* ===================================================================== */
unsigned short getD2 (void)
{
	long d2;
	SerialSendLsbFirst(0x4F, 8);
	SerialSendLsbFirst(0x00, 4); // Note the difference with getD1
	waitOnDoutFall();
	d2 = SerialGet16();
	SerialSendLsbFirst(0x00, 1); // to be compliant with the data sheet
	return(d2);
}
/* ------------------------------------------------------------------------ */
/* --------------------------- ConvertWtoC5534 ---------------------------- */
/* ------------------------------------------------------------------------ */
double fc[7];
void ConvertWtoC5534 (long W1, long W2, long W3, long W4)
{
	long x, y;
	fc[1] = (W1 >> 1) & 0x7FFF;

	x = (W3 << 6) & 0x0FC0;
	y = W4 & 0x003F;
	fc[2] = x | y;

	fc[3] = (W4 >> 6) & 0x03FF;

	fc[4] = (W3 >> 6) & 0x03FF;

	x = (W1 << 10)& 0x0400;
	y = (W2 >> 6 )& 0x03FF;
	fc[5] = x | y;

	fc[6] = W2 & 0x003F;
}

void MS5534Measure(double *temperature, double *pressure)
{
	double dt, off, sens;
	double fd1, fd2, x;
	double temp, temp2;
	double press, press2;
	MS55Reset();
	long d1_arg = getD1();
	long d2_arg = getD2();
	d1_arg = d1_arg & 0xFFFF;
	d2_arg = d2_arg & 0xFFFF;
	fd1 = (double) d1_arg;
	fd2 = (double) d2_arg;
	dt = fd2 - ((8.0 * fc[5]) + 20224.0);
	off = fc[2] * 4.0 + ( ( ( fc[4]-512.0) * dt ) / 4096.0);
	sens = 24576.0 + fc[1] + ( ( fc[3] * dt ) / 1024.0);
	x = (( sens * (fd1- 7168.0)) / 16384.0) -off;
	press = 2500 + x * 10 / 32.0;
	temp = 200 + ( ( dt * ( fc[6] + 50.0 ) ) / 1024.0);
	temp2 = 0;
	press2 = 0;
	if(temp < 200) {
		temp2 = 11.0 * ( fc[6] +24 ) * ( 200 - temp ) * ( 200 - temp ) / 65536.0 /
		16.0;
		press2 = 3.0 * temp2 * ( press - 3500 ) / 16384.0;
	}
	if(temp > 450) {
		temp2 = 3.0 * ( fc[6] + 24 ) * ( 450 - temp ) * ( 450 - temp ) / 655536.0 /
		16.0;
	}
	temp = temp - temp2;
	press = press - press2;
	if (pressure!=0)
		*pressure = press / 10.0;
	if (temperature!=0)
		*temperature = temp / 10.0;
}

void MS55Init(void) 
{
	MS55Reset();
	ConvertWtoC5534 (getW(1), getW(2), getW(3), getW(4));
	
}
