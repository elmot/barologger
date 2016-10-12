# Barologger

This project is a barologger device for stratospheric balloons. 

##Techical data:
 * MCU: STM32F103CBTx; BTE14-07 development board is used (clone of Maple Mini)
 * Sensor: MS5534(http://www.amsys.info/products/ms5534.htm)
 * PC communication: USB (Mass Storage Device emulation)
 * Sampling period: _TBD_
 * Pressure range: 10-1100mBar
 * Storage capacity: _TBD_
 
##How To Use
 
###Start measurement
 * Power up devise without connecting USB. 
 * After 3 seconds the device starts acquiring data.

###Obtain data
 * Power off the device
 * Connect USB 
 * The device is detected as a flash drive containing text data log.

###Clear storage
 * Press a user button (not reset!) for 3 seconds. 
 * Onboard LED will blink rapidly for several seconds. 
 * Device is empty
 
_________
##Pinout

MCU Pin | MCU Function | Sensor Function  | Sensor Pin
------ | ------ | ----- | ---
		10 |	PA0	  | SCK   | 2
		11 |	PA1	  | DOUT  | 3
		12 |	PA2	  | DIN   | 4
    13 |  PA3   | MCLK  | 5
 | | GND | 1
 | | VDD | 6



