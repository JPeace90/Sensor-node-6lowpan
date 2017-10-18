/**
******************************************************************************
  * @file    ipso-acceleration.c
  * @author  Central LAB
  * @version V1.0.0
  * @date    15-September-2016
  * @brief   IPSO Acceleration Object
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
 *         Implementation of OMA LWM2M / IPSO Acceleration
 * \author
 *         Nicola Stefani
 */

#include <stdint.h>
#include "ipso-objects.h"
#include "lwm2m-object.h"
#include "lwm2m-engine.h"
#include "er-coap-engine.h"
#include "lwm2m-server.h"
#include "leds.h"
#include "sensor-common.h"
/*---------------------------------------------------------------------------*/
#define ACCELERATION_IDLE_THRESH 	100
#define LED_BLINK_THRESH 	       1500
#define ACCELERATION_TIMER            1
/*---------------------------------------------------------------------------*/
#ifdef IPSO_ACCELERATION
extern const struct ipso_objects_sensor IPSO_ACCELERATION;
#endif /* IPSO_ACCELERATION */
/*---------------------------------------------------------------------------*/
#ifdef IPSO_ACCELERATION_X
extern const struct ipso_objects_sensor IPSO_ACCELERATION_X;
#endif /* IPSO_ACCELERATION_X */
/*---------------------------------------------------------------------------*/
#ifdef IPSO_ACCELERATION_Y
extern const struct ipso_objects_sensor IPSO_ACCELERATION_Y;
#endif /* IPSO_ACCELERATION_Y */
/*---------------------------------------------------------------------------*/
#ifdef IPSO_ACCELERATION_Z
extern const struct ipso_objects_sensor IPSO_ACCELERATION_Z;
#endif /* IPSO_ACCELERATION_Z */
/*---------------------------------------------------------------------------*/
#ifndef IPSO_ACCELERATION_MIN
#define IPSO_ACCELERATION_MIN (-2000)//2G fullscale
#endif
/*---------------------------------------------------------------------------*/
#ifndef IPSO_ACCELERATION_MAX
#define IPSO_ACCELERATION_MAX (2000)//2G fullscale
#endif
/*---------------------------------------------------------------------------*/
static struct ctimer periodic_timer;
static int32_t last_X;
static int32_t last_Y;
static int32_t last_Z;
/*---------------------------------------------------------------------------*/
static int32_t pmin = ACCELERATION_TIMER;
/*---------------------------------------------------------------------------*/
static int get_acceleration(int32_t axis, int32_t *value);
/*---------------------------------------------------------------------------*/
static int
read_accX(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  int32_t value;
  if(get_acceleration(X_AXIS, &value)) {
    return ctx->writer->write_float32fix(ctx, outbuf, outsize,
                                         value, LWM2M_FLOAT32_BITS);
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
static int
read_accY(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  int32_t value;
  if(get_acceleration(Y_AXIS, &value)) {
    return ctx->writer->write_float32fix(ctx, outbuf, outsize,
                                         value, LWM2M_FLOAT32_BITS);
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
static int
read_accZ(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  int32_t value;
  if(get_acceleration(Z_AXIS, &value)) {
    return ctx->writer->write_float32fix(ctx, outbuf, outsize,
                                         value, LWM2M_FLOAT32_BITS);
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
LWM2M_RESOURCES(acceleration_resources,
                /* Acceleration (Current) */
                LWM2M_RESOURCE_CALLBACK(5702, { read_accX, NULL, NULL }),
                LWM2M_RESOURCE_CALLBACK(5703, { read_accY, NULL, NULL }),
                LWM2M_RESOURCE_CALLBACK(5704, { read_accZ, NULL, NULL }),
                /* Units */
                LWM2M_RESOURCE_STRING(5701, "g"),
                /* Min Range Value */
                LWM2M_RESOURCE_FLOATFIX(5603, IPSO_ACCELERATION_MIN),
                /* Max Range Value */
                LWM2M_RESOURCE_FLOATFIX(5604, IPSO_ACCELERATION_MAX),
                );
LWM2M_INSTANCES(acceleration_instances,
                LWM2M_INSTANCE(0, acceleration_resources));
LWM2M_OBJECT(acceleration, 3313, acceleration_instances);
/*---------------------------------------------------------------------------*/
static int
get_acceleration(int32_t axis, int32_t *acc)
{
#ifdef IPSO_ACCELERATION
  if (axis == X_AXIS){
	  IPSO_ACCELERATION_X.read_value(acc);
  } else if (axis == Y_AXIS){
	  IPSO_ACCELERATION_Y.read_value(acc);
  } else if (axis == Z_AXIS) {
	  IPSO_ACCELERATION_Z.read_value(acc);
  } else {
	  printf("Acceleration Axis not recognized\n");
	  return 0;
  }
#endif
  return 1;
}
/*---------------------------------------------------------------------------*/
static void
handle_periodic_timer(void *ptr)
{
  int32_t v;
  int led_state;
  int led_idx = led_index_of(LEDS_GREEN);
  static unsigned char led_on_by_acceleration = 0 ;

  if (led_idx==-1) led_idx = 0;
  led_state = read_led_external(led_idx);

  /* Only notify when the value has changed since last */
  if(get_acceleration(X_AXIS, &v) && v != last_X) {
	  if((v > (last_X + ACCELERATION_IDLE_THRESH)) || (v < (last_X - ACCELERATION_IDLE_THRESH))){
		  lwm2m_object_notify_observers(&acceleration, "/0/5702");
	  }

	  led_state = read_led_external(led_idx);

	  if((v > (last_X + LED_BLINK_THRESH)) || (v < (last_X - LED_BLINK_THRESH)))
	  {
		  if(led_state == 0)
		  {
			  leds_on(LEDS_GREEN);
			  write_led_external(led_idx, 1);
			  led_on_by_acceleration = 1;
		  }
	  }
	  else
	  {
		  if(led_state == 1 && led_on_by_acceleration == 1)
		  {
			  leds_off(LEDS_GREEN);
			  write_led_external(led_idx, 0);
			  led_on_by_acceleration = 0;
		  }
	  }
	  last_X = v;
  }
  if(get_acceleration(Y_AXIS, &v) && v != last_Y) {

	  if((v > (last_Y + ACCELERATION_IDLE_THRESH)) || (v < (last_Y - ACCELERATION_IDLE_THRESH))){
		  lwm2m_object_notify_observers(&acceleration, "/0/5703");
	  }

	  led_state = read_led_external(led_idx);

	  if((v > (last_Y + LED_BLINK_THRESH)) || (v < (last_Y - LED_BLINK_THRESH)))
	  {
		  if(led_state == 0)
		  {
			  leds_on(LEDS_GREEN);
			  write_led_external(led_idx, 1);
			  led_on_by_acceleration = 1;
		  }
	  }
	  else
	  {
		  if(led_state == 1 && led_on_by_acceleration == 1)
		  {
			  leds_off(LEDS_GREEN);
			  write_led_external(led_idx, 0);
			  led_on_by_acceleration = 0;
		  }
	  }
	  last_Y = v;
  }
  if(get_acceleration(Z_AXIS, &v) && v != last_Z) {

	  if((v > (last_Z + ACCELERATION_IDLE_THRESH)) || (v < (last_Z - ACCELERATION_IDLE_THRESH))){
		  lwm2m_object_notify_observers(&acceleration, "/0/5704");
	  }
	  led_state = read_led_external(led_idx);

	  if((v > (last_Z + LED_BLINK_THRESH)) || (v < (last_Z - LED_BLINK_THRESH)))
	  {
		  if(led_state == 0)
		  {
			  leds_on(LEDS_GREEN);
			  write_led_external(led_idx, 1);
			  led_on_by_acceleration = 1;
		  }
	  }
	  else
	  {
		  if(led_state == 1 && led_on_by_acceleration == 1)
		  {
			  leds_off(LEDS_GREEN);
			  write_led_external(led_idx, 0);
			  led_on_by_acceleration = 0;
		  }
	  }
	  last_Z = v;
  }

  int32_t pt = get_def_pmin();
  if (pt > 0 && pt != pmin)
  {
	  pmin = pt;
	  ctimer_set(&periodic_timer, CLOCK_SECOND * pmin, handle_periodic_timer, NULL);
  }
  else
  {
	  ctimer_reset(&periodic_timer);
  }
}
/*---------------------------------------------------------------------------*/
void
ipso_acceleration_init(void)
{

#ifdef IPSO_ACCELERATION
  IPSO_ACCELERATION.init();
#endif

  /* register this device and its handlers - the handlers automatically
     sends in the object to handle */
  lwm2m_engine_register_object(&acceleration);

  int32_t pt = get_def_pmin();
  if (pt > 0)
  {
	  pmin = pt;
  }
  /* update temp and min/max + notify any listeners */
  ctimer_set(&periodic_timer, CLOCK_SECOND * pmin, handle_periodic_timer, NULL);
}
/*---------------------------------------------------------------------------*/
/** @} */
