#include "time.h"

static volatile uint8_t TickCounter;

volatile static uint8_t		Timer8_ISR[Timer8_ISR_TotNumber];
volatile static uint8_t		Timer8[Timer8TotNumber];
volatile static uint16_t	Timer16[Timer16TotNumber];
volatile static uint32_t	Timer32[Timer32TotNumber];

volatile static uint8_t Timer8_ISR_Flg[Timer8_ISR_TotNumber/8+1];
volatile static uint8_t Timer8Flg[Timer8TotNumber/8+1];
volatile static uint8_t Timer16Flg[Timer16TotNumber/8+1];
volatile static uint8_t Timer32Flg[Timer32TotNumber/8+1];

static uint8_t VacantTimer8_ISR=Timer8_ISR_ApplManuNumber;
static uint8_t VacantTimer8Sys_ISR=Timer8_ISR_ApplNumber;

static uint8_t VacantTimer8=Timer8ApplManuNumber, VacantTimer16=Timer16ApplManuNumber, VacantTimer32=Timer32ApplManuNumber;
static uint8_t VacantTimer8Sys=Timer8ApplNumber, VacantTimer16Sys=Timer16ApplNumber, VacantTimer32Sys=Timer32ApplNumber;
// ~~~~~~~~~~~~~~
uint8_t
Timer8_ISR_Alloc(void)
{
	uint8_t N = VacantTimer8_ISR;
	VacantTimer8_ISR++;
	return N;
}

uint8_t
Timer8Alloc(void)
{
	uint8_t N = VacantTimer8;
	VacantTimer8++;
	return N;
}

// ~~~~~~~~~~~~~~~
uint8_t
Timer16Alloc(void)
{
	uint8_t N = VacantTimer16;
	VacantTimer16++;
	return N;
}

// ~~~~~~~~~~~~~~~
uint8_t
Timer32Alloc(void)
{
	uint8_t N = VacantTimer32;
	VacantTimer32++;
	return N;
}
// ~~~~~~~~~~~~~~

uint8_t
Timer8_ISR_AppAlloc(uint8_t n)
{
	if(n==0)return 0;
	uint8_t N = VacantTimer8_ISR;
	VacantTimer8_ISR+=n;
	return N;
}

uint8_t
Timer8AppAlloc(uint8_t n)
{
	if(n==0)return 0;
	uint8_t N = VacantTimer8;
	VacantTimer8+=n;
	return N;
}

// ~~~~~~~~~~~~~~~
uint8_t
Timer16AppAlloc(uint8_t n)
{
	if(n==0)return 0;
	uint8_t N = VacantTimer16;
	VacantTimer16+=n;
	return N;
}

// ~~~~~~~~~~~~~~~
uint8_t
Timer32AppAlloc(uint8_t n)
{
	if(n==0)return 0;
	uint8_t N = VacantTimer32;
	VacantTimer32+=n;
	return N;
}

// ~~~~~~~~~~~~~~~~~~~~~~
uint8_t
Timer8_ISR_SysAlloc(uint8_t n)
{
	uint8_t N = VacantTimer8Sys_ISR;
	VacantTimer8Sys_ISR += n;
	return N;
}

uint8_t
Timer8SysAlloc(uint8_t n)
{
	uint8_t N = VacantTimer8Sys;
	VacantTimer8Sys += n;
	return N;
}

// ~~~~~~~~~~~~~~~~~~~~~~~
uint8_t
Timer16SysAlloc(uint8_t n)
{
	uint8_t N = VacantTimer16Sys;
	VacantTimer16Sys += n;
	return N;
}

// ~~~~~~~~~~~~~~~~~~~~~~~
uint8_t
Timer32SysAlloc(uint8_t n)
{
	uint8_t N = VacantTimer32Sys;
	VacantTimer32Sys += n;
	return N;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
StartTimer8_ISR(uint8_t TimerN, uint8_t Timeout)
{
//	IntOff();
	if ((Timer8_ISR[TimerN]=Timeout)>0)
		Timer8_ISR_Flg[TimerN/8] &=~(1<<TimerN%8);
	else
		Timer8_ISR_Flg[TimerN/8] |=(1<<TimerN%8);
//	IntOn();
}


void
StartTimer8(uint8_t TimerN, uint8_t Timeout)
{
//	IntOff();
	if ((Timer8[TimerN]=Timeout)>0)
		Timer8Flg[TimerN/8] &=~(1<<TimerN%8);
	else
		Timer8Flg[TimerN/8] |=(1<<TimerN%8);
//	IntOn();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
StartTimer16(uint8_t TimerN, uint16_t Timeout)
{
//	IntOff();
	if ((Timer16[TimerN]=Timeout)>0)
		Timer16Flg[TimerN/8] &=~(1<<TimerN%8);
	else
		Timer16Flg[TimerN/8] |=(1<<TimerN%8);
//	IntOn();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
StartTimer32(uint8_t TimerN, uint32_t Timeout)
{
//	IntOff();
	if ((Timer32[TimerN]=Timeout)>0)
		Timer32Flg[TimerN/8] &=~(1<<TimerN%8);
	else
		Timer32Flg[TimerN/8] |=(1<<TimerN%8);
//	IntOn();
}

// ~~~~~~~~~~~~~~~~~~~~~~~
void
StopTimer8_ISR(uint8_t TimerN)
{
//	IntOff();
	Timer8_ISR_Flg[TimerN/8] |=(1<<TimerN%8);
//	IntOn();
}

void
StopTimer8(uint8_t TimerN)
{
//	IntOff();
	Timer8Flg[TimerN/8] |=(1<<TimerN%8);
//	IntOn();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~
void
StopTimer16(uint8_t TimerN)
{
//	IntOff();
	Timer16Flg[TimerN/8] |=1<<TimerN%8;
//	IntOn();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~
void
StopTimer32(uint8_t TimerN)
{
//	IntOff();
	Timer32Flg[TimerN/8] |=1<<TimerN%8;
//	IntOn();
}
// ~~~~~~~~~~~~~~~~~~~~~~~~
uint8_t
Timer8Stopp_ISR(uint8_t TimerN)
{
	return (Timer8_ISR_Flg[TimerN/8] &(1<<TimerN%8)) && Timer8_ISR[TimerN]==0;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~
uint8_t
Timer8Stopp(uint8_t TimerN)
{
	return (Timer8Flg[TimerN/8] &(1<<TimerN%8)) && Timer8[TimerN]==0;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~
uint8_t
Timer16Stopp(uint8_t TimerN)
{
//	IntOff();
	uint8_t T_S = (Timer16Flg[TimerN/8] &(1<<TimerN%8)) && Timer16[TimerN]==0;
//	IntOn();
	return T_S;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~
uint8_t
Timer32Stopp(uint8_t TimerN)
{
//	IntOff();
	uint8_t T_S = (Timer32Flg[TimerN/8] &(1<<TimerN%8)) && Timer32[TimerN]==0;
//	IntOn();
	return T_S;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~
void
ResetTimer8_ISR(uint8_t TimerN)
{
//	IntOff();
	Timer8_ISR_Flg[TimerN/8] |=(1<<TimerN%8);
//	IntOn();
	Timer8_ISR[TimerN] = 0;
}

void
ResetTimer8(uint8_t TimerN)
{
//	IntOff();
	Timer8Flg[TimerN/8] |=(1<<TimerN%8);
//	IntOn();
	Timer8[TimerN] = 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~
void
ResetTimer16(uint8_t TimerN)
{
//	IntOff();
	Timer16Flg[TimerN/8] |=1<<TimerN%8;
	Timer16[TimerN] = 0;
//	IntOn();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~
void
ResetTimer32(uint8_t TimerN)
{
//	IntOff();
	Timer32Flg[TimerN/8] |=1<<TimerN%8;
	Timer32[TimerN] = 0;
//	IntOn();
}

// ~~~~~~~~~~~~~~~~~~~~~~
uint8_t
GetTimer8_ISR(uint8_t TimerN)
{
	return Timer8_ISR[TimerN];
}
uint8_t
GetTimer8(uint8_t TimerN)
{
	return Timer8[TimerN];
}

// ~~~~~~~~~~~~~~~~~~~~~~~
uint16_t
GetTimer16(uint8_t TimerN)
{
//	IntOff();
	uint16_t Time = Timer16[TimerN];
//	IntOn();
	return Time;
}

// ~~~~~~~~~~~~~~~~~~~~~~~
uint32_t
GetTimer32(uint8_t TimerN)
{
	//IntOff();
	uint32_t Time = Timer32[TimerN];
	//IntOn();
	return Time;
}
// ~~~~~~~~~~~~~~~~~~~~~~~
uint8_t TimerAllocError(void){
	return ( (VacantTimer8Sys >=  Timer8TotNumber) || (VacantTimer16Sys >=  Timer16TotNumber) || (VacantTimer32Sys >=  Timer32TotNumber) ||
		 Timer8AllocErr() || Timer16AllocErr() || Timer32AllocErr() );
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Total
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static uint8_t TD_Scan;
uint8_t ScanCycle, MaxScanCycle;

#ifdef HIGH_SPEED_COUNTER
	extern inline void HSC_Process(void);
#endif

// ~~~~~~~~~~~
void
TimeInit(void)
{


	// Program timers (10 ms)
	uint8_t i;
	for (i=0; i<sizeof(Timer8Flg); i++)
		Timer8Flg[i] = 0xFF;
	for (i=0; i<sizeof(Timer16Flg); i++)
		Timer16Flg[i] = 0xFF;
	for (i=0; i<sizeof(Timer32Flg); i++)
		Timer32Flg[i] = 0xFF;

	// Application
	#ifdef InitTimer
		StartTimer16(InitTimer, InitTime);
	#endif
}

// ~~~~~~~~~~~~~~~~
void
ScanCycleInit(void)
{
	TD_Scan = Timer8SysAlloc(1);
	StartTimer8(TD_Scan, 0xFF);
}



void SoftTimersCallback(void){
	TickCounter++;
	uint8_t i;
	for (i=0; i<Timer8_ISR_TotNumber; i++)
			if (!(Timer8_ISR_Flg[i/8] &(1<<i%8)) && --Timer8_ISR[i]==0)
				Timer8_ISR_Flg[i/8] |=(1<<i%8);

}
void 
TimersInc(void)
{
	uint8_t i, TickCounterVar;	
	//cli();
	TickCounterVar = TickCounter;
	TickCounter = 0;
	//sei();
	for(uint8_t j=0;j<TickCounterVar;j++){

	 	for (i=0; i<Timer8TotNumber; i++){
	//		cli();
			if (!(Timer8Flg[i/8] &(1<<i%8)) && --Timer8[i]==0)
				Timer8Flg[i/8] |=(1<<i%8);
		//	sei();
		}
		for (i=0; i<Timer16TotNumber; i++){
			//cli();
			if (!(Timer16Flg[i/8] &(1<<i%8)) && --Timer16[i]==0)
				Timer16Flg[i/8] |=(1<<i%8);
			//sei();
		}
		for (i=0; i<Timer32TotNumber; i++){
			//cli();
			if (!(Timer32Flg[i/8] &(1<<i%8)) && --Timer32[i]==0)
				Timer32Flg[i/8] |=(1<<i%8);	
			//sei();
		}
	}
}


