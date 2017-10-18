/**
******************************************************************************
* @file    magneto-sensor.c
* @author  System LAB
* @version V1.0.0
* @date    17-June-2015
* @brief   Enable magnetometer sensor functionality
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
 * @defgroup magneto_sensor
 * @ingroup dev
 * @{
 */

/**
 * @addtogroup magneto_sensor
 * @ingroup dev
 * @{
 * @file Driver for the Magneto sensor (on expansion board)
 */
/*---------------------------------------------------------------------------*/
#if COMPILE_SENSORS
/*---------------------------------------------------------------------------*/
#include "lib/sensors.h"
#include "magneto-sensor.h"
#include "st-lib.h"
/*---------------------------------------------------------------------------*/
static int _active = 0;
static void *magneto_handle = NULL;
/*---------------------------------------------------------------------------*/
static void init(void)
{
#ifdef USE_IKS01A2
  if (COMPONENT_ERROR == st_lib_bsp_magneto_init(MAGNETO_SENSORS_AUTO, &magneto_handle)){
	  printf("ERROR initializing Magneto Sensor\n");
  }
#else
  if (COMPONENT_ERROR == st_lib_bsp_magneto_init(LIS3MDL_0, &magneto_handle)){
	  printf("ERROR initializing Magneto Sensor\n");
  }
#endif
}
/*---------------------------------------------------------------------------*/
static void activate(void)
{
  if (st_lib_bsp_magneto_sensor_enable(magneto_handle) == COMPONENT_OK) {
	_active=1;
  }
}
/*---------------------------------------------------------------------------*/
static void deactivate(void)
{
  if (st_lib_bsp_magneto_sensor_disable(magneto_handle) == COMPONENT_OK) {
	_active=0;
  }
}
/*---------------------------------------------------------------------------*/
static int active(void)
{
  return _active;
}
/*---------------------------------------------------------------------------*/
static int value(int type)
{
  int32_t ret_val = 0;
  st_lib_sensor_axes_t axes_data;
  uint8_t status = 0;

  /* NOTE: this is a demo of mapping ST Nucleo sensors on Contiki sensor API.
   * For a real use case of sensors like acceleration, magneto and gyroscope,
   * it is better to directly call the ST lib to get the three value (X/Y/Z)
   * at once.
   */
  if (st_lib_bsp_magneto_is_initialized(magneto_handle, &status) == COMPONENT_OK
      		&& status == 1) {
	  st_lib_bsp_magneto_get_axes(magneto_handle, &axes_data);
  }

  switch (type) {
    case X_AXIS:
        ret_val = axes_data.AXIS_X ;
	break;
    case Y_AXIS:
        ret_val = axes_data.AXIS_Y ;
	break;
    case Z_AXIS:
        ret_val = axes_data.AXIS_Z ;
	break;
    default:
	break;
  }

  return ret_val;
}
/*---------------------------------------------------------------------------*/
static int configure(int type, int value)
{
  switch(type) {
    case SENSORS_HW_INIT:
      init();
      return 1;
    case SENSORS_ACTIVE:
      if(value) {      
        activate();
      } else {
        deactivate();
      }
      return 1;
  }
 
  return 0;
}
/*---------------------------------------------------------------------------*/
static int status(int type)
{
  switch(type) {
    case SENSORS_READY:
      return active();
  }
  
  return 0;
}
/*---------------------------------------------------------------------------*/
SENSORS_SENSOR(magneto_sensor, MAGNETO_SENSOR, value, configure, status);
/*---------------------------------------------------------------------------*/
#endif /*COMPILE_SENSORS*/
/*---------------------------------------------------------------------------*/
/** @} */
/** @} */
