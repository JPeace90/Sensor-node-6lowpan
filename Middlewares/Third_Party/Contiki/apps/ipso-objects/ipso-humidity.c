/**
******************************************************************************
  * @file    ipso-humidity.c
  * @author  Central LAB
  * @version V1.0.0
  * @date    15-September-2016
  * @brief   IPSO Humidity Object
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
 *         Implementation of OMA LWM2M / IPSO Humidity
 * \author
 *         Nicola Stefani
 */

#include <stdint.h>
#include "ipso-objects.h"
#include "lwm2m-object.h"
#include "lwm2m-engine.h"
#include "er-coap-engine.h"
/*---------------------------------------------------------------------------*/
#define HUMIDITY_NOTIFICATION_THRESH 1000
#define HUMIDITY_TIMER 60
/*---------------------------------------------------------------------------*/
#ifdef IPSO_HUMIDITY
extern const struct ipso_objects_sensor IPSO_HUMIDITY;
#endif /* IPSO_HUMIDITY */
/*---------------------------------------------------------------------------*/
#ifndef IPSO_HUMIDITY_MIN
#define IPSO_HUMIDITY_MIN (1 * LWM2M_FLOAT32_FRAC)
#endif
/*---------------------------------------------------------------------------*/
#ifndef IPSO_HUMIDITY_MAX
#define IPSO_HUMIDITY_MAX (100 * LWM2M_FLOAT32_FRAC)
#endif
/*---------------------------------------------------------------------------*/
static struct ctimer periodic_timer;
static int32_t min_hum;
static int32_t max_hum;
static int read_hum(int32_t *value);
/*---------------------------------------------------------------------------*/
static int
hum(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  int32_t value;
  if(read_hum(&value)) {
    return ctx->writer->write_float32fix(ctx, outbuf, outsize,
                                         value, LWM2M_FLOAT32_BITS);
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
LWM2M_RESOURCES(humidity_resources,
                /* Temperature (Current) */
                LWM2M_RESOURCE_CALLBACK(5700, { hum, NULL, NULL }),
                /* Units */
                LWM2M_RESOURCE_STRING(5701, "rH"),
                /* Min Range Value */
                LWM2M_RESOURCE_FLOATFIX(5603, IPSO_HUMIDITY_MIN),
                /* Max Range Value */
                LWM2M_RESOURCE_FLOATFIX(5604, IPSO_HUMIDITY_MAX),
                /* Min Measured Value */
                LWM2M_RESOURCE_FLOATFIX_VAR(5601, &min_hum),
                /* Max Measured Value */
                LWM2M_RESOURCE_FLOATFIX_VAR(5602, &max_hum),
                );
LWM2M_INSTANCES(humidity_instances,
                LWM2M_INSTANCE(0, humidity_resources));
LWM2M_OBJECT(humidity, 3304, humidity_instances);
/*---------------------------------------------------------------------------*/
static int
read_hum(int32_t *value)
{
#ifdef IPSO_HUMIDITY
  int32_t hum_t;
  if(IPSO_HUMIDITY.read_value == NULL ||
     IPSO_HUMIDITY.read_value(&hum_t) != 0) {
    return 0;
  }

//  *value = (hum_t * LWM2M_FLOAT32_FRAC) / 1000;
  *value = hum_t ;

  /*Decide if to apply the Threshold also to min and max*/
  if(*value < min_hum) {
    min_hum = *value;
    lwm2m_object_notify_observers(&humidity, "/0/5601");
  }
  if(*value > max_hum) {
    max_hum = *value;
    lwm2m_object_notify_observers(&humidity, "/0/5602");
  }
  return 1;
#else /* IPSO_HUMIDITY */
  return 0;
#endif /* IPSO_HUMIDITY */
}
/*---------------------------------------------------------------------------*/
static void
handle_periodic_timer(void *ptr)
{
  static int32_t last_value = IPSO_HUMIDITY_MIN;
  int32_t v;

  /* Only notify when the value has changed since last */
  if(read_hum(&v) && v != last_value) {
	  if ((v < last_value - HUMIDITY_NOTIFICATION_THRESH) ||
		  (v > last_value + HUMIDITY_NOTIFICATION_THRESH)){
		  last_value = v;
		  lwm2m_object_notify_observers(&humidity, "/0/5700");
	  }
  }
  ctimer_reset(&periodic_timer);
}
/*---------------------------------------------------------------------------*/
void
ipso_humidity_init(void)
{
  int32_t v;
  min_hum = IPSO_HUMIDITY_MAX;
  max_hum = IPSO_HUMIDITY_MIN;

#ifdef IPSO_HUMIDITY
  if(IPSO_HUMIDITY.init) {
    IPSO_HUMIDITY.init();
  }
#endif /* IPSO_HUMIDITY */

  /* register this device and its handlers - the handlers automatically
     sends in the object to handle */
  lwm2m_engine_register_object(&humidity);

  /* update hum and min/max + notify any listeners */
  read_hum(&v);
  ctimer_set(&periodic_timer, CLOCK_SECOND * HUMIDITY_TIMER, handle_periodic_timer, NULL);
}
/*---------------------------------------------------------------------------*/
/** @} */
