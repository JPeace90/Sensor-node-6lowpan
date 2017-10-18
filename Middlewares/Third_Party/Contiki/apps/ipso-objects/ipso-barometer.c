/**
******************************************************************************
  * @file    ipso-barometer.c
  * @author  Central LAB
  * @version V1.0.0
  * @date    15-September-2016
  * @brief   IPSO Barometer Object
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
 *         Implementation of OMA LWM2M / IPSO Pressure
 * \author
 *         Nicola Stefani
 */

#include <stdint.h>
#include "ipso-objects.h"
#include "lwm2m-object.h"
#include "lwm2m-engine.h"
#include "er-coap-engine.h"
/*---------------------------------------------------------------------------*/
#define BAROMETER_NOTIFICATION_THRESH 1000
#define BAROMETER_TIMER 60
/*---------------------------------------------------------------------------*/
#ifdef IPSO_BAROMETER
extern const struct ipso_objects_sensor IPSO_BAROMETER;
#endif /* IPSO_BAROMETER */
/*---------------------------------------------------------------------------*/
#ifndef IPSO_BAROMETER_MIN
#define IPSO_BAROMETER_MIN (260 * LWM2M_FLOAT32_FRAC)
#endif
/*---------------------------------------------------------------------------*/
#ifndef IPSO_BAROMETER_MAX
#define IPSO_BAROMETER_MAX (1260 * LWM2M_FLOAT32_FRAC)
#endif
/*---------------------------------------------------------------------------*/
static struct ctimer periodic_timer;
static int32_t min_bar;
static int32_t max_bar;
static int read_bar(int32_t *value);
/*---------------------------------------------------------------------------*/
static int
bar(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  int32_t value;
  if(read_bar(&value)) {
    return ctx->writer->write_float32fix(ctx, outbuf, outsize,
                                         value, LWM2M_FLOAT32_BITS);
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
LWM2M_RESOURCES(barometer_resources,
                /* Temperature (Current) */
                LWM2M_RESOURCE_CALLBACK(5700, { bar, NULL, NULL }),
                /* Units */
                LWM2M_RESOURCE_STRING(5701, "hPa"),
                /* Min Range Value */
                LWM2M_RESOURCE_FLOATFIX(5603, IPSO_BAROMETER_MIN),
                /* Max Range Value */
                LWM2M_RESOURCE_FLOATFIX(5604, IPSO_BAROMETER_MAX),
                /* Min Measured Value */
                LWM2M_RESOURCE_FLOATFIX_VAR(5601, &min_bar),
                /* Max Measured Value */
                LWM2M_RESOURCE_FLOATFIX_VAR(5602, &max_bar),
                );
LWM2M_INSTANCES(barometer_instances,
                LWM2M_INSTANCE(0, barometer_resources));
LWM2M_OBJECT(barometer, 3315, barometer_instances);
/*---------------------------------------------------------------------------*/
static int
read_bar(int32_t *value)
{
#ifdef IPSO_BAROMETER
  int32_t bar_t;
  if(IPSO_BAROMETER.read_value == NULL ||
     IPSO_BAROMETER.read_value(&bar_t) != 0) {
    return 0;
  }

//  *value = (bar_t * LWM2M_FLOAT32_FRAC) / 1000;
  *value = bar_t ;

  /*Decide if to apply the Threshold also to min and max*/
  if(*value < min_bar) {
    min_bar = *value;
    lwm2m_object_notify_observers(&barometer, "/0/5601");
  }
  if(*value > max_bar) {
    max_bar = *value;
    lwm2m_object_notify_observers(&barometer, "/0/5602");
  }
  return 1;
#else /* IPSO_BAROMETER */
  return 0;
#endif /* IPSO_BAROMETER */
}
/*---------------------------------------------------------------------------*/
static void
handle_periodic_timer(void *ptr)
{
  static int32_t last_value = IPSO_BAROMETER_MIN;
  int32_t v;

  /* Only notify when the value has changed since last */
  if(read_bar(&v) && v != last_value) {
	  if ((v < last_value - BAROMETER_NOTIFICATION_THRESH) ||
		  (v > last_value + BAROMETER_NOTIFICATION_THRESH)){
		  last_value = v;
		  lwm2m_object_notify_observers(&barometer, "/0/5700");
	  }
  }
  ctimer_reset(&periodic_timer);
}
/*---------------------------------------------------------------------------*/
void
ipso_barometer_init(void)
{
  int32_t v;
  min_bar = IPSO_BAROMETER_MAX;
  max_bar = IPSO_BAROMETER_MIN;

#ifdef IPSO_BAROMETER
  if(IPSO_BAROMETER.init) {
    IPSO_BAROMETER.init();
  }
#endif /* IPSO_BAROMETER */

  /* register this device and its handlers - the handlers automatically
     sends in the object to handle */
  lwm2m_engine_register_object(&barometer);

  /* update hum and min/max + notify any listeners */
  read_bar(&v);
  ctimer_set(&periodic_timer, CLOCK_SECOND * BAROMETER_TIMER, handle_periodic_timer, NULL);
}
/*---------------------------------------------------------------------------*/
/** @} */
