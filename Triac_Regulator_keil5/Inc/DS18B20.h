#ifndef DS18B20_H
#define DS18B20_H

#include "stm32f1xx_hal.h"

#define PORT  GPIOB   //указать порт, к которому подключены датчики
#define PIN 15
#define TIMER TIM3    //задаем таймер, используемый для формирования задержек
#define SKIP_ROM_ADR 0xCC // пропуск адресации
#define CONVERT_TEMP 0x44 // запускает преобразование температуры
#define READ_DATA_COMAND 0xBE //команда чтения содержимого памяти


float readTemperature(void);

#endif

