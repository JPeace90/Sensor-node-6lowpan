/**
******************************************************************************
* @file    contiki-spirit1-main.c
* @author  System LAB
* @version V1.0.0
* @date    17-June-2015
* @brief   Contiki main file for stm32nucleo-spirit1 platform
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

/**
 * @defgroup STM32_Contiki_Library
 * @{
 */

/**
 * @addtogroup STM32_Contiki_Library
 * @{
 */
/*---------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "contiki.h"
#include "contiki-net.h"
#include "sys/autostart.h"
#include "dev/leds.h"
#include "dev/slip.h"
#include "dev/watchdog.h"
#include "lib/random.h"
#include "net/netstack.h"
#include "net/ip/uip.h"
#include "net/mac/frame802154.h"
#include "SPIRIT_Config.h"
#include "SPIRIT_Management.h"
#include "spirit1.h"
#include "spirit1-arch.h"
#include "node-id.h"
#include "stdbool.h"
#include "dev/button-sensor.h"
#include "dev/radio-sensor.h"

#ifdef WITH_IP64
#include "ip64.h"
#include "ip64-addr.h"
#endif

#ifdef USE_STM32L1XX_NUCLEO
#include "stm32l1xx.h"
#include "hw-config.h" 
#endif

#ifdef USE_STM32F4XX_NUCLEO
#include "stm32f4xx.h"
#endif
/*---------------------------------------------------------------------------*/
#if NETSTACK_CONF_WITH_IPV6
#include "net/ipv6/uip-ds6.h"
#endif /*NETSTACK_CONF_WITH_IPV6*/
/*---------------------------------------------------------------------------*/
#if COMPILE_SENSORS //X_NUCLEO_IKS01Ax
extern const struct sensors_sensor temperature_sensor;
extern const struct sensors_sensor humidity_sensor;
extern const struct sensors_sensor pressure_sensor;
extern const struct sensors_sensor magneto_sensor;
extern const struct sensors_sensor acceleration_sensor;
extern const struct sensors_sensor gyroscope_sensor;
SENSORS(&button_sensor,
        &radio_sensor,
        &temperature_sensor,
        &humidity_sensor,
	&pressure_sensor,
	&magneto_sensor,
        &acceleration_sensor,
	&gyroscope_sensor);

#elif X_NUCLEO_6180XA1
#include "dev/presence-sensor.h"
extern const struct sensors_sensor presence_sensor;
SENSORS(&button_sensor,
        &radio_sensor,
		&presence_sensor);

#else //!COMPILE_SENSORS && !X_NUCLEO_6180XA1
SENSORS(&button_sensor,
        &radio_sensor);
#endif
/*---------------------------------------------------------------------------*/
extern unsigned char node_mac[8];
/*---------------------------------------------------------------------------*/

#undef DEBUG
#define DEBUG 0

#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */  
/*---------------------------------------------------------------------------*/
#if NETSTACK_CONF_WITH_IPV6
PROCINIT(&etimer_process, &tcpip_process);
#else /*NETSTACK_CONF_WITH_IPV6*/
PROCINIT(&etimer_process);
#warning "No TCP/IP process!"
#endif /*NETSTACK_CONF_WITH_IPV6*/
/*---------------------------------------------------------------------------*/
static void set_rime_addr(void);
void Stack_6LoWPAN_Init(void);
static void print_parameters(void);
/*---------------------------------------------------------------------------*/

/**
 * @brief  Stack_6LoWPAN_Init program
 * 		initialises Contiki structures, the SPIRIT1 and runs all the PROCESSes
 * @param  None
 * @retval None
 */
void Stack_6LoWPAN_Init(void)
{

  /* Initialize Contiki and our processes. */
  clock_init();
  ctimer_init();
  rtimer_init();
  watchdog_init();

  process_init();
  process_start(&etimer_process, NULL);
  
  /* Restore node id if such has been stored in external mem */
  node_id_restore(); /* also configures node_mac[] */

  random_init(node_id);

  set_rime_addr();

  netstack_init();

  spirit_radio_driver.on();

  energest_init();

    
#if NETSTACK_CONF_WITH_IPV6
  memcpy(&uip_lladdr.addr, node_mac, sizeof(uip_lladdr.addr));
  
  queuebuf_init();
  process_start(&tcpip_process, NULL);

  uip_ipaddr_t ipaddr;
  uip_ip6addr(&ipaddr, 0xfe80, 0, 0, 0, 0, 0, 0, 0);
  uip_ds6_set_addr_iid(&ipaddr, &uip_lladdr);
  uip_ds6_addr_add(&ipaddr, 0, ADDR_AUTOCONF);  
#endif /* NETSTACK_CONF_WITH_IPV6*/

  print_parameters();

  PRINTF("Contiki and SPIRIT1 correctly configured... Starting all processes\n");

  process_start(&sensors_process, NULL);

  autostart_start(autostart_processes);

#if WITH_IP64
  uip_ip4addr_t ipv4addr, netmask, ip4addr;
  uip_ip6addr_t ip6addr;

  uip_ipaddr(&ipv4addr, 192, 168, 0, 1);
  uip_ipaddr(&netmask, 255, 255, 255, 0);
  ip64_set_ipv4_address(&ipv4addr, &netmask);
/*  printf("IPv4 address %d.%d.%d.%d\n",
  	   ipv4addr.u8[0], ipv4addr.u8[1],
  	   ipv4addr.u8[2], ipv4addr.u8[3]);
*/
  uip_ipaddr(&ip4addr, 8,8,8,8);
  ip64_addr_4to6(&ip4addr, &ip6addr);
  uip_nameserver_update((uip_ipaddr_t *)&ip6addr, UIP_NAMESERVER_INFINITE_LIFETIME);
#endif

  watchdog_start();

}
/*---------------------------------------------------------------------------*/
static void set_rime_addr(void)
{
  linkaddr_t addr;

  memset(&addr, 0, sizeof(linkaddr_t));
  memcpy(addr.u8, node_mac, sizeof(addr.u8));

  linkaddr_set_node_addr(&addr);
}
/*---------------------------------------------------------------------------*/
static void print_parameters(void)
{
#include "rpl-conf.h"

/* A selected set of parameteres to check the firmware configuration.        */
/* To print float parameters use PRINT_PARAMETER_STR macro                   */
printf("Platform and Contiki parameters:\n");
#ifdef USE_STM32L1XX_NUCLEO
  PRINT_PARAMETER(USE_STM32L1XX_NUCLEO, "%d");
#endif
#ifdef USE_STM32F4XX_NUCLEO
  PRINT_PARAMETER(USE_STM32F4XX_NUCLEO, "%d");
#endif

#ifdef X_NUCLEO_IDS01A4
  PRINT_PARAMETER(X_NUCLEO_IDS01A4, "%d");
#endif
#ifdef X_NUCLEO_IDS01A5
  PRINT_PARAMETER(X_NUCLEO_IDS01A5, "%d");
#endif

#ifdef COMPILE_SENSORS
  PRINT_PARAMETER(COMPILE_SENSORS, "%d");
#endif
#ifdef USE_IKS01A1
  PRINT_PARAMETER(USE_IKS01A1, "%d");
#endif
#ifdef USE_IKS01A2
  PRINT_PARAMETER(USE_IKS01A2, "%d");
#endif

#ifdef X_NUCLEO_6180XA1
  PRINT_PARAMETER(X_NUCLEO_6180XA1, "%d");
#endif

#ifdef USE_X_CUBE_IDW01M1
  PRINT_PARAMETER(USE_X_CUBE_IDW01M1, "%d");
#endif


  printf("\n");
  PRINT_PARAMETER_STR(RSSI_RX_THRESHOLD);
  PRINT_PARAMETER_STR(RSSI_TX_THRESHOLD);
  PRINT_PARAMETER_STR(POWER_DBM);
  PRINT_PARAMETER_STR(CHANNEL_SPACE);
  PRINT_PARAMETER_STR(FREQ_DEVIATION);
  PRINT_PARAMETER_STR(BANDWIDTH);
  PRINT_PARAMETER_STR(MODULATION_SELECT);
  PRINT_PARAMETER(DATARATE, "%d");
  PRINT_PARAMETER(IEEE802154_CONF_PANID, "%x");
  PRINT_PARAMETER_STR(BASE_FREQUENCY);
  PRINT_PARAMETER(CHANNEL_NUMBER, "%d");
  PRINT_PARAMETER(NULLRDC_CONF_802154_AUTOACK, "%d");
  PRINT_PARAMETER(SICSLOWPAN_CONF_MAC_MAX_PAYLOAD, "%d");

  printf("\n");
  PRINT_PARAMETER(UIP_CONF_BUFFER_SIZE, "%d");
  PRINT_PARAMETER(UIP_CONF_ROUTER, "%d");
  PRINT_PARAMETER(UIP_CONF_IPV6_RPL, "%d");
  PRINT_PARAMETER(RPL_LEAF_ONLY, "%d");
  PRINT_PARAMETER(QUEUEBUF_CONF_NUM, "%d");
  PRINT_PARAMETER(UIP_CONF_ND6_REACHABLE_TIME, "%d");
  PRINT_PARAMETER(UIP_CONF_IP_FORWARD, "%d");
  PRINT_PARAMETER(UIP_TCP_MSS, "%d");
  PRINT_PARAMETER(UIP_RECEIVE_WINDOW, "%d");
  PRINT_PARAMETER(UIP_CONF_TCP, "%d");
  PRINT_PARAMETER(UIP_CONF_MAX_ROUTES, "%d");
  PRINT_PARAMETER(NBR_TABLE_CONF_MAX_NEIGHBORS, "%d");
  PRINT_PARAMETER(UIP_CONF_ND6_SEND_RA, "%d");
  PRINT_PARAMETER(UIP_CONF_ND6_SEND_NA, "%d");
  PRINT_PARAMETER(UIP_CONF_ND6_SEND_NS, "%d");
#ifdef WITH_IP64
  PRINT_PARAMETER(WITH_IP64, "%d");
#else
  printf("IP64 is disabled.\n");
#endif

#ifdef REST
 #if REST == coap_rest_implementation
#include "er-coap.h"

  printf("\n");
  PRINT_PARAMETER(REST_MAX_CHUNK_SIZE, "%d");
  PRINT_PARAMETER(COAP_MAX_HEADER_SIZE, "%d");
  PRINT_PARAMETER(COAP_MAX_BLOCK_SIZE, "%d");
  PRINT_PARAMETER(COAP_MAX_PACKET_SIZE, "%d");
  PRINT_PARAMETER(COAP_LINK_FORMAT_FILTERING,  "%d");
  PRINT_PARAMETER(COAP_PROXY_OPTION_PROCESSING,  "%d");
  PRINT_PARAMETER(COAP_MAX_OPEN_TRANSACTIONS,  "%d");
  PRINT_PARAMETER(COAP_MAX_OBSERVERS,  "%d");
  #ifdef COAP_OBSERVE_CLIENT
#include "er-coap-observe-client.h"
  printf("COAP_OBSERVE_CLIENT is enabled.\n");
  PRINT_PARAMETER(COAP_MAX_OBSERVEES,  "%d");
  #else /*!COAP_OBSERVE_CLIENT*/
  printf("COAP_OBSERVE_CLIENT is disabled.\n");
  #endif /*#ifdef COAP_OBSERVE_CLIENT*/
  PRINT_PARAMETER(COAP_OBSERVE_REFRESH_INTERVAL, "%d");
 #endif /*#if REST == coap_rest_implementation*/
#endif /*#ifdef REST*/

  printf("\n");
}
/*---------------------------------------------------------------------------*/
/** @} */

/** @} */
