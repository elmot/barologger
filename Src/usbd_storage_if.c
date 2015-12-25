/**
  ******************************************************************************
  * @file           : usbd_storage_if.c
  * @brief          : Memory management layer
  ******************************************************************************
  * COPYRIGHT(c) 2015 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  * 1. Redistributions of source code must retain the above copyright notice,
  * this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  * this list of conditions and the following disclaimer in the documentation
  * and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of its contributors
  * may be used to endorse or promote products derived from this software
  * without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "usbd_storage_if.h"
/* USER CODE BEGIN INCLUDE */
#include "hardware.h"
/* USER CODE END INCLUDE */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @{
  */

/** @defgroup USBD_STORAGE 
  * @brief usbd core module
  * @{
  */ 

/** @defgroup USBD_STORAGE_Private_TypesDefinitions
  * @{
  */ 
/* USER CODE BEGIN PRIVATE_TYPES  */
/* USER CODE END PRIVATE_TYPES */ 
/**
  * @}
  */ 

/** @defgroup USBD_STORAGE_Private_Defines
  * @{
  */ 
#define STORAGE_LUN_NBR                  1  
#define STORAGE_BLK_NBR                  4400  
#define STORAGE_BLK_SIZ                  0x200

/* USER CODE BEGIN PRIVATE_DEFINES  */
/* USER CODE END PRIVATE_DEFINES */
  
/**
  * @}
  */ 

/** @defgroup USBD_STORAGE_Private_Macros
  * @{
  */ 
/* USER CODE BEGIN PRIVATE_MACRO  */
#define fileSize() ((freeIdx + 1) * 32);
/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */ 

/** @defgroup USBD_STORAGE_IF_Private_Variables
  * @{
  */
/* USB handler declaration */
/* Handle for USB Full Speed IP */
  USBD_HandleTypeDef  *hUsbDevice_0;
/* USER CODE BEGIN INQUIRY_DATA_FS */ 
/* USB Mass storage Standard Inquiry Data */
const int8_t  STORAGE_Inquirydata_FS[] = {//36
  
  /* LUN 0 */
  0x00,		
  0x80,		
  0x02,		
  0x02,
  (STANDARD_INQUIRY_DATA_LEN - 5),
  0x00,
  0x00,	
  0x00,
  'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
  'P', 'r', 'o', 'd', 'u', 'c', 't', ' ', /* Product      : 16 Bytes */
  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
  '0', '.', '0' ,'1',                     /* Version      : 4 Bytes */
}; 
/* USER CODE END INQUIRY_DATA_FS */ 

/* USER CODE BEGIN PRIVATE_VARIABLES  */
/* USER CODE END  PRIVATE_VARIABLES */

/**
  * @}
  */ 
 
/** @defgroup USBD_STORAGE_IF_Exported_Variables
  * @{
  */ 
  extern USBD_HandleTypeDef hUsbDeviceFS;
/* USER CODE BEGIN EXPORTED_VARIABLES  */
extern int freeIdx;
/* USER CODE END  EXPORTED_VARIABLES */

/**
  * @}
  */ 
  
/** @defgroup USBD_STORAGE_Private_FunctionPrototypes
  * @{
  */
static int8_t STORAGE_Init_FS (uint8_t lun);
static int8_t STORAGE_GetCapacity_FS (uint8_t lun, 
                           uint32_t *block_num, 
                           uint16_t *block_size);
static int8_t  STORAGE_IsReady_FS (uint8_t lun);
static int8_t  STORAGE_IsWriteProtected_FS (uint8_t lun);
static int8_t STORAGE_Read_FS (uint8_t lun, 
                        uint8_t *buf, 
                        uint32_t blk_addr,
                        uint16_t blk_len);
static int8_t STORAGE_Write_FS (uint8_t lun, 
                        uint8_t *buf, 
                        uint32_t blk_addr,
                        uint16_t blk_len);
static int8_t STORAGE_GetMaxLun_FS (void);

/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */
void fillBootSector(uint8_t * buf);
void fillFat(uint8_t * buf, int blkNum);
void fillDir(uint8_t * buf);
void fillFile(uint8_t * buf, int blkNum);
/* USER CODE END  PRIVATE_FUNCTIONS_DECLARATION */

/**
  * @}
  */ 
  
USBD_StorageTypeDef USBD_Storage_Interface_fops_FS =
{
  STORAGE_Init_FS,
  STORAGE_GetCapacity_FS,
  STORAGE_IsReady_FS,
  STORAGE_IsWriteProtected_FS,
  STORAGE_Read_FS,
  STORAGE_Write_FS,
  STORAGE_GetMaxLun_FS,
  (int8_t *)STORAGE_Inquirydata_FS,
};

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : STORAGE_Init_FS
* Description    : 
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_Init_FS (uint8_t lun)
{
  /* USER CODE BEGIN 2 */ 
  return (USBD_OK);
  /* USER CODE END 2 */ 
}

/*******************************************************************************
* Function Name  : STORAGE_GetCapacity_FS
* Description    : 
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_GetCapacity_FS (uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
  /* USER CODE BEGIN 3 */   
  *block_num  = STORAGE_BLK_NBR;
  *block_size = STORAGE_BLK_SIZ;
  return (USBD_OK);
  /* USER CODE END 3 */ 
}

/*******************************************************************************
* Function Name  : STORAGE_IsReady_FS
* Description    : 
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t  STORAGE_IsReady_FS (uint8_t lun)
{
  /* USER CODE BEGIN 4 */ 
  return (USBD_OK);
  /* USER CODE END 4 */ 
}

/*******************************************************************************
* Function Name  : STORAGE_IsWriteProtected_FS
* Description    : 
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t  STORAGE_IsWriteProtected_FS (uint8_t lun)
{
  /* USER CODE BEGIN 5 */ 
  return (USBD_FAIL);
  /* USER CODE END 5 */ 
}

/*******************************************************************************
* Function Name  : STORAGE_Read_FS
* Description    : 
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_Read_FS (uint8_t lun, 
                        uint8_t *buf, 
                        uint32_t blk_addr,                       
                        uint16_t blk_len)
{
  /* USER CODE BEGIN 6 */
	if(blk_len != 1) return USBD_FAIL;
	if(blk_addr > STORAGE_BLK_NBR) return USBD_FAIL;
	if(blk_addr >= 21) {
		fillFile(buf, blk_addr - 21);
	} else {
		memset(buf, 0, STORAGE_BLK_SIZ);
		if(blk_addr == 0) {
			fillBootSector(buf);
		} else if(blk_addr >= 1 && blk_addr <=18) { 
			fillFat(buf, blk_addr-1);
		} else if(blk_addr == 19) {
			fillDir(buf);
		}
	}
	
  switch(blk_addr) {
		case 0:break;
		case 1:break;
	}
  return (USBD_OK);
  /* USER CODE END 6 */ 
}

/*******************************************************************************
* Function Name  : STORAGE_Write_FS
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_Write_FS (uint8_t lun, 
                         uint8_t *buf, 
                         uint32_t blk_addr,
                         uint16_t blk_len)
{
  /* USER CODE BEGIN 7 */ 
  return (USBD_FAIL);
  /* USER CODE END 7 */ 
}

/*******************************************************************************
* Function Name  : STORAGE_GetMaxLun_FS
* Description    : 
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_GetMaxLun_FS (void)
{
  /* USER CODE BEGIN 8 */ 
  return (STORAGE_LUN_NBR - 1);
  /* USER CODE END 8 */ 
}

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */
void fillBootSector(uint8_t * buf) {
	static const uint8_t block_start[] = {
 0xEB, 0x3C, 0x90, 0x6D, 0x6B, 0x66, 0x73, 0x2E, 0x66, 0x61, 0x74, 0x00, 0x02, 0x01, 0x01, 0x00,
 0x01, 0x10, 0x00, 0x30, 0x11, 0xF8, 0x12, 0x00, 0x20, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x29, 0x5E, 0xE9, 0xC3, 0x7D, 0x42, 0x41, 0x52, 0x4F, 0x5F,
 0x45, 0x4C, 0x4D, 0x4F, 0x54, 0x20, 0x46, 0x41, 0x54, 0x31, 0x36, 0x20, 0x20, 0x20, 0x0E, 0x1F,
 0xBE, 0x5B, 0x7C, 0xAC, 0x22, 0xC0, 0x74, 0x0B, 0x56, 0xB4, 0x0E, 0xBB, 0x07, 0x00, 0xCD, 0x10,
 0x5E, 0xEB, 0xF0, 0x32, 0xE4, 0xCD, 0x16, 0xCD, 0x19, 0xEB, 0xFE, 0x4E, 0x4F, 0x0D, 0x0A, 0x00};
	memcpy(buf, block_start, sizeof(block_start));
 buf[510] = 0x55;
 buf[511] = 0xAA;
}

void fillFat(uint8_t * buf, int blkNum) {
	int fSize = fileSize();
	int lastCluster = 3 + (fSize + 511) / 512;
	int clusterNo = 1 + blkNum * 256;
	uint16_t * wordBuf = (uint16_t *)buf;
  for(int i = 0; i <256; i++) {
		if(clusterNo == lastCluster) {
			wordBuf[i] = 0xFFFF;
			break;
		} else if(clusterNo > lastCluster) {
			break;
		} else 
		wordBuf[i] = clusterNo++;
	}
	
	if(blkNum == 0) {
		wordBuf[0] = 0xFFF8;
		wordBuf[1] = 0xFFFF;
		wordBuf[2] = 0;
	}
}

void fillDir(uint8_t * buf) {
	static const uint8_t block_start[] = {
		0x42, 0x41, 0x52, 0x4F, 0x5F, 0x45, 0x4C, 0x4D, 0x4F, 0x54, 0x20, 0x08, 0x00, 0x00, 0xB0, 0x0E,
		0x98, 0x47, 0x98, 0x47, 0x00, 0x00, 0xB0, 0x0E, 0x98, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x4C, 0x45, 0x46, 0x54, 0x5F, 0x32, 0x30, 0x30, 0x4D, 0x49, 0x4E, 0x20, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 0x0E, 0x98, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x42, 0x41, 0x52, 0x4F, 0x20, 0x20, 0x20, 0x20, 0x54, 0x58, 0x54, 0x20, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 0x0E, 0x98, 0x47, 0x03
	};
	memcpy(buf, block_start, sizeof(block_start));
	//"left minutes" offset = 0x25;
	int leftRecords = MAX_RECORDS - freeIdx;
	buf[0x27] = '0' + (leftRecords / 60) % 10; 
	buf[0x26] = '0' + (leftRecords / 600) % 10; 
	buf[0x25] = '0' + leftRecords / 6000;
	//file size offset = 0x5C;
  *(uint32_t*)(&buf[0x5c]) = fileSize();
}

void fillFile(uint8_t * buf, int blkNum) {
	int blockRecord = blkNum * TEXT_LINES_PER_BLOCK; 
	if(blockRecord >= freeIdx) return;
	memset(buf, 32, STORAGE_BLK_SIZ);
	if(blkNum==0) {
		memcpy(buf,"S    \tN   \tT, C\tP, mBar\tAlt, m\r\n", TEXT_LINE_LENGTH);
	}
	int serie = 1;
	int n = 1;
	for(int i = 1; i < blockRecord; i++) {
		if(dataLog[i].mBarsM60 == MARKER_RECORD.mBarsM60 && dataLog[i].tempDegC == MARKER_RECORD.tempDegC) {
			serie++;
			n = 1;
		} else n++;
	}
	for(int i = 0; i < TEXT_LINES_PER_BLOCK; i++, blockRecord++) {
		if(blockRecord >= freeIdx) break;
		if(blkNum == 0 && i==0) continue;
		int textIndex = i*TEXT_LINE_LENGTH;
		if(dataLog[blockRecord].mBarsM60 == MARKER_RECORD.mBarsM60 && dataLog[blockRecord].tempDegC == MARKER_RECORD.tempDegC) {
			serie++;
			n = 1;
			memset(&buf[textIndex], '*', TEXT_LINE_LENGTH - 2);
		} else {
			RECORD r = dataLog[blockRecord];
			sprintf((char*)&buf[textIndex],"%04d\t%05d\t%+04d\t%07.2f\t?????", serie, n++, r.tempDegC, r.mBarsM60 / 60.0);
			
		}
		buf[textIndex + TEXT_LINE_LENGTH - 2] = '\r';
		buf[textIndex + TEXT_LINE_LENGTH - 1] = '\n';
	}
}
/* USER CODE END  PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @}
  */ 

/**
  * @}
  */  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
