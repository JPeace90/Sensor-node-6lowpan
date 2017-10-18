/**
******************************************************************************
  * @file    lwm2m-server.h
  * @author  Central LAB
  * @version V1.0.0
  * @date    20-June-2016
  * @brief   LWM2M Server Header file
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

#ifndef LWM2M_SERVER_H
#define LWM2M_SERVER_H
/*---------------------------------------------------------------------------*/
#define LWM2M_SERVER_SHORT_SERVER_ID             0
#define LWM2M_SERVER_LIFETIME                    1
#define LWM2M_SERVER_DEFAULT_MINIMUM_PERIOD      2
#define LWM2M_SERVER_DEFAULT_MAXIMUM_PERIOD      3
#define LWM2M_SERVER_DISABLE                     4
#define LWM2M_SERVER_DISABLE_TIMEOUT             5
#define LWM2M_SERVER_NOTIFICATION_STORING        6
#define LWM2M_SERVER_BINDING                     7
#define LWM2M_SERVER_REGISTRATION_UPDATE_TRIGGER 8
/*---------------------------------------------------------------------------*/
int32_t get_def_pmin(void);
/*---------------------------------------------------------------------------*/
int32_t get_def_pmax(void);
/*---------------------------------------------------------------------------*/
#endif /*LWM2M_SERVER_H*/
