# Barologger

This project is a barologger device for stratospheric balloons. 

##Techical data:
 * MCU: STM32F103CBTx; [BTE14-07](https://www.aliexpress.com/item/leaflabs-Leaf-maple-mini-ARM-STM32-compatibility/1987703487.html) development board is used (clone of [LeafLab Maple Mini](https://github.com/leaflabs/maplemini))
 * Sensor: [MS5534](http://www.amsys.info/products/ms5534.htm)
 * PC communication: USB (Mass Storage Device emulation)
 * Sampling rate: 1 sec 
 * Pressure range: 10-1100 mBar
 * Storage capacity: ~9 hr
 
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

MCU/BRD Pin | MCU Function | Sensor Function  | Sensor Pin
------ | ------ | ----- | ---
10/11 |	PA0	  | SCK   | 2
11/10 |	PA1	  | DOUT  | 3
12/9 |	PA2	  | DIN   | 4
13/8 |  PA3   | MCLK  | 5
 | | GND | 1
 | | VDD | 6



