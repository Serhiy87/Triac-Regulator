#ifndef PID_H
#define PID_H
#define  TD_PID_Tk 20
#include "stm32f1xx_hal.h"
typedef struct {
	int16_t Setpoint;
	int16_t Actual;
	int16_t Actual_Old;
	int16_t Output;
	int16_t P;
	int16_t I;
	int16_t D;
	int32_t Sum;
	int16_t Setpoint_old;
	uint16_t t_Pulse;
	int8_t Impulse;
} PID_RAM;

typedef struct {
	uint16_t Kp;
	uint16_t Ki;
	uint16_t Kd;
	uint16_t PBand;
	uint16_t Deadband;		//зона нечуствительности
	uint16_t Sample;
	uint16_t t_PulseMax;
	uint16_t t_PulseMin;

	uint8_t Timer;
	uint16_t ScaleFactor;
} PID_EEP;

static PID_RAM PID_Tk_RAM;
static PID_EEP PID_Tk_EEP = {
	20,		// Kp
	240,	// Ki
	0,		// Kd
	500,	// PBand
	0,		// Luft
	100,	// Sample
	0,		// t_PulseMin
	1000,	// t_PulseMax

	TD_PID_Tk,	// Timer
	10,			// ScaleFactor
};

void PID_Init(PID_RAM* const PID_R, const PID_EEP* const PID_E);
void PID(PID_RAM*  PID_R,  PID_EEP*  PID_E);
#endif
