/**
* @file    wmbus_phy.h
* @author  VMA division - AMS/System Lab - NOIDA
* @version V2.4.2
* @date    1-Mar-2016
* @brief   This file contains routines for PHYSICAL LAYER
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
#ifndef __WMBUS_PHY_H
#define __WMBUS_PHY_H
/* Includes ------------------------------------------------------------------*/
#include "SPIRIT_Config.h"
#include <string.h>  

/** @addtogroup WMBUS_Library
 * @{
 */


/** @addtogroup WMBus_PhyLayer      wM-Bus Physical Layer
* @brief Configuration and management of WMBus Physical layer
* @{
*/

/** @addtogroup WMBus_Phy         WMBus Phy
* @brief Configuration and management of WMBus Phy layer.
* @details See the file <i>@ref wmbus_phy.h</i> for more details.
* @{
*/

/** @defgroup WMBus_Phy_Exported_Types           WMBus Phy Exported Types
* @{
*/

/**
* @brief  WMBus Modes typedef enum for WMBus Phy layer
*/
typedef enum {
  S1_MODE = 0x00,/*!<Transmit only meter for stationary receiving readout */
  S1m_MODE,/*!<Transmit only meter for mobile or stationary readout*/
  S2_MODE,/*!<All meter types. Stationary reading*/
  T1_MODE,/*!<Frequent transmission (short frame meters)*/
  T2_MODE,/*!<Frequent transmission (short frame meter with two way capability)*/
  R2_MODE,/*!<Frequent reception (long range)*/
  ALL_MODE,/*!<Multi-mode option */
  N1_MODE,/*!<Long range transmit for stationary readout*/
  N2_MODE,/*!<Long range two-way communication for stationary readout*/ 
  F2_MODE,/*!<Long range two-way communication for stationary readout*/
  F2m_MODE,/*!<Long range two-way communication */
  C1_MODE,/*!<Frequent transmit only meter for mobile or stationary readout*/
  C2_MODE,/*!<Frequent transmit meter for mobile or stationary readout*/
  INVALID_MODE/*!<Invalid Mode*/
}WMBusMode_t;

/**
* @brief  WMBus Channel typedef enum for WMBus Phy layer
*/
typedef enum{
  CHANNEL_1 = (uint8_t)0x0,/*!<Support for Channel 1*/
  CHANNEL_2,/*!<Support for Channel 2*/
  CHANNEL_3,/*!<Support for Channel 3*/
  CHANNEL_4,/*!<Support for Channel 4*/
  CHANNEL_5,/*!<Support for Channel 5*/
  CHANNEL_6,/*!<Support for Channel 6*/
  CHANNEL_7,/*!<Support for Channel 7*/
  CHANNEL_8,/*!<Support for Channel 8*/
  CHANNEL_9,/*!<Support for Channel 9*/             
  CHANNEL_10,/*!<Support for Channel 10*/
  CHANNEL_1a=0,/*!<Support for Channel 1a*/
  CHANNEL_1b,/*!<Support for Channel 1b*/
  CHANNEL_2a,/*!<Support for Channel 2a*/
  CHANNEL_2b,/*!<Support for Channel 2b*/
  CHANNEL_3a,/*!<Support for Channel 3a*/
  CHANNEL_3b,/*!<Support for Channel 3b*/
  Invalid_Channel/*!<Invalid channel*/
}WMBusChannel_t;

/**
* @brief  WMBus Device type typedef enum for WMBus Phy layer
*/
typedef enum {
  OTHER = 0x00,/*!<Device Type is Other/Concentrator*/
  METER = 0x01,/*!<Device Type is Meter*/
  ROUTER = 0x02,/*!<Device Type is Router*/
  SNIFFER = 0x03,/*!<Device Type is Sniffer*/ 
  NOT_CONFIGURED = 0xFF/*!<Device Type not configured*/
}WMBusDeviceType_t;

/**
* @brief  WMBus Frame Format typedef enum for WMBus Phy layer
*/
typedef enum
{
  FRAME_FORMAT_A  =(uint8_t)0x00,/*!<Indicates Frame Format A*/ 
  FRAME_FORMAT_B,/*!<Indicates Frame Format B*/ 
  FRAME_FORMAT_PRESET
}FrameFormatType_t;

/**
* @brief  WMBus Phy state typedef enum for WMBus Phy layer
*/
typedef enum {
  PHY_STATE_READY=0x00,/*!<PHY radio ready state*/ 
  PHY_STATE_TX,/*!<PHY radio tx state*/ 
  PHY_STATE_RX,/*!<PHY radio rx state*/ 
  PHY_STATE_SHUTDOWN,/*!<PHY radio shutdown state*/
  PHY_STATE_STANDBY,/*!<PHY radio standby state*/
  PHY_STATE_INVALID/*!<PHY radio state invalid*/
}WMBusPhyState_t; 

/**
* @brief  WMBus Phy Attribute typedef enum for WMBus Phy layer
*/
typedef enum {
  WMBUS_PHY_MODE =0x00,/*!<PHY Device Operation Mode*/
  WMBUS_PHY_DEVICE_TYPE,/*!<Device Type*/
  WMBUS_PHY_CHANNEL,/*!< For R2 only, otherwise it is 0*/
  WMBUS_PHY_RESPONSE_TIME_MIN,/*!<PHY minimum response time*/
  WMBUS_PHY_RESPONSE_TIME_MAX,/*!<PHY maximum response time*/
  WMBUS_PHY_RESPONSE_TIME_TYP,/*!<PHY typical response time*/
  WMBUS_PHY_FAC_TIME_DELAY,/*!<FAC time delay*/ 
  WMBUS_PHY_FAC_TIMEOUT,/*!<FAC timeout*/
  WMBUS_PHY_NOMINAL_TIME,/*!<Nomianl Time*/
  WMBUS_PHY_PREAMBLE_LEN,/*!<Preamble length*/ 
  WMBUS_PHY_POSTAMBLE_LEN,/*!<Postable length*/
  WMBUS_PHY_OP_POWER,/*!<Operating Power*/
  WMBUS_PHY_RX_RSSI_THRESHOLD,/*!<RSSI threshold for Rx */
  WMBUS_PHY_TX_INTERVAL,/*!<Transmission interval*/
  WMBUS_PHY_RX_TIMEOUT, /*<RX period to seek the SYNC*/
  WMBUS_PHY_DIR,/*!<Direction of Communication*/  
  WMBUS_PHY_RF_OFFSET,/*!<RF offset, used to compensate the XTAL offset*/
  WMBUS_PHY_CUST_DATARATE,/*!<Specify a datarate from the appli level*/
  WMBUS_PHY_CSMA_ENABLED,/*!<CSMA enabled*/
  WMBUS_PHY_CSMA_RSSI_THRESHOLD,/*!<RSSI threshold for CSMA*/
  WMBUS_PHY_CSMA_OVERRIDE_FAIL,/*!<CSMA override fail*/
  WMBUS_PHY_CSMA_CCA_PERIOD,/*!<CSMA time for RSSI measurement  (ref. to SPIRIT1 datasheet)*/
  WMBUS_PHY_CSMA_CCA_LENGTH,/*!<CSMA length for RSSI measurement (ref. to SPIRIT1 datasheet)*/
  WMBUS_PHY_CSMA_MAX_BO,/*!<CSMA max backoff (ref. to SPIRIT1 datasheet)*/
  WMBUS_PHY_CSMA_BU_SEED,/*!<CSMA max backoff (ref. to SPIRIT1 datasheet)*/
  WMBUS_PHY_CSMA_BU_PRESCALER,/*!<CSMA max backoff (ref. to SPIRIT1 datasheet)*/
}WMBUS_PHY_ATTR_t;


/**
* @brief  PHY_STATUS enum for WMBus Phy layer
*/
enum
{
  PHY_STATUS_SUCCESS = 0x00,/*!<Indicates PHY Radio success */  
  PHY_STATUS_ERROR,/*!<Indicates PHY Radio error */                   
  PHY_STATUS_ERROR_TIMEOUT,/*!<Indicates PHY  timeout error*/           
  PHY_STATUS_ERROR_INVALID_DEVICE_TYPE,/*!<PHY error for Unknown Device type*/
  PHY_STATUS_ERROR_INVALID_ADDRESS, /*!<PHY error for Invalid device Address*/
  PHY_STATUS_ERROR_INVALID_VALUE,/*!<PHY error for invalid value*/
  PHY_STATUS_ERROR_INVALID_STATE,/*!<PHY error for invalid state*/
  PHY_STATUS_ERROR_INVALID_LENGTH,/*!<PHY error for invalid length*/
  PHY_STATUS_ERROR_NOTHING_RECEIVED,/*!<PHY error nothing received*/
  PHY_STATUS_ERROR_DECODING,/*!<PHY error in decoding*/
  PHY_STATUS_ERROR_XTAL_TIMEOUT,/*!<PHY error crystal timeout occured*/
  PHY_STATUS_ERROR_TX_TIMEOUT,/*!<PHY error for transmission timeout*/
  PHY_STATUS_ERROR_RX_INVALID_LENGTH,/*!<PHY error for received invalid length*/
  PHY_STATUS_ERROR_RX_PACKET_INCOMPLETE,/*!<PHY error for received incomplete packet*/
  PHY_STATUS_ERROR_RX_INVALID_WMBUS_MODE,/*!<PHY error for invalid WMBus mode*/
  PHY_STATUS_INVALID_ATTR/*!<Invalid attribute value*/     
};

/**
* @}
*/

/** @defgroup WMBus_Phy_Exported_Constants        WMBus Phy Exported Constants
* @{
*/



/**
* @}
*/

/** @defgroup WMBus_Phy_Exported_Macros           WMBus Phy Exported Macros
* @{
*/

#define PHY_STATUS              uint8_t
#define  L_MIN(a,b)      ((a>b)?b:a)
#define  L_MAX(a,b)      ((a>b)?a:b)


/**
* @brief  This macro performs the computation of the RSSI threshold over N samples.
* @param  N number of samples to be used.
*/
#define WMBUS_PHY_COMPUTE_RSSI_THR(N)           {int32_t rssi=0;\
                                                  for(uint32_t i=0;i<10;i++){\
                                                    rssi+=(int32_t)WMBus_PhyGetIdleRssi();}\
                                                  WMBus_PhySetAttr(WMBUS_PHY_RX_RSSI_THRESHOLD, rssi/10+10);}
/**
* @}
*/

/** @defgroup WMBus_Phy_Exported_Functions        WMBus Phy Exported Functions
* @{
*/

void WMBus_PhyDeviceCmd(uint8_t en);
uint8_t* GetPhyBuffer(void);

/**
* @brief  This function handles Transmit and Receive
*         interrupt request from the Transceiver.
* @param  None
* @retval None
*/
void WMBus_PhyInterruptHandler(void);



/**
* @brief  This function will configure the SPIRIT Radio registers.This will \
*         abort the current TX and Rx transactions.
* @param  None.
* @retval PHY_STATUS.
*/
PHY_STATUS WMBus_PhyInit(WMBusMode_t devMode, WMBusDeviceType_t devType);


/**
* @brief  This function will return the current PHY state.
* @param  *phyState: The pointer to WMBusPhyState_t type primitive.
* @retval PHY_STATUS_SUCCESS or PHY_STATUS_ERROR_INVALID_STATE 
*              if the state is a transition one.
*/
PHY_STATUS  WMBus_PhyGetState (WMBusPhyState_t *phyState);

/**
* @brief  This function will set the current PHY state.
* @param  WMBusPhyState_t phyState: The phy state.
* @retval PHY_STATUS: PHY_STATUS_SUCCESS
*/
PHY_STATUS  WMBus_PhySetState(WMBusPhyState_t phyState);

/**
* @brief  This function gets the RSSI when the radio is not receiving any packet.
* @retval RSSI value in dBm. Value 0 is error, meaning that RSSI can't be measured.
*/
int32_t WMBus_PhyGetIdleRssi(void);

/**
* @brief  This function will transmit the buffer.
* @param  *buff: The pointer to the buffer to be transmitted.
* @param  length: The length of the data buffer.
* @param  void(*TxDataSentStateHandler)(uint8_t): This callback function is 
*            invoked after successful transmission.
* @retval PHY_STATUS.
*                       
*/
PHY_STATUS  WMBus_PhyTxDataHandleMode(uint8_t *buff,
                                      uint16_t length,
                                      void(*TxDataSentStateHandler)(uint8_t));

/**
* @brief  This Routine will set the WMBus PHY attributes.
* @param  attr:The WMBus attribute
* @param  ParamVal: The value of the attribute.
* @retval PHY_STATUS: The status of execution.
*/
PHY_STATUS WMBus_PhySetAttr(WMBUS_PHY_ATTR_t attr, int32_t ParamVal);

/**
* @brief  This Routine will return the WMBus PHY attributes.
* @param  attr: The WMBus attribute
*        *ParamVal: The pointer to the variable to set the attribute value
* @retval PHY_STATUS: The status of execution
*/
PHY_STATUS WMBus_PhyGetAttr(WMBUS_PHY_ATTR_t attr, int32_t *ParamVal);


/**
* @brief  This Routine will Check wheather the communication is bidirectional.
* @param  None
* @retval Returns 1 Bidirectional communication ,Otherwise 0.
*/
uint8_t WMBus_PhyIsTwoWayMode(void);

/**
* @brief  This Routine will return the WMBus PHY attributes.
* @param  None.
* @retval Returns the Device Type.
*/
WMBusDeviceType_t WMBus_PhyGetDevType(void);

/**
* @brief  This Routine will return minimum Response time in MicroSecond.
* @param  None.
* @retval Returns Response Time.
*/
uint32_t WMBus_PhyGetResponseTimeMin(void);

/**
* @brief  This Routine will return maximum Response time in MicroSecond.
* @param  None.
* @retval Returns Response Time.
*/
uint32_t WMBus_PhyGetResponseTimeMax(void);

/**
* @brief  This Routine will return typical Response time(Tro)in MicroSecond.
* @param  None.
* @retval Returns Response Time.
*/
uint32_t WMBus_PhyGetResponseTimeTyp(void);

/**
* @brief  This Routine will return FAC delay time(Txd)in MicroSecond.
* @param  None.
* @retval Returns FAC delay time.
*/
uint32_t WMBus_PhyGetFACDelay(void);

/**
* @brief  This Routine will return FAC Timeout time(Tto)in MicroSecond.
* @param  None.
* @retval Returns FAC timeout Time.
*/
uint32_t WMBus_PhyGetFACTimeout(void);

/**
* @brief  This Routine will return Nominal Time(Tnom)in MicroSecond.
* @param  None.
* @retval Returns Nominal Time.
*/
uint32_t WMBus_PhyGetNominalTime(void);

/**
* @brief  This Routine will return number of received packets.
* @param  None.
* @retval Returns the number of received packets.
*/
uint8_t WMBus_PhyGetNumRxPackets(void);

/**
* @brief  This Routine will Pop byte from Queue.
* @param  None.
* @retval Returns  the Byte.
*/
uint8_t WMBus_PhyPopBytefromQueue(void);

/**
* @brief  This Function will return Packet Length.
* @param  None.
* @retval Returns the Packet Length.
*/
uint16_t WMBus_PhyGetPacketLength(void);

/**
* @brief  This Function will return the RSSI Value.
* @param  None.
* @retval Returns the RSSI Value.
*/
int32_t WMBus_PhyGetPacketRssi(void);

/**
* @brief  This Function will return Packet Format.
* @param  None.
* @retval Returns the Packet Format.
*/
FrameFormatType_t WMBus_PhyGetPacketFormat(void);

/**
* @brief  This Function will return the received packet submode.
* @param  None.
* @retval Returns the Packet Format.
*/
WMBusMode_t WMBus_PhyGetRecvSubmode(void);

/**
* @brief  This Function will return Time Stamp.
* @param  None.
* @retval Returns the Time Stamp.
*/
uint32_t WMBus_PhyGetPacketRxTimestamp(void);

/**
* @brief  This Function will Perform Pop Operation from the Phy queue.
* @param  None.
* @retval None.
*/
void WMBus_PhyPopDesc(void);

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

#endif /* __WMBUS_PHY_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
