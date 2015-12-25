#include "stm32f1xx_hal.h"

#include "arm_math.h"
#include "hardware.h"
#include "ms5534.h"


const RECORD MARKER_RECORD = {126,0x8000};

int freeIdx = MAX_RECORDS;

//RECORD *  firstFreeRecord;

RECORD dataLog [MAX_RECORDS]  __attribute__((at(DATA_ADDRESS))) ;

bool findFirstFreeRecord() 
{
	for(freeIdx = 0; freeIdx < MAX_RECORDS; freeIdx +=2) {
		if(dataLog[freeIdx].mBarsM60 == 0xFFFF && dataLog[freeIdx].tempDegC == -1)
			return true;
	}
	return false;
}

static RECORD buffer [2];
uint8_t buffer_index = 0;

bool writeRecord(const RECORD * record)
{
	if(freeIdx >= MAX_RECORDS) return false;	
	buffer[buffer_index++] = *record;
	if(buffer_index <2) return true;
	buffer_index = 0;
	// RCC_HSICmd(ENABLE); Do we need this???
	//while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) != SET);
	HAL_FLASH_Unlock();
	FLASH->CR |= FLASH_CR_PG;
	
	__IO uint16_t * dst = (__IO uint16_t * )& dataLog[freeIdx];
	uint16_t * src = (uint16_t * )buffer;
	
	for(int i = 0; i < sizeof(RECORD); i++)
	{
		dst[i] = src[i];
		FLASH_WaitForLastOperation(HAL_MAX_DELAY);
	}
	
	FLASH->CR &= !FLASH_CR_PG;
	HAL_FLASH_Lock();
	//RCC_HSICmd(DISABLE); todo do we need this?
	freeIdx += 2;
	return true;
}

