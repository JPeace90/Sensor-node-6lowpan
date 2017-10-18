/**
******************************************************************************
  * @file    ipso-magneto.c
  * @author  Central LAB
  * @version V1.0.0
  * @date    15-September-2016
  * @brief   IPSO Magnetometer Object
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
 *         Implementation of OMA LWM2M / IPSO Magnetometer
 * \author
 *         Marco Grella
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
#define MAGNETO_IDLE_THRESH 	0 /*Does it makes sense for magnetometer?*/
#define MAGNETO_TIMER          10
/*---------------------------------------------------------------------------*/
#ifdef IPSO_MAGNETO
extern const struct ipso_objects_sensor IPSO_MAGNETO;
#endif /* IPSO_MAGNETO */
/*---------------------------------------------------------------------------*/
#ifdef IPSO_MAGNETO_X
extern const struct ipso_objects_sensor IPSO_MAGNETO_X;
#endif /* IPSO_MAGNETO_X */
/*---------------------------------------------------------------------------*/
#ifdef IPSO_MAGNETO_Y
extern const struct ipso_objects_sensor IPSO_MAGNETO_Y;
#endif /* IPSO_MAGNETO_Y */
/*---------------------------------------------------------------------------*/
#ifdef IPSO_MAGNETO_Z
extern const struct ipso_objects_sensor IPSO_MAGNETO_Z;
#endif /* IPSO_MAGNETO_Z */
/*---------------------------------------------------------------------------*/
static struct ctimer periodic_timer;
static int32_t last_X;
static int32_t last_Y;
static int32_t last_Z;
/*---------------------------------------------------------------------------*/
static int32_t pmin = MAGNETO_TIMER;
/*---------------------------------------------------------------------------*/
static int get_magneto(int32_t axis, int32_t *value);
/*---------------------------------------------------------------------------*/
static int
read_mgnX(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  int32_t value;
  if(get_magneto(X_AXIS, &value)) {
    return ctx->writer->write_float32fix(ctx, outbuf, outsize,
                                         value, LWM2M_FLOAT32_BITS);
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
static int
read_mgnY(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  int32_t value;
  if(get_magneto(Y_AXIS, &value)) {
    return ctx->writer->write_float32fix(ctx, outbuf, outsize,
                                         value, LWM2M_FLOAT32_BITS);
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
static int
read_mgnZ(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  int32_t value;
  if(get_magneto(Z_AXIS, &value)) {
    return ctx->writer->write_float32fix(ctx, outbuf, outsize,
                                         value, LWM2M_FLOAT32_BITS);
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
LWM2M_RESOURCES(magneto_resources,
                /* Acceleration (Current) */
                LWM2M_RESOURCE_CALLBACK(5702, { read_mgnX, NULL, NULL }),
                LWM2M_RESOURCE_CALLBACK(5703, { read_mgnY, NULL, NULL }),
                LWM2M_RESOURCE_CALLBACK(5704, { read_mgnZ, NULL, NULL }),
                /* Units */
                LWM2M_RESOURCE_STRING(5701, "gauss"),
                );
LWM2M_INSTANCES(magneto_instances,
                LWM2M_INSTANCE(0, magneto_resources));
LWM2M_OBJECT(magneto, 3314, magneto_instances);
/*---------------------------------------------------------------------------*/
static int
get_magneto(int32_t axis, int32_t *mgn)
{
#ifdef IPSO_MAGNETO
  if (axis == X_AXIS){
	  IPSO_MAGNETO_X.read_value(mgn);
  } else if (axis == Y_AXIS){
	  IPSO_MAGNETO_Y.read_value(mgn);
  } else if (axis == Z_AXIS) {
	  IPSO_MAGNETO_Z.read_value(mgn);
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

  /* Only notify when the value has changed since last of a given threshold */
  if(get_magneto(X_AXIS, &v) && v != last_X) {
	  if((v > (last_X + MAGNETO_IDLE_THRESH)) || (v < (last_X - MAGNETO_IDLE_THRESH))){
		  lwm2m_object_notify_observers(&magneto, "/0/5702");
	  }

	  last_X = v;
  }
  if(get_magneto(Y_AXIS, &v) && v != last_Y) {

	  if((v > (last_Y + MAGNETO_IDLE_THRESH)) || (v < (last_Y - MAGNETO_IDLE_THRESH))){
		  lwm2m_object_notify_observers(&magneto, "/0/5703");
	  }

	  last_Y = v;
  }
  if(get_magneto(Z_AXIS, &v) && v != last_Z) {

	  if((v > (last_Z + MAGNETO_IDLE_THRESH)) || (v < (last_Z - MAGNETO_IDLE_THRESH))){
		  lwm2m_object_notify_observers(&magneto, "/0/5704");
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
ipso_magneto_init(void)
{

#ifdef IPSO_MAGNETO
  IPSO_MAGNETO.init();
#endif

  /* register this device and its handlers - the handlers automatically
     sends in the object to handle */
  lwm2m_engine_register_object(&magneto);

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
