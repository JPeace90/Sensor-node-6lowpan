#ifndef __SENSORS_SETTINGS_H
#define __SENSORS_SETTINGS_H

#include "x_nucleo_iks01a2.h"
#include "x_nucleo_iks01a2_temperature.h"
#include "x_nucleo_iks01a2_humidity.h"
#include "x_nucleo_iks01a2_pressure.h"
#include "cube_hal.h"


#define SENSOR_PRINT(in, out_int, out_dec) {out_int = (int32_t)in; out_dec= (int32_t)((in-out_int)*100);};

void *TEMPERATURE_handle;
void *HUMIDITY_handle;
void *PRESSURE_handle;
float temperature_value;
float humidity_value;
float pressure_value;

typedef enum
{
  MODULE_SUCCESS           = 1,
  MODULE_ERROR           = -1
} System_Status_t;

static System_Status_t initSensors(void);

static System_Status_t initSensors(){
	System_Status_t status = MODULE_ERROR;

	if (BSP_TEMPERATURE_Init(TEMPERATURE_SENSORS_AUTO, &TEMPERATURE_handle)!=COMPONENT_OK){
		return status;
	}

	if (BSP_HUMIDITY_Init(HUMIDITY_SENSORS_AUTO, &HUMIDITY_handle)!=COMPONENT_OK){
		return status;
	}

	if (BSP_PRESSURE_Init(PRESSURE_SENSORS_AUTO, &PRESSURE_handle)!=COMPONENT_OK){
		return status;
	}

	BSP_TEMPERATURE_Sensor_Enable(TEMPERATURE_handle);
	BSP_TEMPERATURE_Sensor_Enable(HUMIDITY_handle);
	BSP_PRESSURE_Sensor_Enable(PRESSURE_handle);

	status = MODULE_SUCCESS;
	return status;
}

#endif
