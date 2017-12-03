#include "DS18B20.h"
#include "time.h"

extern uint8_t waitflg;
/* Private variables ---------------------------------------------------------*/
uint8_t ds_buff[2];                  //сюда принимаем данные 
uint8_t DS18B20_timer;
//*********************************************************************************************
//function  импульс сброса                                                                   //
//argument  маска порта                                                                      //
//return    0 - устройство обнаружен, 1 - не обнаружено, 2 - к.з. на линии                   //
//*********************************************************************************************
uint8_t ds_reset_pulse(uint16_t PinMask)
{
   uint16_t result;   
 
   if((PORT->IDR & PinMask)==0)  return 2;         //проверить линию на отсутствие замыкания
   PORT->ODR &= ~PinMask;                          //потянуть шину к земле
   TIMER->CNT=0;
   while(TIMER->CNT<480){};                        //ждать 480 микросекунд
   PORT->ODR |=  PinMask;                          //отпустить шину
   while(TIMER->CNT<550){};                        //ждать 70 микросекунд
   result =  PORT->IDR & PinMask;                 //прочитать шину 
   while(TIMER->CNT<960){};                        //дождаться окончания инициализации
   if(result) return 1;                            //датчик не обнаружен
   return 0;                                       //датчик обнаружен      
}

//*********************************************************************************************
//function  передача бита                                                                    //
//argument  значение передаваемого бита,маска порта                                          //
//return    none                                                                             //
//*********************************************************************************************
void ds_write_bit(uint8_t bit,uint16_t PinMask)
{
   TIMER->CNT=0;
   PORT->ODR &= ~PinMask;                          //потянуть шину к земле
   while(TIMER->CNT<2){};                          //ждать 1 микросекунду
   if(bit) PORT->ODR |=  PinMask;                  //если передаем 1, то отпускаем шину
   while(TIMER->CNT<60){};                         //задержка 60 микросекунд 
   PORT->ODR |=  PinMask;                          //отпускаем шину 
}

//*********************************************************************************************
//function  чтение бита                                                                      //
//argument  маска порта                                                                      //
//return    прочитанный бит                                                                  //
//*********************************************************************************************
uint16_t ds_read_bit(uint16_t PinMask)
{
   uint16_t result;
 
  TIMER->CNT=0;
   PORT->ODR &= ~PinMask;                          //потянуть шину к земле
   while(TIMER->CNT<2){};
   PORT->ODR |=  PinMask;                          //отпускаем шину  
   while(TIMER->CNT<15){};                         //задержка 15 микросекунд
   result     =  PORT->IDR & PinMask;              //прочитать шину
   while(TIMER->CNT<60){};                         //оставшееся время 
   return result;                                  //возвратить результат
}
//*********************************************************************************************
//function  запись байта                                                                     //
//argument  передаваемый байт,маска порта                                                    //
//return    none                                                                             //
//*********************************************************************************************
void ds_write_byte(uint8_t byte, uint16_t PinMask)
{
   uint8_t i;
   for(i=0;i<8;i++) ds_write_bit(byte&(1<<i), PinMask);
}
//*********************************************************************************************
//function  чтение байта                                                                     //
//argument  маска порта                                                                      //
//return    прочитанный байт                                                                 //
//*********************************************************************************************
uint8_t ds_read_byte(uint16_t PinMask)
{
   uint8_t i,result = 0;
   for(i=0;i<8;i++) 
   if(ds_read_bit(PinMask)) result |= 1<<i; 
   return result;
}
float celsius;
/*
float readTemperature(void){
	
	ds_reset_pulse(1<<PIN);          //послать импульс сброса                                       /
	ds_write_byte(SKIP_ROM_ADR,1<<PIN);//разрешить доступ к датчику не используя адрес
	ds_write_byte(CONVERT_TEMP,1<<PIN);      //запустить преобразование
	HAL_Delay (1000);               //дать время для измерения
	ds_reset_pulse(1<<PIN);          //послать импульс сброса              
	ds_write_byte(SKIP_ROM_ADR,1<<PIN);//разрешить доступ к датчику не используя адрес
	ds_write_byte(READ_DATA_COMAND,1<<PIN);      //команда, заставляющая датчик выдать 9 байт своей памяти
	waitflg=1;
	for(int i=0; i<2; i++ )ds_buff[i] = ds_read_byte(1<<PIN);          //прочитать 2 байт в массив
	waitflg=0;
	int16_t raw = (ds_buff[1]<<8)|ds_buff[0];
	celsius = (float)raw/16;
	celsius*=10;

	return celsius;
}
*/
float readTemperature(void){	
	return celsius;
};
uint8_t DS18B20_App(void){
	static uint8_t state = 0;
	switch(state){
		case 0:
			DS18B20_timer = Timer8Alloc();
			state = 1;
			break;
		case 1:
			ds_reset_pulse(1<<PIN);          //послать импульс сброса                                       /
			ds_write_byte(SKIP_ROM_ADR,1<<PIN);//разрешить доступ к датчику не используя адрес
			ds_write_byte(CONVERT_TEMP,1<<PIN);      //запустить преобразование
			StartTimer8(DS18B20_timer, 100);
		  state = 2;
			break;
		case 2:
			if(Timer8Stopp(DS18B20_timer))
			{
					ds_reset_pulse(1<<PIN);          //послать импульс сброса              
					ds_write_byte(SKIP_ROM_ADR,1<<PIN);//разрешить доступ к датчику не используя адрес
					ds_write_byte(READ_DATA_COMAND,1<<PIN);      //команда, заставляющая датчик выдать 9 байт своей памяти
					waitflg=1;
					for(int i=0; i<2; i++ )ds_buff[i] = ds_read_byte(1<<PIN);          //прочитать 2 байт в массив
					waitflg=0;
					int16_t raw = (ds_buff[1]<<8)|ds_buff[0];
					celsius = (float)raw/16;
					celsius*=10;
					state = 1;
			}
			break;
	}

}
