#ifndef POWER_H
#define POWER_H

#include "stm32f1xx_hal.h"

	#define POWER_GPIO 					GPIOC
	#define POWER_GPIO_PIN 		  GPIO_PIN_13
	
	void POWER_On(void);
	void POWER_Off(void);
	void POWER_App(float setPoint);

#endif

