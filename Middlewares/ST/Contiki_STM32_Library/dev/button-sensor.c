/**
******************************************************************************
* @file    platform/stm32nucleo-spirit1/dev/button-sensor.c
* @author  System LAB
* @version V1.0.0
* @date    17-June-2015
* @brief   Enable button sensor functionality 
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
 * @defgroup button_sensor
 * @ingroup dev
 * @{
 */

/**
 * @addtogroup button_sensor
 * @ingroup dev
 * @{
 * @file Driver for the board User Button
 */

/*---------------------------------------------------------------------------*/
#include "dev/button-sensor.h"
#include "lib/sensors.h"
#include "st-lib.h"
/*---------------------------------------------------------------------------*/
static int _active = 0 ;
/*---------------------------------------------------------------------------*/
static void init(void)
{
  /* See stm32f4xx_it.c for the callback that triggers the relevant
   * "sensors_changed" event
   */
  st_lib_bsp_pb_init(BUTTON_USER, BUTTON_MODE_EXTI);
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
  /*Note: 0 means pressed, 1 means not pressed.*/
  return st_lib_bsp_pb_get_state(BUTTON_USER);
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
SENSORS_SENSOR(button_sensor, BUTTON_SENSOR, value, configure, status);
/*---------------------------------------------------------------------------*/
/** @} */
/** @} */
