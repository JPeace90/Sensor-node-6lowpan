/*
 * Copyright (c) 2015, Yanzi Networks AB.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \addtogroup oma-lwm2m
 * @{
 *
 */

/**
 * \file
 *         Implementation of the Contiki OMA LWM2M server
 * \author
 *         Joakim Eriksson <joakime@sics.se>
 *         Niclas Finne <nfi@sics.se>
 */

/*
 * 2016-09-xx Modified by ST Central Lab: Pmin implementation, Registration Update trigger
 */

#include <stdint.h>
#include "lwm2m-object.h"
#include "lwm2m-engine.h"

#include "lwm2m-server.h"

#define DEBUG 0
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

#ifdef LWM2M_CONF_SERVER_MAX_COUNT
#define MAX_COUNT LWM2M_CONF_SERVER_MAX_COUNT
#else
#define MAX_COUNT 1//2//MGR
#endif

static int32_t sid_arr[MAX_COUNT] = {101};
static int32_t lifetime_arr[MAX_COUNT] = {86400};
static int32_t def_pmin_arr[MAX_COUNT];//MGR
static int32_t def_pmax_arr[MAX_COUNT];//MGR
static lwm2m_instance_t server_instances[MAX_COUNT];

/*---------------------------------------------------------------------------*/
static int
read_def_pmin(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  return ctx->writer->write_int(ctx, outbuf, outsize, def_pmin_arr[ctx->object_instance_index]);
}
/*---------------------------------------------------------------------------*/
static int
set_def_pmin(lwm2m_context_t *ctx, const uint8_t *inbuf, size_t insize,
           uint8_t *outbuf, size_t outsize)
{
  /* assume that this only read one TLV value */
  int32_t value;
  size_t len = ctx->reader->read_int(ctx, inbuf, insize, &value);

  def_pmin_arr[ctx->object_instance_index] = value;
  /* return the number of bytes read */
  return len;
}
/*---------------------------------------------------------------------------*/
static int
read_def_pmax(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  return ctx->writer->write_int(ctx, outbuf, outsize, def_pmax_arr[ctx->object_instance_index]);
}
/*---------------------------------------------------------------------------*/
static int
set_def_pmax(lwm2m_context_t *ctx, const uint8_t *inbuf, size_t insize,
           uint8_t *outbuf, size_t outsize)
{
  /* assume that this only read one TLV value */
  int32_t value;
  size_t len = ctx->reader->read_int(ctx, inbuf, insize, &value);

  def_pmax_arr[ctx->object_instance_index] = value;
  /* return the number of bytes read */
  return len;
}
/*---------------------------------------------------------------------------*/
static int
exec_reg_update(lwm2m_context_t *ctx, const uint8_t *arg, size_t arg_size,
        uint8_t *outbuf, size_t outsize)
{
  update_to_lwm2m_server();
  return 0;
}
/*---------------------------------------------------------------------------*/

LWM2M_RESOURCES(server_resources,
		LWM2M_RESOURCE_INTEGER_VAR_ARR(0, MAX_COUNT, sid_arr),
		LWM2M_RESOURCE_INTEGER_VAR_ARR(1, MAX_COUNT, lifetime_arr),
		LWM2M_RESOURCE_CALLBACK(2, {read_def_pmin, set_def_pmin, NULL}), //MGR
		LWM2M_RESOURCE_CALLBACK(3, {read_def_pmax, set_def_pmax, NULL}), //MGR
		LWM2M_RESOURCE_STRING(7, "U"),//MGR
		LWM2M_RESOURCE_CALLBACK(8, {NULL, NULL, exec_reg_update}), //MGR
                );
LWM2M_OBJECT(server, 1, server_instances);
/*---------------------------------------------------------------------------*/
void
lwm2m_server_init(void)
{
//  lwm2m_instance_t template = LWM2M_INSTANCE_UNUSED(0, server_resources);
  lwm2m_instance_t template = LWM2M_INSTANCE(0, server_resources);
  int i;

  /* Initialize the instances */
  for(i = 0; i < MAX_COUNT; i++) {
    server_instances[i] = template;
    server_instances[i].id = i;
  }

  /**
   * Register this device and its handlers - the handlers
   * automatically sends in the object to handle
   */
  PRINTF("*** Init lwm2m-server\n");
  lwm2m_engine_register_object(&server);
}
/*---------------------------------------------------------------------------*/
int32_t get_def_pmin(void)
{
	return def_pmin_arr[0];//MGR FIXME instance... for the moment we support only one server
}
/*---------------------------------------------------------------------------*/
int32_t get_def_pmax(void)
{
	return def_pmax_arr[0];//MGR FIXME instance... for the moment we support only one server
}
/** @} */
