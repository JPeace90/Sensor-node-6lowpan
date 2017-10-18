/**
* @file    wmbus_crc.h
* @author  System Lab - NOIDA/VMA division - AMS
* @version V2.4.2
* @date    1-Mar-2016
* @brief   This file contains routines for CRC computation
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WMBUS_CRC_H
#define __WMBUS_CRC_H
/* Includes ------------------------------------------------------------------*/
#include "wmbus_link.h"

/** @addtogroup WMBUS_Library
* @{
*/

/** @addtogroup WMBus_LinkLayer
*   @{
*/

/** @addtogroup WMBus_CRC         WMBus CRC
* @brief Configuration and management of WMBus Link layer CRC.
* @details See the file <i>@ref wmbus_crc.h</i> for more details.
* @{
*/



/** @defgroup WMBus_CRC_Exported_Functions        WMBus CRC Exported Functions
* @{
*/
void AppendCRC(uint8_t *pStart, uint8_t *pStop);
uint8_t CRCCheck(uint8_t *pStart, uint8_t *pStop);

void crcAppend(uint8_t crcData);
uint8_t crcVerify(uint8_t* crc);

/**
* @}
*/

/**
*@}
*/

/**
* @}
*/

/**
* @}
*/

#endif  /*__WMBUS_CRC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
