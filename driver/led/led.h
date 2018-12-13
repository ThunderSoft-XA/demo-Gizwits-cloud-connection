/******************************************************************************
*@file    motor.h
*@brief   example of led operation
*
*  ---------------------------------------------------------------------------
*
*  Copyright (c) 2018 Quectel Technologies, Inc.
*  All Rights Reserved.
*  Confidential and Proprietary - Quectel Technologies, Inc.
*  ---------------------------------------------------------------------------
*******************************************************************************/
#ifndef __LED_H__
#define __LED_H__

#include "quectel_gpio.h"

void ledsetvalue(uint8_t ledvalue);
void gpio_config(MODULE_PIN_ENUM m_pin,qapi_GPIO_Direction_t gpio_dir,qapi_GPIO_Pull_t gpio_pull,qapi_GPIO_Drive_t gpio_drive);

#endif
