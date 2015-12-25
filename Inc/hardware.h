#ifndef __HARDWARE_H
#define __HARDWARE_H

#include "stm32f1xx_hal.h"

#include <stdbool.h>

#define LED_PORT GPIOB
#define LED_GPIO_PIN GPIO_PIN_1

//#define USB_DISCONNECT_GPIO_PIN GPIO_PIN_9
#define USB_DISCONNECT_PORT GPIOB
#define USB_DISCONNECT_PIN_N 9

#define BUTTON_PORT GPIOB
#define BUTTON_PIN  GPIO_PIN_8

#define CLEAR_BUTTON_TIMEOUT 2000

#define BB_BIT(addr, bit, value) 	*((uint32_t*)((PERIPH_BB_BASE + 32 * (((uint32_t)addr) - PERIPH_BASE)) + bit*4)) = value;

#define DATA_ADDRESS (FLASH_BASE + 0x8000)
//96kb / 3b
#define MAX_RECORDS (32768)
#define END_FLASH_ADDRESS (FLASH_BASE + 0x20000)
#define TEXT_LINES_PER_BLOCK (16)
#define TEXT_LINE_LENGTH (32)

#define MARKER_TEMP 127

typedef enum LED_MODE {
	LED_MSD_STANDBY,
	LED_MSD_CONNECTED,
	LED_MEASUREMENT,
	LED_CLEANING,
	LED_ERROR
}LED_MODE;

#pragma pack(1)
typedef struct RECORD {
int8_t tempDegC;
uint16_t mBarsM60;
} RECORD;

extern const RECORD MARKER_RECORD;

extern RECORD dataLog [MAX_RECORDS];

void BSP_LED_Init(void);
void BSP_SensorInit(void);

void setLEDMode(LED_MODE);
void switchToMeasurementMode(void);
void checkBtnClear(void);

bool findFirstFreeRecord(void); 
bool writeRecord(const RECORD * record);

#endif
