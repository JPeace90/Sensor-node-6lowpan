/* Sensor node implementation using 6LoWPAN and RPL protocols
 * Author: Giovanni Pisana
 * University of Bologna - Computer Science
 */

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "main.h"
#include "cube_hal.h"
#include "radio_shield_config.h"
#include "spirit1.h"
#include "process.h"
#include "sensors_settings.h"



/* Private function prototypes -----------------------------------------------*/

void USARTConfig(void);
void Stack_6LoWPAN_Init(void);


/**
  * @brief  main()
  * @param  None
  * @retval None
  */
int main()
{
	DrvStatusTypeDef status;
	System_Status_t statusinit;
	void *TEMPERATURE_handle=NULL;
	void *HUMIDITY_handle=NULL;
	float temperature_value;
	float humidity_value;
    HAL_Init();
    /* Configure the system clock */
    SystemClock_Config();

    HAL_EnableDBGStopMode();
    
    MX_GPIO_Init();
    
    /* Initialize LEDs */
    BSP_LED_Init(LED2);

    RadioShieldLedInit(RADIO_SHIELD_LED);

    BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);

    USARTConfig();

    /* Initialize RTC */
    RTC_Config();
    RTC_TimeStampConfig();

    /*Compiler, HAL and firmware info:*/
  printf("\t(HAL %ld.%ld.%ld_%ld)\r\n"
      "\tCompiled %s %s"
#if defined (__IAR_SYSTEMS_ICC__)
      " (IAR)\r\n\n",
#elif defined (__CC_ARM)
      " (KEIL)\r\n\n",
#elif defined (__GNUC__)
      " (openstm32)\r\n\n",
#endif
         HAL_GetHalVersion() >>24,
        (HAL_GetHalVersion() >>16)&0xFF,
        (HAL_GetHalVersion() >> 8)&0xFF,
         HAL_GetHalVersion()      &0xFF,
       __DATE__,__TIME__);

  	//init sensors
  	statusinit = initSensors();

  	//init stack
    Stack_6LoWPAN_Init();

    while(1) {
      int r = 0;
      do {
        r = process_run();
      } while(r > 0);
    }

}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
