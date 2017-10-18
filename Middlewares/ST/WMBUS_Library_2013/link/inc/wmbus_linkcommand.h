/**
* @file    wmbus_linkcommand.h
* @author  System Lab - NOIDA/VMA division - AMS
* @version V2.4.2
* @date    1-Mar-2016
* @brief   This file contains function headers for LINK LAYER commands
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
#ifndef __WMBUS_LINKCOMMAND_H
#define __WMBUS_LINKCOMMAND_H

/* Includes ------------------------------------------------------------------*/
#include "wmbus_phy.h"

/** @addtogroup WMBUS_Library
* @{
*/


/** @addtogroup WMBus_LinkLayer
*   @{
*/

/** @addtogroup WMBus_LinkCommand         WMBus LinkCommand
* @brief Configuration and management of WMBus Link layer Command.
* @details See the file <i>@ref wmbus_linkcommand.h</i> for more details.
* @{
*/



/** @defgroup WMBus_LinkCommand_Exported_Functions  WMBus LinkCommand Exported Functions
* @{
*/

/**
* @brief  This function will send Installation request 
*         from meter to concentrator.
* @param  *appliData:Application Data pointer
* @param  length: Message Length
* @param  ci_field: CI Filed.
* @retval Success/Error                     
*/
uint8_t WMBus_LinkSendInstallationRequest(uint8_t *appliData,
                                          uint8_t length,
                                          uint8_t ci_field);

/**
* @brief  This function will send No-Reply(Unsolicited) user data request from 
*         meter to concentrator.
* @param  *appliData:Application Data pointer
* @param   length: Message Length
* @param   ci_field: CI Filed.
* @retval  Success/Error                     
*/
uint8_t WMBus_LinkSendNoReplyApplicationData(uint8_t *appliData, 
                                             uint8_t length,
                                             uint8_t ci_field);

/**
* @brief  This function will send ACC-DMD from meter to concentrator.
* @param  *appliData:Application Data pointer
* @param   length: Message Length
* @param   ci_field: CI Filed.
* @retval  Success/Error                      
*/
uint8_t WMBus_LinkSendAccessDemand(uint8_t *appliData,
                                   uint8_t length,
                                   uint8_t ci_field);

/**
* @brief  This function will send ACC-NR from meter to concentrator.
* @param  *appliData:Application Data pointer
* @param   length: Message Length
* @param   ci_field: CI Filed.
* @retval  Success/Error                       
*/
uint8_t WMBus_LinkSendAccess_NoReply(uint8_t *appliData,
                                     uint8_t length,
                                     uint8_t ci_field);

/**
* @brief  This function will send RESP-UD from meter to concentrator.
* @param  *appliData:Application Data pointer
* @param   length: Message Length
* @param   ci_field: CI Filed.
* @retval  Success/Error                      
*/
uint8_t WMBus_LinkSendResponse_UD(uint8_t *appliData,
                                  uint8_t length,
                                  uint8_t ci_field);

/**
* @brief  This function will send Ack.
* @param  ci_field: CI Field of Frame 
* @retval Success/Error                    
*/
uint8_t WMBus_LinkSendAck(uint8_t *appliData,
                            uint8_t length,
                            uint8_t ci_field);

/**
* @brief  This function will send SND-NKE from concentrator to meter
* @param  ci_field: CI Field of Frame
* @retval Success/Error                      
*/
uint8_t WMBus_LinkSendResetRemoteLink(uint8_t *appliData,
                               uint8_t length,
                               uint8_t ci_field);

/**
* @brief  This function will send SND-UD from concentrator to meter
* @param  *appliData:Application Data pointer
* @param   length: Message Length
* @param   ci_field: CI Filed.
* @retval  Success/Error                      
*/
uint8_t WMBus_LinkSendUserDataCommand(uint8_t *appliData,
                                      uint8_t length,
                                      uint8_t ci_field);

/**
* @brief  This function will send SND-UD2 from concentrator to meter
* @param  *appliData:Application Data pointer
* @param   length: Message Length
* @param   ci_field: CI Filed.
* @retval  Success/Error                       
*/
uint8_t WMBus_LinkSendUserData2Command(uint8_t *appliData,
                                       uint8_t length,
                                       uint8_t ci_field);


/**
* @brief  This function will send REQ-UD1 from concentrator to meter
* @param  *appliData:Application Data pointer
* @param   length: Message Length
* @param   ci_field: CI Filed.
* @retval  Success/Error                   
*/
uint8_t WMBus_LinkRequestUserData1(uint8_t *appliData,
                                   uint8_t length,
                                   uint8_t ci_field);

/**
* @brief  This function will send REQ-UD2 from concentrator to meter
* @param  *appliData:Application Data pointer
* @param   length: Message Length
* @param   ci_field: CI Filed.
* @retval  Success/Error                   
*/
uint8_t WMBus_LinkRequestUserData2(uint8_t *appliData,
                                   uint8_t length,
                                   uint8_t ci_field);

/**
* @brief  This function will send CNF-IR from concentrator to meter
* @param  *appliData:Application Data pointer
* @param   length: Message Length
* @param   ci_field: CI Filed.
* @retval  Success/Error                     
*/
uint8_t WMBus_LinkSendConfirmInstallationRequest(uint8_t *appliData,
                                                 uint8_t length,
                                                 uint8_t ci_field);

/**
* @brief  Set the FCV bit for the next frame.
* @note This bit is used only for frames from primary stations.
* @param  fcv: FDV bit, 1 or 0.
* @retval None
*/
void WMBus_LinkSetFcv(uint8_t fcv);

/**
* @brief  Set the FCB bit for the next frame.
* @note This bit is used only for frames from primary stations.
* @param  fcb: FDB bit, 1 or 0.
* @retval None
*/
void WMBus_LinkSetFcb(uint8_t fcb);

/**
* @brief  Set the ACD (access demand) bit for the next frame.
* @note This bit is used only for frames from secondary stations.
* @param  acd: ACD bit, 1 or 0.
* @retval None
*/
void WMBus_LinkSetAcd(uint8_t acd);

/**
* @brief  Set the DFC (data flow control) bit for the next frame.
* @note This bit is used only for frames from secondary stations.
* @param  dfc: DFC bit, 1 or 0.
* @retval None
*/
void WMBus_LinkSetDfc(uint8_t dfc);


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

#endif/* __WMBUS_LINKCOMMAND_H*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
