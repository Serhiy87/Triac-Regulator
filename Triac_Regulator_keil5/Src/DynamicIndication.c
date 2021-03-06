#include "DynamicIndication.h"

uint16_t numAraay[]={
	{CATHODE_A_GPIO_PIN|CATHODE_B_GPIO_PIN|CATHODE_C_GPIO_PIN|CATHODE_D_GPIO_PIN|CATHODE_E_GPIO_PIN|CATHODE_F_GPIO_PIN},
	{CATHODE_B_GPIO_PIN|CATHODE_C_GPIO_PIN},
	{CATHODE_A_GPIO_PIN|CATHODE_B_GPIO_PIN|CATHODE_G_GPIO_PIN|CATHODE_E_GPIO_PIN|CATHODE_D_GPIO_PIN},
	{CATHODE_A_GPIO_PIN|CATHODE_B_GPIO_PIN|CATHODE_G_GPIO_PIN|CATHODE_C_GPIO_PIN|CATHODE_D_GPIO_PIN},
	{CATHODE_B_GPIO_PIN|CATHODE_C_GPIO_PIN|CATHODE_G_GPIO_PIN|CATHODE_F_GPIO_PIN},
	{CATHODE_A_GPIO_PIN|CATHODE_F_GPIO_PIN|CATHODE_G_GPIO_PIN|CATHODE_C_GPIO_PIN|CATHODE_D_GPIO_PIN},
	{CATHODE_A_GPIO_PIN|CATHODE_C_GPIO_PIN|CATHODE_D_GPIO_PIN|CATHODE_E_GPIO_PIN|CATHODE_G_GPIO_PIN|CATHODE_F_GPIO_PIN},
	{CATHODE_A_GPIO_PIN|CATHODE_B_GPIO_PIN|CATHODE_C_GPIO_PIN},
	{CATHODE_A_GPIO_PIN|CATHODE_B_GPIO_PIN|CATHODE_C_GPIO_PIN|CATHODE_D_GPIO_PIN|CATHODE_E_GPIO_PIN|CATHODE_F_GPIO_PIN|CATHODE_G_GPIO_PIN},
	{CATHODE_A_GPIO_PIN|CATHODE_B_GPIO_PIN|CATHODE_C_GPIO_PIN|CATHODE_D_GPIO_PIN|CATHODE_F_GPIO_PIN|CATHODE_G_GPIO_PIN},
};


GPIO_TypeDef* digitsGPIO_Array[]={
	ANODE1_GPIO,
	ANODE2_GPIO,
	ANODE3_GPIO,
	ANODE4_GPIO,
};

uint16_t digitsArray[]={
	ANODE1_GPIO_PIN,
	ANODE2_GPIO_PIN,
	ANODE3_GPIO_PIN,
	ANODE4_GPIO_PIN,
};

void ToggleLed(){};
void setDigit(uint8_t digit, uint8_t value){
	HAL_GPIO_WritePin(CATHODE_A_GPIO,CATHODE_A_GPIO_PIN|CATHODE_B_GPIO_PIN|CATHODE_C_GPIO_PIN|CATHODE_D_GPIO_PIN|CATHODE_E_GPIO_PIN|CATHODE_F_GPIO_PIN|CATHODE_G_GPIO_PIN|CATHODE_DP_GPIO_PIN,GPIO_PIN_SET);
	HAL_GPIO_WritePin(CATHODE_A_GPIO,ANODE1_GPIO_PIN|ANODE2_GPIO_PIN|ANODE3_GPIO_PIN|ANODE4_GPIO_PIN,GPIO_PIN_RESET);
	if(digit==3)HAL_GPIO_WritePin(CATHODE_A_GPIO,CATHODE_DP_GPIO_PIN,GPIO_PIN_RESET);
	if(digit!=1){
	HAL_GPIO_WritePin(digitsGPIO_Array[0],numAraay[value],GPIO_PIN_RESET);
	HAL_GPIO_WritePin(digitsGPIO_Array[0],digitsArray[digit-1],GPIO_PIN_SET);}
};
uint16_t value = 0;
void showValue(uint16_t value1){
value = value1;
}

void dynamicIndicationTickHandler(void){
	static uint8_t state = 0;
	static uint16_t counter=0;
	static uint8_t currentDigit=4;
	static uint16_t currentValue = 0;
	switch(state){
		case 0:
			setDigit(currentDigit, currentValue%10);
			currentValue = currentValue/10;		
			state = 1;
			break;
		case 1:
			counter++;
			if(counter == 1){
				currentDigit--;
				if(currentDigit==0){
					currentDigit = 4;
					currentValue = value;
				}
				counter=0;
				state = 0;				
			}
			break;
	}

}
