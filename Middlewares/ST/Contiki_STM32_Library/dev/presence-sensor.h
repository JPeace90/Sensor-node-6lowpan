/**
******************************************************************************
* @file    acceleration-sensor.h
* @author  System LAB
* @version V1.0.0
* @date    17-June-2015
* @brief   Enable aceleration sensor functionality 
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
/*---------------------------------------------------------------------------*/

/**
 * @addtogroup presence_sensor
 * @ingroup dev
 * Maps the presence sensor on the STM32 Sensor Expansion board.
 * @{
 * @file Header file for the Presence Sensor Driver
 */

/*---------------------------------------------------------------------------*/
#ifndef PRESENCE_SENSOR_H_
#define PRESENCE_SENSOR_H_
/*---------------------------------------------------------------------------*/
#include "lib/sensors.h"
#include "sensor-common.h"
/*---------------------------------------------------------------------------*/
extern const struct sensors_sensor presence_sensor;
/*---------------------------------------------------------------------------*/
#define PRESENCE_SENSOR "Presence"
/*---------------------------------------------------------------------------*/
#endif /* PRESENCE_SENSOR_H_ */
/*---------------------------------------------------------------------------*/
/**
 * @}
 */
