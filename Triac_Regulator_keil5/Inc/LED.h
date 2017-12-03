#ifndef LED_H
#define LED_H

#include "stm32f1xx_hal.h"

	#define LED_GPIO 					GPIOC
	#define LED_GPIO_PIN 		  GPIO_PIN_13
	
	void LED_On(void);
	void LED_Off(void);
	void LED_App(void);

#endif

