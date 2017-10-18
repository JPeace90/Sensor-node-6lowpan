/**
******************************************************************************
* @file    platform/stm32nucleo-spirit1/node-id.c
* @author  System LAB
* @version V1.0.0
* @date    17-June-2015
* @brief   Source file for node Id
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of STMicroelectronics nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
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
/*---------------------------------------------------------------------------*/
#include "node-id.h"
#include "contiki-conf.h"
#include <string.h>

/**
 * @addtogroup STM32_Contiki_Library
 * @{
 */

/*---------------------------------------------------------------------------*/
unsigned short node_id = 0;
unsigned char node_mac[8];
volatile uint32_t device_id[3];
/*---------------------------------------------------------------------------*/
#ifdef USE_STM32L1XX_NUCLEO
#define DEVICE_ID_REG0  (*((volatile uint32_t *) 0x1FF80050))
#define DEVICE_ID_REG1  (*((volatile uint32_t *) 0x1FF80054))
#define DEVICE_ID_REG2  (*((volatile uint32_t *) 0x1FF80064))
#endif

#ifdef USE_STM32F4XX_NUCLEO
#define DEVICE_ID_REG0  (*((volatile uint32_t *) 0x1FFF7A10))
#define DEVICE_ID_REG1  (*((volatile uint32_t *) 0x1FFF7A14))
#define DEVICE_ID_REG2	(*((volatile uint32_t *) 0x1FFF7A18))
#endif
/*---------------------------------------------------------------------------*/
/**
 * @brief  node_id_restore
 * 		restores Unique ID of the node
 * @param  None
 * @retval None
 */

void node_id_restore(void)
{
  device_id[0] = DEVICE_ID_REG0;
  device_id[1] = DEVICE_ID_REG1;
  device_id[2] = DEVICE_ID_REG2;
  
  (*(uint32_t*)node_mac) = DEVICE_ID_REG1;
  (*(((uint32_t*)node_mac)+1)) = DEVICE_ID_REG2;
  (*(((uint32_t*)node_mac)+1)) += DEVICE_ID_REG0;
  node_id = (unsigned short) DEVICE_ID_REG2;
}
/*---------------------------------------------------------------------------*/
/** @} */
