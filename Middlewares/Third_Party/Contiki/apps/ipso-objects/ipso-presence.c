/**
******************************************************************************
  * @file    ipso-presence.c
  * @author  Central LAB
  * @version V1.0.0
  * @date    20-June-2016
  * @brief   IPSO Presence Object
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
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
 * \addtogroup ipso-objects
 * @{
 */

/**
 * \file
 *         Implementation of OMA LWM2M / IPSO PRESENCE
 * \author
 *         Nicola Stefani
 */

#include <stdint.h>
#include "contiki.h"
#include "ipso-objects.h"
#include "lwm2m-object.h"
#include "lwm2m-engine.h"
#include "er-coap-engine.h"
#include "presence-sensor.h"
#include "leds.h"
/*---------------------------------------------------------------------------*/
#ifdef IPSO_PRESENCE
extern const struct ipso_objects_sensor IPSO_PRESENCE;
#endif /* IPSO_PRESENCE */
/*---------------------------------------------------------------------------*/
static int32_t last_state;
static int32_t counter = 0;
static int32_t btc = 0;
static int32_t ctb = 0;
/*---------------------------------------------------------------------------*/
#define PRESENCE_TIMER 1
/*---------------------------------------------------------------------------*/
static int
read_state(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  int32_t current_state;
  IPSO_PRESENCE.read_value(&current_state);

  if(current_state != last_state)
	  last_state = current_state;
  if(current_state == 1)
	  counter++;

  return ctx->writer->write_boolean(ctx, outbuf, outsize, current_state);
}
/*---------------------------------------------------------------------------*/
static int
reset_counter(lwm2m_context_t *ctx, const uint8_t *arg, size_t len,
              uint8_t *outbuf, size_t outlen)
{
  counter = 0;
  return 0;
}
/*---------------------------------------------------------------------------*/
static int
read_btc(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  return ctx->writer->write_int(ctx, outbuf, outsize, btc);
}
/*---------------------------------------------------------------------------*/
static int
set_btc(lwm2m_context_t *ctx, const uint8_t *inbuf, size_t insize,
           uint8_t *outbuf, size_t outsize)
{
  /* assume that this only read one TLV value */
  int32_t value;
  size_t len = ctx->reader->read_int(ctx, inbuf, insize, &value);

  btc = value;
  /* return the number of bytes read */
  return len;
}
/*---------------------------------------------------------------------------*/
static int
read_ctb(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  return ctx->writer->write_int(ctx, outbuf, outsize, ctb);
}
/*---------------------------------------------------------------------------*/
static int
set_ctb(lwm2m_context_t *ctx, const uint8_t *inbuf, size_t insize,
           uint8_t *outbuf, size_t outsize)
{
  /* assume that this only read one TLV value */
  int32_t value;
  size_t len = ctx->reader->read_int(ctx, inbuf, insize, &value);

  ctb = value;
  /* return the number of bytes read */
  return len;
}
/*---------------------------------------------------------------------------*/
LWM2M_RESOURCES(presence_resources,
                /* Presence (Current) */
                LWM2M_RESOURCE_CALLBACK(5500, { read_state, NULL, NULL }),
                /* Counter of detected presences */
				LWM2M_RESOURCE_INTEGER_VAR(5501, &counter),
                /* Reset the counter */
				LWM2M_RESOURCE_CALLBACK(5505, { NULL, NULL, reset_counter }),
				/* Application type */
				LWM2M_RESOURCE_STRING(5751, "Presence"),
                /* Busy to Clear delay */
				LWM2M_RESOURCE_CALLBACK(5903, { read_btc, set_btc, NULL }),
                /* Clear to Busy delay */
				LWM2M_RESOURCE_CALLBACK(5904, { read_ctb, set_ctb, NULL }),
                );
LWM2M_INSTANCES(presence_instances,
                LWM2M_INSTANCE(0, presence_resources));
LWM2M_OBJECT(presence, 3302, presence_instances);

/*---------------------------------------------------------------------------*/
#if PRESENCE_PERIODIC

static struct ctimer periodic_timer;

static void
handle_periodic_timer(void *ptr)
{
  int32_t current_state;
  int led_state;
  int led_idx= led_index_of(LEDS_GREEN);

  /* Only notify when the value has changed since last */
 	IPSO_PRESENCE.read_value(&current_state);
	led_state = read_led_external(led_idx);

  	if(current_state == 1 && last_state== 0 && led_state == 0 && led_idx > -1)
  	{
  		leds_on(LEDS_GREEN);
  		write_led_external(led_idx, 1);
  	}
  	else if (current_state == 0 && last_state== 1 && led_state == 1 && led_idx > -1)
  	{
  		leds_off(LEDS_GREEN);
  		write_led_external(led_idx, 0);
  	}
  	if(current_state != last_state) {
  	    last_state = current_state;
  	    lwm2m_object_notify_observers(&presence, "/0/5500");
  	 }
  ctimer_reset(&periodic_timer);
}
/*---------------------------------------------------------------------------*/

void
ipso_presence_init(void)
{
	int32_t current_state;

  IPSO_PRESENCE.init();
  /* register this device and its handlers - the handlers automatically
     sends in the object to handle */
  lwm2m_engine_register_object(&presence);

  IPSO_PRESENCE.read_value(&current_state);
  ctimer_set(&periodic_timer, CLOCK_SECOND * PRESENCE_TIMER, handle_periodic_timer, NULL);
}
/*---------------------------------------------------------------------------*/
#else

PROCESS(ipso_presence_process, "ipso-presence");

void
ipso_presence_init(void)
{
  int32_t current_state;

  IPSO_PRESENCE.init();
  /* register this device and its handlers - the handlers automatically
     sends in the object to handle */
  lwm2m_engine_register_object(&presence);

  process_start(&ipso_presence_process, NULL);

}

PROCESS_THREAD(ipso_presence_process, ev, data)
{

  int32_t current_state;
  int led_state;


  PROCESS_BEGIN();

  while(1) {
    PROCESS_WAIT_EVENT();

    if(ev == sensors_event && data == &presence_sensor) {

    	IPSO_PRESENCE.read_value(&current_state);
		led_state = read_led_external(LEDS_GREEN);

    	if(current_state == 1 && led_state == 0)
    	{
    		leds_on(LEDS_GREEN);
    		write_led_external(LEDS_GREEN, 1);
    	}
    	else if (current_state == 0 && led_state == 1)
    	{
    		leds_off(LEDS_GREEN);
    		write_led_external(LEDS_GREEN, 0);
    	}
    	if(current_state != last_state) {
    	    last_state = current_state;
    	    lwm2m_object_notify_observers(&presence, "/0/5500");
    	 }

    }
  }

  PROCESS_END();
}
#endif

/** @} */
