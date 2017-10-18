/**
* @file    wmbus_cbc.c
* @author  System Lab - NOIDA/VMA division - AMS
* @version V2.4.0
* @date    1-Feb-2016
* @brief   This file contains the encryption/decryption routines.
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
#include "wmbus_cbc.h"
#include "aes.h"


/** @defgroup wmbus_encryption_Private_Functions      wM-Bus Encryption Private Functions
* @{
*/

/**
* @brief  This routine encrypts a payload buffer returning the encrypted version on another buffer.
* @param  payload: the buffer to encrypt.
* @param  size: the buffer size.
* @param  key: the key to be used for encryption (16 bytes).
* @param  enc_payload: the destination buffer.
* @param  iv: the initialization vector.
* @retval None
*/
uint16_t WMBus_AES_Encrypt_CBC(uint8_t *payload, uint16_t size, uint8_t *key, uint8_t *enc_payload, uint8_t *iv)
{
  
  AES128_CBC_encrypt(enc_payload, payload, size, key, iv);
   
  if(size%16==0)
    return size;
  
  return size+(16-(size%16));
}

/**
* @brief  This routine decrypts a payload buffer returning the decrypted version on another buffer.
* @param  payload: the buffer to decrypt.
* @param  size: the buffer size.
* @param  key: the key to be used for encryption (16 bytes).
* @param  dec_payload: the destination buffer.
* @param  iv: the initialization vector.
* @retval None
*/
uint16_t WMBus_AES_Decrypt_CBC(uint8_t *payload, uint16_t size, uint8_t *key, uint8_t *dec_payload, uint8_t *iv)
{
  
  AES128_CBC_decrypt(dec_payload, payload, size, key, iv);
  
  if(size%16==0)
    return size;
  
  return size+(16-(size%16));
}

/**
*@}
*/

/**
*@}
*/



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
