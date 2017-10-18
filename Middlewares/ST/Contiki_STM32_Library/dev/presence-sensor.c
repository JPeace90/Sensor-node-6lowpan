/**
******************************************************************************
  * @file    presence-sensor.c
  * @author  Central LAB
  * @version V1.0.0
  * @date    15-September-2016
  * @brief   Presence sensor
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
 * @defgroup dev
 * @ingroup STM32_Contiki_Library
 * @{
 */

/**
 * @defgroup presence_sensor
 * @ingroup dev
 * @{
 */

/**
 * @addtogroup presence_sensor
 * @ingroup dev
 * @{
 * @file Driver for the Proximity/Presence sensor (on expansion board)
 */

/*---------------------------------------------------------------------------*/
#if X_NUCLEO_6180XA1
/*---------------------------------------------------------------------------*/
#include "lib/sensors.h"
#include "presence-sensor.h"
#include "my_vl6180x.h"
#include "st-lib.h"
/*---------------------------------------------------------------------------*/
static int _active = 1;
/*---------------------------------------------------------------------------*/
static void init(void)
{

	st_lib_vl6180x_init();
	st_lib_vl6180x_kickoff(RANGE_ONLY,0);//1 == RANGE_ONLY
    _active = 1;

}
/*---------------------------------------------------------------------------*/
static void activate(void)
{
  _active = 1;
}
/*---------------------------------------------------------------------------*/
static void deactivate(void)
{
  _active = 0;
}
/*---------------------------------------------------------------------------*/
static int active(void)
{
  return _active;
}
/*---------------------------------------------------------------------------*/
static int value(int type)
{
  int32_t range;

  range = st_lib_vl6180x_get_range(type);

  if (range < PRESENCE_LOW_TH)
  {
	  return 1;
  }
  else
  {
	  return 0;
  }


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
SENSORS_SENSOR(presence_sensor, PRESENCE_SENSOR,
               value, configure, status);
/*---------------------------------------------------------------------------*/
#endif /*X_NUCLEO_VL6180X*/
/*---------------------------------------------------------------------------*/
/** @} */
/** @} */
/** @} */
