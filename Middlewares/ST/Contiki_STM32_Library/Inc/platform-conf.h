/**
******************************************************************************
* @file    platform/stm32nucleo-spirit1/platform-conf.h
* @author  System LAB 
* @version V1.0.0
* @date    17-May-2015
* @brief   Configuration parameters
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
/**
 * @addtogroup configuration_files
 * @ingroup STM32_Contiki_Library
 * @{
 * @file Platform specific configuration file for Contiki
 */

/*---------------------------------------------------------------------------*/
#ifndef __PLATFORM_CONF_H__
#define __PLATFORM_CONF_H__
/*---------------------------------------------------------------------------*/
#include <inttypes.h>
#include <string.h>
/*---------------------------------------------------------------------------*/
/*This is needed if we want to stringize the result of expansion
 * of a macro argument (i.e. we need two levels) */
#define xstr(s) str(s)
/*---------------------------------------------------------------------------*/
#define str(x) #x
/*---------------------------------------------------------------------------*/
#define PRINT_PARAMETER(PARAM, format)  do{\
	printf(#PARAM ":\t" format "\n", PARAM);\
}while(0)
/*---------------------------------------------------------------------------*/
#define PRINT_PARAMETER_STR(PARAM)  do{\
	printf(#PARAM ":\t" str(PARAM) "\n");\
}while(0)
/*---------------------------------------------------------------------------*/
#define PLATFORM_HAS_LEDS 1
#define PLATFORM_HAS_BUTTON 1
#define PLATFORM_HAS_RADIO 1

#undef LEDS_GREEN
#undef LEDS_RED
#undef LEDS_BLUE
#undef LEDS_YELLOW

#define LEDS_GREEN  1 /*Nucleo LED*/
#define LEDS_RED    2 /*SPIRIT1 LED*/
#define LEDS_BLUE   4 /*Not used*/
#define LEDS_YELLOW 8 /*Not used*/

#if COMPILE_SENSORS
#define LEDS_CONF_ALL LEDS_GREEN /* SPIRIT1 LED is not available */
#else
#define LEDS_CONF_ALL LEDS_GREEN + LEDS_RED /* SPIRIT1 LED is available */
#endif /*COMPILE_SENSORS*/

#define UART1_CONF_TX_WITH_INTERRUPT        0
#define WITH_SERIAL_LINE_INPUT              1
#define TELNETD_CONF_NUMLINES               6
#define NETSTACK_CONF_RADIO                 spirit_radio_driver
#define NETSTACK_RADIO_MAX_PAYLOAD_LEN      96 /* spirit1-config.h */

/*---------------------------------------------------------------------------*/
/* define ticks/second for slow and fast clocks. Notice that these should be a
  power of two, eg 64,128,256,512 etc, for efficiency as POT's can be optimized
  well. */
#define CLOCK_CONF_SECOND             1000
#define RELOAD_VALUE        ((F_CPU/CLOCK_CONF_SECOND) - 1)
/* One tick: 1 ms */

#if WITH_IP64
#include "ip64-conf.h"
#define WITH_SLIP 1
#ifndef UIP_FALLBACK_INTERFACE
#define UIP_FALLBACK_INTERFACE ip64_uip_fallback_interface
#endif
#endif /* WITH_IP64 */

#define RTIMER_CLOCK_DIFF(a,b)     ((signed short)((a)-(b))) //MGR from new Contiki
/*---------------------------------------------------------------------------*/
typedef unsigned long clock_time_t;
typedef unsigned long long rtimer_clock_t;
/*---------------------------------------------------------------------------*/
#define CC_CONF_REGISTER_ARGS          0
#define CC_CONF_FUNCTION_POINTER_ARGS  1
#define CC_CONF_FASTCALL
#define CC_CONF_VA_ARGS                1
#define CC_CONF_INLINE                 inline

#define CCIF
#define CLIF
/*---------------------------------------------------------------------------*/
#ifndef __ARCHDEP__TYPES
#define __ARCHDEP__TYPES
typedef uint8_t          u8_t;
typedef uint16_t        u16_t;
typedef uint32_t        u32_t;
typedef int8_t           i8_t;
typedef int16_t         i16_t;
typedef int32_t         i32_t;
typedef i8_t             s8_t;
typedef i16_t           s16_t;
typedef i32_t           s32_t;
#endif /*__ARCHDEP__TYPES*/
/*---------------------------------------------------------------------------*/
typedef unsigned short  uip_stats_t;
/*---------------------------------------------------------------------------*/
#define MULTICHAN_CONF_SET_CHANNEL(x)
#define MULTICHAN_CONF_READ_RSSI(x) 0

#ifdef USE_STM32L1XX_NUCLEO
/*---------------------------------------------------------------------------*/
#define F_CPU                   32000000ul
#define RTIMER_ARCH_SECOND      32768
#define PRESCALER       ((F_CPU / (RTIMER_ARCH_SECOND*2)))

/*---------------------------------------------------------------------------*/
#endif//USE_STM32L1XX_NUCLEO

#ifdef USE_STM32F4XX_NUCLEO
/*---------------------------------------------------------------------------*/
#define F_CPU                   84000000ul
#define RTIMER_ARCH_SECOND      96000

/*---------------------------------------------------------------------------*/
#endif//USE_STM32F4XX_NUCLEO

#endif /* __PLATFORM_CONF_H__ */
/*---------------------------------------------------------------------------*/
/** @} */
