/**
******************************************************************************
  * @file    ipso-digital-output.c
  * @author  Central LAB
  * @version V1.0.0
  * @date    20-June-2016
  * @brief   IPSO digital output
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
 *
 */

/**
 * \file
 *         Implementation of OMA LWM2M / IPSO Actuation
 * \author
 *         Nicola Stefani
 */

#include "ipso-objects.h"
#include "lwm2m-object.h"
#include "lwm2m-engine.h"

/*---------------------------------------------------------------------------*/
#define MAX_APPLEN 16
#define STATE_HIGH 0x01
#define STATE_LOW  0x00

static int polarity = 0;
static int state = 0;

void init_digital_pin(void);
void write_digital_pin(int level);
int read_digital_pin(void);

/*---------------------------------------------------------------------------*/
static int
read_state(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{

  int value;
  if(polarity == 0) {
	value = read_digital_pin();
	printf("state = %d", state);
  } else {
	value = !(read_digital_pin());
	printf("state = %d", state);

  }
  return ctx->writer->write_boolean(ctx, outbuf, outsize, value);
}
/*---------------------------------------------------------------------------*/
static int
write_state(lwm2m_context_t *ctx, const uint8_t *inbuf, size_t insize,
            uint8_t *outbuf, size_t outsize)
{
  int value;
  size_t len;

  len = ctx->reader->read_boolean(ctx, inbuf, insize, &value);
  if(len > 0) {
    if(value) {
    	if(polarity == 0 && state == 0) {
    		write_digital_pin(STATE_HIGH);
    		state = 1;
      }
    	else if (polarity == 1 && state == 1){
    		write_digital_pin(STATE_LOW);
    		state = 0;
      }
    } else {
        if(polarity == 0 && state == 1) {
        	write_digital_pin(STATE_LOW);
        	state = 0;
        }
        else if (polarity == 1 && state == 0){
        	write_digital_pin(STATE_HIGH);
        	state = 1;
        }
    }
  }
  else {
	  printf ("something wrong when trying to write state\n");
  }

  return len;
}

/*---------------------------------------------------------------------------*/
static int
read_polarity(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
	return ctx->writer->write_boolean(ctx, outbuf, outsize, polarity);
}
/*---------------------------------------------------------------------------*/
static int
write_polarity(lwm2m_context_t *ctx,
              const uint8_t *inbuf, size_t insize,
              uint8_t *outbuf, size_t outsize)
{
  int value;
  size_t len;

  len = ctx->reader->read_boolean(ctx, inbuf, insize, &value);
  if(len > 0) {
    if(value != polarity) {
      polarity = value;
    }
  }
  else {
	  printf ("something wrong when trying to write polarity\n");
  }
  return len;
}

/*---------------------------------------------------------------------------*/
LWM2M_RESOURCES(digital_output_resources,
                LWM2M_RESOURCE_CALLBACK(5550, { read_state, write_state, NULL }),
                LWM2M_RESOURCE_CALLBACK(5551, { read_polarity, write_polarity, NULL }),
				LWM2M_RESOURCE_STRING(5750, "Digital Output"),
              );
LWM2M_INSTANCES(digital_output_instances,
		LWM2M_INSTANCE(0, digital_output_resources));
LWM2M_OBJECT(digital_output, 3201, digital_output_instances);
/*---------------------------------------------------------------------------*/
void
ipso_digital_output_init(void)
{

  init_digital_pin();
  lwm2m_engine_register_object(&digital_output);
}
/*---------------------------------------------------------------------------*/
/** @} */
