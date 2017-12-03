#include "LED.h"
#include "time.h"
	uint8_t LED_timer;
	

	void LED_On(){
		HAL_GPIO_WritePin(LED_GPIO,LED_GPIO_PIN,GPIO_PIN_RESET);
	}
	
	void LED_Off(){
		HAL_GPIO_WritePin(LED_GPIO,LED_GPIO_PIN,GPIO_PIN_SET);
	}
	
	void LED_App(void){
	static uint8_t state = 0;
		static uint8_t LED_state = 0;
		switch(state){
		case 0:
			LED_timer = Timer16Alloc();
			StartTimer16(LED_timer, 1000);
			state = 1;
			break;
		case 1:
				if(Timer16Stopp(LED_timer)){
					if(LED_state==1){
						LED_Off();
						LED_state = 0;
					}
					else{
						LED_On();
						LED_state = 1;					
					}
					StartTimer16(LED_timer, 1000);
				}
			break;
		}
	}
	