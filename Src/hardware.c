#include "stm32f1xx_hal.h"
#include "usbd_core.h"

#include "hardware.h"

extern USBD_HandleTypeDef hUsbDeviceFS;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim2;

void BSP_LED_Init(void)
{
	HAL_TIM_Base_Start(&htim3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
	setLEDMode(LED_MSD_STANDBY);
}

void setLEDMode(LED_MODE mode)
{
	switch(mode) {
		case LED_MSD_STANDBY:
			__HAL_TIM_SET_AUTORELOAD(&htim3, 50);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 10);
			break;		
		case LED_MSD_CONNECTED:
			__HAL_TIM_SET_AUTORELOAD(&htim3, 200);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 50);
			break;		
		case LED_MEASUREMENT:
			__HAL_TIM_SET_AUTORELOAD(&htim3, 200);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 2);
			break;		
		case LED_CLEANING:
			__HAL_TIM_SET_AUTORELOAD(&htim3, 60);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 50);
			break;		
		default: //LED_ERROR:
			__HAL_TIM_SET_AUTORELOAD(&htim3, 50);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 51);
			
	}
	 __HAL_TIM_SET_COUNTER(&htim3, 0);
}

void usbOff() {
	BB_BIT(&USB_DISCONNECT_PORT->ODR, USB_DISCONNECT_PIN_N, 1);
//	USBD_DeInit(&hUsbDeviceFS); - Produces HardFault
	USBD_LL_Stop(&hUsbDeviceFS); 
	USBD_LL_DeInit(&hUsbDeviceFS); 
}

void 	switchToMeasurementMode(void ) {

	usbOff();
	
	//Set system clock to 8MHz
	__HAL_RCC_SYSCLK_CONFIG(RCC_SYSCLKSOURCE_HSE);
	__HAL_RCC_SYSCLK_CONFIG(RCC_SYSCLKSOURCE_HSE);
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	SystemCoreClockUpdate();
	//Run MCLK
	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
	//Blink type
	setLEDMode(LED_MEASUREMENT);
}

static uint32_t user_buttonTS;

void checkBtnClear(void) {
	if(HAL_GPIO_ReadPin(BUTTON_PORT,BUTTON_PIN) == GPIO_PIN_SET) {
		if(user_buttonTS == 0xFFFFFFFF) {
			user_buttonTS = HAL_GetTick() + CLEAR_BUTTON_TIMEOUT;
		} else {
			if(user_buttonTS < HAL_GetTick())
			{
				setLEDMode(LED_CLEANING);
				usbOff();
				HAL_FLASH_Unlock();
				for(uint32_t a = DATA_ADDRESS; a < END_FLASH_ADDRESS; a += FLASH_PAGE_SIZE) {
					FLASH_PageErase(a);
          int status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
          
          /* If the erase operation is completed, disable the PER Bit */
          CLEAR_BIT(FLASH->CR, FLASH_CR_PER);
					if(status !=HAL_OK) {
						setLEDMode(LED_ERROR);
						while(1);
					}
				}
				while(HAL_GetTick() < user_buttonTS + 5000) __wfi();
				NVIC_SystemReset();
			}
		}	
	} else {
		user_buttonTS = 0xFFFFFFFF;
	}
}


void HardFault_Handler() {
	setLEDMode(LED_ERROR);
	while(1) __wfi();
}

void BusFault_Handler() {
	HardFault_Handler();
}

void UsageFault_Handler() {
	HardFault_Handler();
}
