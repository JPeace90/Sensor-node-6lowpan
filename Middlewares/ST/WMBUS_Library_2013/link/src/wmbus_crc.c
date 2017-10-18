/**
* @file    wmbus_crc.c
* @author  System Lab - NOIDA/VMA division - AMS
* @version V2.4.2
* @date    1-Mar-2016
* @brief   This file contains routines for CRC calculation
* @details
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* THIS SOURCE CODE IS PROTECTED BY A LICENSE.
* FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED
* IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
*
* <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
*/

/* Includes ------------------------------------------------------------------*/
#include "wmbus_crc.h"

/** @addtogroup WMBUS_Library
* @{
*/


/** @addtogroup WMBus_LinkLayer
*   @{
*/

/** @addtogroup WMBus_CRC
*   @{
*/




/** @defgroup WMBus_CRC_Private_Defines  WMBus CRC Private Defines
* @{
*/
#define CRC_POLYNOM         0x3D65

/**
* @}
*/



/** @defgroup WMBus_CRC_Private_FunctionPrototypes   WMBus CRC Private Function Prototypes
* @{
*/
uint16_t crcCalc(uint16_t crcReg, uint8_t crcData); 

/**
* @}
*/

/** @defgroup WMBus_CRC_Private_Functions   WMBus CRC Private Functions
* @{
*/

/**
* @brief  Calculates the 16-bit CRC. 
* @param  crcData  - Data to perform the CRC-16 operation on.
*         crcReg   - Current or initial value of the CRC calculation
* @retval None                 
*/
void AppendCRC(uint8_t *pStart, uint8_t *pStop)
{
  uint16_t  seed= 0x0000;  
  while (pStart != pStop)
  {
    seed = crcCalc(seed, *pStart);
    pStart++;
  }
  seed =~seed;
  pStop[0]  = (uint8_t)(seed>>8);
  pStop[1]  = (uint8_t)seed;
}

/**
* @brief  Calculates the 16-bit CRC. 
* @param  crcData  - Data to perform the CRC-16 operation on.
*         crcReg   - Current or initial value of the CRC calculation
* @retval 0 or 1
*                       
*/
uint8_t CRCCheck(uint8_t *pStart, uint8_t *pStop)
{
  uint16_t  seed= 0x0000;
  
  while (pStart != pStop)
  {
    seed = crcCalc(seed, *pStart);
    pStart++;
  }
  seed =~seed;
  if((pStop[0]  == (uint8_t)(seed>>8))&&(pStop[1]  == (uint8_t)(seed)))
  {
    return 1;
  }
  return 0;
}

/**
* @brief  Calculates the 16-bit CRC. The function requires
*         that the CRC_POLYNOM is defined,
*           which gives the wanted CRC polynom. 
* @param  crcData  - Data to perform the CRC-16 operation on.
*         crcReg   - Current or initial value of the CRC calculation
* @retval crcReg Current or initial value of the CRC calculation                   
*/
uint16_t crcCalc(uint16_t crcReg, uint8_t crcData) 
{
  uint8_t i;
  
  for (i = 0; i < 8; i++) 
  {
    // If upper most bit is 1
    if (((crcReg & 0x8000) >> 8) ^ (crcData & 0x80))
      crcReg = (crcReg << 1)  ^ CRC_POLYNOM;
    else
      crcReg = (crcReg << 1);
    
    crcData <<= 1;
  }
  
  return crcReg;
}

static uint16_t crc_seed=0;

/**
* @brief  Calculates the 16-bit CRC.
*          The result is set in a static variable that is used as a seed.
*          This is usable for iterative procedures passing data for CRC computing byte by byte.
* @param  crcData  - Data to perform the CRC-16 operation on.
* @retval None.                   
*/
void crcAppend(uint8_t crcData)
{
  crc_seed=crcCalc(crc_seed,crcData);
}

/**
* @brief  Verifies the 16-bit CRC taking as input the CRC for checking.
*         The data passed are compared with the CRC computed until this time by the @ref crcAppend.
* @param  crc  - CRC received bytes.
* @retval None.                   
*/
uint8_t crcVerify(uint8_t* crc)
{
  uint8_t ret=0;
  crc_seed =~crc_seed;
  if((crc[0]  == (uint8_t)(crc_seed>>8))&&(crc[1]  == (uint8_t)(crc_seed)))
  {
    ret=1;
  }
  crc_seed=0;
  
  return ret;
}
  
/**
* @}
*/


/**
* @}
*/


/**
* @}
*/

/**
* @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
