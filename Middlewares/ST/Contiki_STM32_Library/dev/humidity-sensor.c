/**
******************************************************************************
* @file    humidity-sensor.c
* @author  System LAB
* @version V1.0.0
* @date    17-June-2015
* @brief   Enable humidity sensor functionality 
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
 * @defgroup humidity_sensor
 * @ingroup dev
 * @{
 */

/**
 * @addtogroup humidity_sensor
 * @ingroup dev
 * @{
 * @file Driver for the Humidity sensor (on expansion board)
 */
/*---------------------------------------------------------------------------*/
#if COMPILE_SENSORS
/*---------------------------------------------------------------------------*/
#include "lib/sensors.h"
#include "humidity-sensor.h"
#include "st-lib.h"
/*---------------------------------------------------------------------------*/
static int _active = 0;
static void *humidity_handle = NULL;
/*---------------------------------------------------------------------------*/
static void init(void)
{
#ifdef USE_IKS01A2
  if (COMPONENT_ERROR == st_lib_bsp_humidity_init(HUMIDITY_SENSORS_AUTO, &humidity_handle)){
	  printf("ERROR initializing Humidity Sensor\n");
  }
#else
  if (COMPONENT_ERROR == st_lib_bsp_humidity_init(HTS221_H_0, &humidity_handle)){
	  printf("ERROR initializing Humidity Sensor\n");
  }
#endif
}
/*---------------------------------------------------------------------------*/
static void activate(void)
{
  if (st_lib_bsp_humidity_sensor_enable(humidity_handle) ==COMPONENT_OK){
    _active=1;
  }
}
/*---------------------------------------------------------------------------*/
static void deactivate(void)
{
  if (st_lib_bsp_humidity_sensor_disable(humidity_handle) ==COMPONENT_OK){
    _active=0;
  }
}
/*---------------------------------------------------------------------------*/
static int active(void)
{
  return _active;
}
/*---------------------------------------------------------------------------*/
/*We use \"type\" to select the multiplication factor since the sensor value
 * is a float and should be encoded */
static int value(int type)
{
  uint32_t humidity;
  volatile float humidity_value;
  uint8_t status = 0;
  
  if (st_lib_bsp_humidity_is_initialized(humidity_handle, &status) == COMPONENT_OK
  		&& status == 1){
    st_lib_bsp_humidity_get_hum(humidity_handle, (float *)&humidity_value);
  }
  humidity = (int) (humidity_value * ((type>0)?type:10));

  return humidity;
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
SENSORS_SENSOR(humidity_sensor, HUMIDITY_SENSOR, value, configure, status);
/*---------------------------------------------------------------------------*/
#endif /*COMPILE_SENSORS*/
/*---------------------------------------------------------------------------*/
/** @} */
/** @} */
