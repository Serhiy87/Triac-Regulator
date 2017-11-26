#ifndef DYNAMIC_INDICATION_H
#define DYNAMIC_INDICATION_H

	#include "stm32f1xx_hal.h"
	//#include "main.h"
	//#include "stm32f103xb.h"
	#define ANODE1_GPIO 					GPIOB
	#define ANODE2_GPIO 					GPIOB
	#define ANODE3_GPIO 					GPIOB
	#define ANODE4_GPIO 					GPIOB
	#define ANODE1_GPIO_PIN 			GPIO_PIN_0
	#define ANODE2_GPIO_PIN 			GPIO_PIN_1
	#define ANODE3_GPIO_PIN 			GPIO_PIN_3
	#define ANODE4_GPIO_PIN 			GPIO_PIN_4
	#define CATHODE_A_GPIO 				GPIOB
	#define CATHODE_B_GPIO 				GPIOB
	#define CATHODE_C_GPIO 				GPIOB
	#define CATHODE_D_GPIO 				GPIOB
	#define CATHODE_E_GPIO 				GPIOB
	#define CATHODE_F_GPIO 				GPIOB
	#define CATHODE_G_GPIO 				GPIOB
	#define CATHODE_DP_GPIO 			GPIOB
	#define CATHODE_A_GPIO_PIN 		GPIO_PIN_5
	#define CATHODE_B_GPIO_PIN 		GPIO_PIN_6
	#define CATHODE_C_GPIO_PIN 		GPIO_PIN_7
	#define CATHODE_D_GPIO_PIN 		GPIO_PIN_8
	#define CATHODE_E_GPIO_PIN 		GPIO_PIN_9
	#define CATHODE_F_GPIO_PIN 		GPIO_PIN_10
	#define CATHODE_G_GPIO_PIN 		GPIO_PIN_11
	#define CATHODE_DP_GPIO_PIN 	GPIO_PIN_12
	

	void showValue(uint16_t value1);
	void ToggleLed(void);
	void setDigit(uint8_t digit, uint8_t value);
	void dynamicIndicationTickHandler(void);
#endif
