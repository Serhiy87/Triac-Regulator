#ifndef TIME_H
#define TIME_H

#include "stm32f1xx_hal.h"



// ~~~~~~~~~~~~~~~~~~~~~~
// Program timers (10 ms)
// ~~~~~~~~~~~~~~~~~~~~~~
#ifndef Timer8_ISR_ApplNumber
#define Timer8_ISR_ApplNumber 0
#endif

#ifndef Timer8_ISR_ApplManuNumber
#define Timer8_ISR_ApplManuNumber 0
#endif

#ifndef Timer8ApplNumber
#define Timer8ApplNumber 0
#endif

#ifndef Timer16ApplNumber
#define Timer16ApplNumber 0
#endif

#ifndef Timer32ApplNumber
#define Timer32ApplNumber 0
#endif

#ifndef Timer8ApplManuNumber
#define Timer8ApplManuNumber 0
#endif

#ifndef Timer16ApplManuNumber
#define Timer16ApplManuNumber 0
#endif

#ifndef Timer32ApplManuNumber
#define Timer32ApplManuNumber 0
#endif

// Divisible by 8!
#define Timer8_ISR_TotNumber		(Timer8_ISR_ApplNumber  + 010)
#define Timer8TotNumber		(Timer8ApplNumber  + 030)
#define Timer16TotNumber	(Timer16ApplNumber + 030)
#define Timer32TotNumber	(Timer32ApplNumber + 010)



#define Timer8AllocErr()	(VacantTimer8>=Timer8ApplNumber)
#define Timer16AllocErr()	(VacantTimer16>=Timer16ApplNumber)
#define Timer32AllocErr()	(VacantTimer32>=Timer32ApplNumber)

// ~~~~~~~~~~~~~~
uint8_t Timer8_ISR_Alloc(void);
uint8_t Timer8Alloc(void);
uint8_t Timer16Alloc(void);
uint8_t Timer32Alloc(void);
uint8_t Timer8_ISR_AppAlloc(uint8_t n);
uint8_t Timer8AppAlloc(uint8_t n);
uint8_t Timer16AppAlloc(uint8_t n);
uint8_t Timer32AppAlloc(uint8_t n);
uint8_t Timer8_ISR_SysAlloc(uint8_t n);
uint8_t Timer8SysAlloc(uint8_t n);
uint8_t Timer16SysAlloc(uint8_t n);
uint8_t Timer32SysAlloc(uint8_t n);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void StartTimer8_ISR(uint8_t TimerN, uint8_t Timeout);
void StartTimer8(uint8_t TimerN, uint8_t Timeout);
void StartTimer16(uint8_t TimerN, uint16_t Timeout);
void StartTimer32(uint8_t TimerN, uint32_t Timeout);

// ~~~~~~~~~~~~~~~~~~~~~~~
void StopTimer8_ISR(uint8_t TimerN);
void StopTimer8(uint8_t TimerN);
void StopTimer16(uint8_t TimerN);
void StopTimer32(uint8_t TimerN);

// ~~~~~~~~~~~~~~~~~~~~~~~~
uint8_t Timer8Stopp_ISR(uint8_t TimerN);
uint8_t Timer8Stopp(uint8_t TimerN);
uint8_t Timer16Stopp(uint8_t TimerN);
uint8_t Timer32Stopp(uint8_t TimerN);

//~~~~~~~~~~~~~~~~~~~~~~~~~
void ResetTimer8_ISR(uint8_t TimerN);
void ResetTimer8(uint8_t TimerN);
void ResetTimer16(uint8_t TimerN);
void ResetTimer32(uint8_t TimerN);

// ~~~~~~~~~~~~~~~~~~~~~~
uint8_t GetTimer8_ISR(uint8_t TimerN);
uint8_t GetTimer8(uint8_t TimerN);
uint16_t GetTimer16(uint8_t TimerN);
uint32_t GetTimer32(uint8_t TimerN);

// ~~~~~~~~~~~~~~~~~~~~~~~
uint8_t TimerAllocError(void);


// ~~~~~~~~~~~
void TimeInit(void);
// ~~~~~~~~~~~~~~~~~~~~~

void SoftTimersCallback(void);
void TimersInc(void);

#endif

