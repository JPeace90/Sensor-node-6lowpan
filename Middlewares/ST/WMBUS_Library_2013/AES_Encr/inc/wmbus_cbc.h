/**
* @file    wmbus_cbc.h
* @author  System Lab - NOIDA/VMA division - AMS
* @version V2.4.0
* @date    1-Feb-2016
* @brief   This file contains header for wmbus_cbc.h.
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

/**
* @addtogroup  wmbus_encryption 	wM-Bus Encryption
* @{
*/
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "wmbus_link.h"

/** @defgroup wmbus_encryption_Exported_Macros      wM-Bus Encryption Exported Macros
* @{
*/
#define IS_CBC_5_CONFIG_WORD(CONFIG_WORD)               ((CONFIG_WORD & 0x0500)?(1):(0))
#define SIZE_IN_CONFIG_WORD(CONF_WORD,SIZE)          {CONF_WORD = 0x0500; CONF_WORD|=((SIZE%16)==0)?((SIZE)/16)<<4:((SIZE)/16+1)<<4;}

/**
*@}
*/

/** @defgroup wmbus_encryption_Exported_Functions      wM-Bus Encryption Exported Functions
* @{
*/

uint16_t WMBus_AES_Encrypt_CBC(uint8_t *payload, uint16_t size, uint8_t *key, uint8_t *enc_payload, uint8_t *iv);
uint16_t WMBus_AES_Decrypt_CBC(uint8_t *payload, uint16_t size, uint8_t *key, uint8_t *dec_payload, uint8_t *iv);

/**
*@}
*/


/**
*@}
*/


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
