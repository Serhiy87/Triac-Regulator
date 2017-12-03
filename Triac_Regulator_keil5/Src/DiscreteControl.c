#include "LED.h"
#include "time.h"
	uint8_t POWER_timer, _10SEC_timer;
	

	void POWER_On(){
		HAL_GPIO_WritePin(LED_GPIO,LED_GPIO_PIN,GPIO_PIN_RESET);
	}
	
	void POWER_Off(){
		HAL_GPIO_WritePin(LED_GPIO,LED_GPIO_PIN,GPIO_PIN_SET);
	}
	uint8_t POWERstate = 0;
	void POWER_App(float setPoint){
	static uint8_t state = 0;
POWERstate = state;
		switch(state){
		case 0:
			POWER_timer  = Timer16Alloc();
			_10SEC_timer = Timer16Alloc();
			state = 1;
			break;
		case 1:
			if((uint16_t)setPoint!=0){
				StartTimer16(POWER_timer,(uint16_t)setPoint);
				StartTimer16(_10SEC_timer,1000);
				POWER_On();
				state = 2;
			}
			break;
		case 2:
			if(Timer16Stopp(POWER_timer)){
				POWER_Off();
			}
			if(Timer16Stopp(_10SEC_timer)){
			state = 1;
			}
			break;
		
		}
	}

	