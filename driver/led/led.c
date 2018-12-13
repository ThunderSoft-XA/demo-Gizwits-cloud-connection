#include "led.h"
#include "quectel_utils.h"			
#include "../../sdk/include/qapi/qapi_timer.h"		//QAPI_TIMER_UNIT_SEC
#include "../../main/log.h"		// gizLog

/*  !!! This Pin Enumeration Only Applicable BG96-OPEN Project !!!
 */
extern GPIO_MAP_TBL gpio_map_tbl[PIN_E_GPIO_MAX];

/* gpio id table */
extern qapi_GPIO_ID_t gpio_id_tbl[PIN_E_GPIO_MAX];

/* gpio tlmm config table */
extern qapi_TLMM_Config_t tlmm_config[PIN_E_GPIO_MAX];

extern MODULE_PIN_ENUM  led_pin_num_motion ;
extern MODULE_PIN_ENUM  led_pin_num_Pulsesensor ;
extern MODULE_PIN_ENUM  led_pin_num_pressure ;


/**************************************************************************
*                                 FUNCTION
***************************************************************************/
/*
@func
  motorSetValue
@brief
  [in]  ledvalue
  		ledvalue: 0x00 | 0x01
*/


void ledsetvalue(uint8_t ledvalue)
{
	gizLog(LOG_INFO,"in ledsetvalue.....\n"); 
	qapi_Status_t status = QAPI_OK;
	if(ledvalue == 0x00)
	{
		status = qapi_TLMM_Drive_Gpio(gpio_id_tbl[led_pin_num_pressure], gpio_map_tbl[led_pin_num_pressure].gpio_id, QAPI_GPIO_LOW_VALUE_E);
		//IOT_DEBUG("[GPIO] Set %d QAPI_GPIO_LOW_VALUE_E status = %d", g_test_pin_num, status);
		gizLog(LOG_INFO,"set %d QAPI_GPIO_LOW_VALUE_E status = %d\n",led_pin_num_pressure, status);
		//qapi_Timer_Sleep(5, QAPI_TIMER_UNIT_SEC, true);
	}
	else if(ledvalue == 0x01)
	{
		status = qapi_TLMM_Drive_Gpio(gpio_id_tbl[led_pin_num_pressure], gpio_map_tbl[led_pin_num_pressure].gpio_id, QAPI_GPIO_HIGH_VALUE_E);
		//IOT_DEBUG("[GPIO] Set QAPI_GPIO_HIGH_VALUE_E %d  status = %d", g_test_pin_num, status);
		gizLog(LOG_INFO,"set %d QAPI_GPIO_HIGH_VALUE_E status = %d\n",led_pin_num_pressure, status);
		//qapi_Timer_Sleep(5, QAPI_TIMER_UNIT_SEC, true);
	}
}



/*
@func
  gpio_config
@brief
  [in]  m_pin
  		MODULE_PIN_ENUM type; the GPIO pin which customer want used for operation;
  [in]  gpio_dir
  		qapi_GPIO_Direction_t type; GPIO pin direction.
  [in]  gpio_pull
  		qapi_GPIO_Pull_t type; GPIO pin pull type.
  [in]  gpio_drive
  		qapi_GPIO_Drive_t type; GPIO pin drive strength. 
*/

void gpio_config(MODULE_PIN_ENUM m_pin,qapi_GPIO_Direction_t gpio_dir,qapi_GPIO_Pull_t gpio_pull,qapi_GPIO_Drive_t gpio_drive)
{
	gizLog(LOG_INFO,"in led gpio config.....\n"); 
	
	qapi_Status_t status = QAPI_OK;

	tlmm_config[m_pin].pin   = gpio_map_tbl[m_pin].gpio_id;
	tlmm_config[m_pin].func  = gpio_map_tbl[m_pin].gpio_func;
	tlmm_config[m_pin].dir   = gpio_dir;
	tlmm_config[m_pin].pull  = gpio_pull;
	tlmm_config[m_pin].drive = gpio_drive;

	// the default here
	status = qapi_TLMM_Get_Gpio_ID(&tlmm_config[m_pin], &gpio_id_tbl[m_pin]);
	//IOT_DEBUG(LOG_INFO, "gpio_id[%d], status = %d", gpio_map_tbl[m_pin].gpio_id, status);
	
	gizLog(LOG_INFO,"pin_num = %d, gpio_id[%d], status = %d ...\n",gpio_map_tbl[m_pin].pin_num, gpio_map_tbl[m_pin].gpio_id, status); 
	
	if (status == QAPI_OK)
	{
		status = qapi_TLMM_Config_Gpio(gpio_id_tbl[m_pin], &tlmm_config[m_pin]);
		//IOT_DEBUG("[GPIO] gpio_id[%d] status = %d", gpio_map_tbl[m_pin].gpio_id, status);
		gizLog(LOG_INFO,"after qapi_TLMM_Config_Gpio, status = %d ...\n", status); 
		
		if (status != QAPI_OK)
		{
			//IOT_DEBUG("[GPIO] gpio_config failed");
			gizLog(LOG_INFO,"gpio config failed.....\n"); 
		}
//		status = qapi_TLMM_Drive_Gpio(gpio_id_tbl[led_pin_num_pressure], gpio_map_tbl[led_pin_num_pressure].gpio_id, QAPI_GPIO_LOW_VALUE_E);	(low work for motor)
//		qapi_Timer_Sleep(5, QAPI_TIMER_UNIT_SEC, true);
		
		status = qapi_TLMM_Drive_Gpio(gpio_id_tbl[led_pin_num_pressure], gpio_map_tbl[led_pin_num_pressure].gpio_id, QAPI_GPIO_HIGH_VALUE_E);
//		qapi_Timer_Sleep(5, QAPI_TIMER_UNIT_SEC, true);
	}
}
