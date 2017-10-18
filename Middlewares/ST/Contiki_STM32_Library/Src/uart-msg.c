/**
******************************************************************************
* @file    uart-msg.c
* @author  System LAB
* @version V1.0.0
* @date    17-June-2015
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
#include "contiki.h"
#include "dev/leds.h"

/**
 * @defgroup slip
 * @ingroup STM32_Contiki_Library
 * @{
 */

/**
 * @addtogroup slip
 * @ingroup STM32_Contiki_Library
 * @{
 * @file Implementation of slip functions for stm32 platform
 */

#ifdef USE_STM32L1XX_NUCLEO
#include "stm32l1xx_nucleo.h"
#include "stm32l1xx_hal.h"
#include "hw-config.h"
#endif
#ifdef USE_STM32F4XX_NUCLEO
#include "stm32f4xx_nucleo.h"
#include "stm32f4xx_hal.h"
#include "main.h"
#endif
#include "platform-conf.h"
#include <stdio.h>
#include "dev/slip.h"
#include "st-lib.h"
/*---------------------------------------------------------------------------*/
void uart_send_msg(unsigned char *);
extern st_lib_uart_handle_typedef st_lib_uart_handle;
/*---------------------------------------------------------------------------*/
unsigned char databyte[1] = {0};
/*---------------------------------------------------------------------------*/
/**
* @brief  Rx Transfer completed callbacks.
* @param  huart: Pointer to a st_lib_uart_handle_typedef structure that contains
*                the configuration information for the specified UART module.
* @retval None
*/
#ifndef USE_X_CUBE_IDW01M1
void st_lib_hal_uart_rx_cplt_callback(st_lib_uart_handle_typedef *huart)
{   
  slip_input_byte(databyte[0]);
  st_lib_hal_uart_receive_it(&st_lib_uart_handle, databyte, 1);
}
#endif
/*---------------------------------------------------------------------------*/
void
uart1_set_input(int (*input) (unsigned char c))
{
  st_lib_hal_uart_receive_it(&st_lib_uart_handle, databyte, 1);
}
/*--------------------------------------------------------------------------*/

/**
 * @brief  slip_arch_init
 * 		initialises slip device
 * @param  unsigned long baudrate
 * @retval none
 */
void
slip_arch_init(unsigned long ubr)
{
  st_lib_hal_uart_enable_it(&st_lib_uart_handle, UART_IT_RXNE);
  //uart1_set_input(slip_input_byte);
}
/*--------------------------------------------------------------------------*/

/**
 * @brief  slip_arch_writeb
 * 		writes a byte to the slip
 * @param  unsigned char c
 * @retval none
 */
void
slip_arch_writeb(unsigned char c)
{
  uart_send_msg(&c);
}
/*--------------------------------------------------------------------------*/

/**
  * @brief  Send a message via UART
  * @param  msg the pointer to the message to be sent
  * @retval None
  */
void uart_send_msg(unsigned char *msg)
{
  st_lib_hal_uart_transmit(&st_lib_uart_handle, (uint8_t*)msg, 1, 5000);
}
/*--------------------------------------------------------------------------*/
/** @} */
/** @} */
