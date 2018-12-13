/**
************************************************************
* @file         main.c
* @brief        main
* @author       Gizwits
* @date         2018-07-19
* @version      V03030000
* @copyright    Gizwits
*
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值ֵ|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/
#include "gagent_soc.h"
#include "../Gizwits/gizwits_product.h"
#include "log.h"
#include "../driver/led/led.h"


#define QUERY_INTERVAL 5 //S

extern dataPoint_t currentDataPoint;

TX_TIMER *userTimer;

GPIO_MAP_TBL gpio_map_tbl[PIN_E_GPIO_MAX] = {
/* PIN NUM,     PIN NAME,    GPIO ID  GPIO FUNC */
	{  4, 		"GPIO01",  		23, 	 0},
	{  5, 		"GPIO02",  		20, 	 0},
	{  6, 		"GPIO03",  		21, 	 0},
	{  7, 		"GPIO04",  		22, 	 0},
	{ 18, 		"GPIO05",  		11, 	 0},
	{ 19, 		"GPIO06",  		10, 	 0},
	{ 22, 		"GPIO07",  		 9, 	 0},
	{ 23, 		"GPIO08",  	 	 8, 	 0},
	{ 26, 		"GPIO09",  		15, 	 0},
	{ 27, 		"GPIO10",  		12, 	 0},
	{ 28, 		"GPIO11",  		13, 	 0},
	{ 40, 		"GPIO19",  		19, 	 0},
	{ 41, 		"GPIO20",  		18, 	 0},
	{ 64, 		"GPIO21",  		07, 	 0},
};

/* gpio id table */
qapi_GPIO_ID_t gpio_id_tbl[PIN_E_GPIO_MAX];

/* gpio tlmm config table */
qapi_TLMM_Config_t tlmm_config[PIN_E_GPIO_MAX];
	
/* Modify this pin num which you want to test */
MODULE_PIN_ENUM  led_pin_num_motion ;
MODULE_PIN_ENUM  led_pin_num_Pulsesensor ;
MODULE_PIN_ENUM  led_pin_num_pressure ;

//led port
void led_init()
{
	   gizLog(LOG_INFO,"led initialization ...\n"); 
	   //led_pin_num_motion = PIN_E_GPIO_06;
	   //gpio_config(led_pin_num_motion, QAPI_GPIO_OUTPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_2MA_E);	//led for motion
	   
	   //led_pin_num_Pulsesensor = PIN_E_GPIO_07;
	   //gpio_config(led_pin_num_Pulsesensor, QAPI_GPIO_OUTPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_2MA_E);	
	   
	   led_pin_num_pressure = PIN_E_GPIO_09;						// motor pin;
	   gpio_config(led_pin_num_pressure, QAPI_GPIO_OUTPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_2MA_E);	
}

//heartrate sensor init (Pulsesensor)
void heartrate_init()
{
	gizLog(LOG_INFO,"Pulsesensor initialization ...\n"); 
	//Pulsesensor_init();
}

//temperature sensor init (QT18b20)
void temperature_init()
{
	gizLog(LOG_INFO,"QT18b20 initialization ...\n"); 
	//QT18b20_init();
}

//ADXL345 init
void motion_init()
{
	gizLog(LOG_INFO,"ADXL345 initialization ...\n"); 
	//adxl345_init();
}


void ICACHE_FLASH_ATTR userTimerCB(void)
{
	gizLog(LOG_INFO,"in userTimerCB.....\n"); 
    static uint8_t ctime = 0;
    static uint8_t ccount = 0;
    int8_t status = 0;
	
	uint32_t pressure = 80;		//压力
	uint32_t heartrate = 75;				//心跳
	int32_t X_axis_Value = 50;			//x轴
	int32_t Y_axis_Value = 60;
	int32_t Z_axis_Value = 70;
	
	gizLog(LOG_INFO,"before QUERY_INTERVAL....\n"); 
	if (QUERY_INTERVAL < ctime)
	{
			ctime = 0;
			
			//status = getHealthInfo(&bloodpressure, &heartbeat); 	//health info from Pulsesensor
			if( status )
			{
				gizLog(LOG_INFO,"get health info error\n"); 
				
			}
			currentDataPoint.valueHeartRateValue = heartrate;	
			//status = getaxis(&stepcount);					//data from ADXL345
			if( status )
			{
				gizLog(LOG_INFO,"get stepcount error\n"); 
					
			}
			currentDataPoint.valueX_axis_Value = X_axis_Value;
			currentDataPoint.valueY_axis_Value = Y_axis_Value;
			currentDataPoint.valueZ_axis_Value = Z_axis_Value;			
			//status = getPressValue(&pressure);		//data from pressure sensor
			if( status )
			{
				gizLog(LOG_INFO,"get pressure error\n"); 
			}
			currentDataPoint.valuePressure_Value = pressure;
			//数据上报
			gizLog(LOG_INFO,"begin to upload data\n"); 
			gizwitsHandle((dataPoint_t *)&currentDataPoint);
			gizLog(LOG_INFO,"currentDataPoint.valueHeartRateValue = %d, currentDataPoint.valueX_axis_Value = %d, currentDataPoint.valueY_axis_Value = %d, currentDataPoint.valueZ_axis_Value = %d, currentDataPoint.valuePressure_Value = %d,\n", 
			currentDataPoint.valueHeartRateValue, currentDataPoint.valueX_axis_Value,currentDataPoint.valueY_axis_Value,currentDataPoint.valueZ_axis_Value,currentDataPoint.valuePressure_Value);
			ccount++;
	}
    ctime++;  
}

void sensorInit(void)
{
    int32 ret = -1;
    
    gizLog(LOG_INFO,"Sensor initialization ...\n"); 

	led_init();							//led初始化（port）
	//heartrate_init();					//心率传感器初始化
	//temperature_init();				//温度传感器初始化
	//motion_init();						//运动传感器初始化
    txm_module_object_allocate(&userTimer, sizeof(TX_TIMER));
    ret = tx_timer_create(userTimer, "userTimer", userTimerCB, NULL, 1,
                          100, TX_AUTO_ACTIVATE);			
    if(ret != TX_SUCCESS)
    {
        gizLog(LOG_WARNING,"Failed to create UserTimer.\n");
    }
}


void gagentMain( void )
{
    getFreeHeap();
    sensorInit();
    gizwitsInit();
}
