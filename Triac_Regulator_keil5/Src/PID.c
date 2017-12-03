#include "PID.h"
#include "time.h"
#define erw(X) *(X)
#define erb(X) *(X)
void PID_Init(PID_RAM* const PID_R, const PID_EEP* const PID_E){
	//функция проводит инициализацию только если указатели коректные
	if(PID_R){
		PID_R->P = 0;
		PID_R->I = 0;
		PID_R->D = 0;
		PID_R->Actual_Old = PID_R->Actual;
		PID_R->Sum = 0;
		PID_R->Output = 0;
	}
	if(PID_E)ResetTimer16(erb(&PID_E->Timer));
}

void PID(PID_RAM*  PID_R,  PID_EEP*  PID_E){

	if( Timer16Stopp(erb(&PID_E->Timer)) ){
		// -------	In Deadband
		if( (( PID_R->Setpoint - (int16_t)erw(&PID_E->Deadband)) > PID_R->Actual ) ||
			( (PID_R->Setpoint + (int16_t)erw(&PID_E->Deadband)) < PID_R->Actual ) ||
			!erw(&PID_E->Deadband) ){
			int16_t Scale = (int16_t)erw(&PID_E->ScaleFactor);
			// -------	In Band
			if( (( PID_R->Setpoint - (int16_t)erw(&PID_E->PBand)) <= PID_R->Actual ) &&
				( (PID_R->Setpoint + (int16_t)erw(&PID_E->PBand)) >= PID_R->Actual ) ){

					StartTimer16(erb(&PID_E->Timer), erw(&PID_E->Sample));

					// ------ P
					float P =  0.01 * Scale *(int16_t)erw(&PID_E->Kp) * (PID_R->Setpoint - PID_R->Actual);
					if ( P > 10000 ) PID_R->P = 10000;
					if ( P < -10000 ) PID_R->P = -10000;
					if (( P > -10000) && ( P < 10000 )) PID_R->P = P;
					// ------ I
					if(Scale>=0){
						if ( ( ( PID_R->Output >= 1000 ) && ( PID_R->Setpoint > PID_R->Actual ) ) ||
							( ( PID_R->Output <= 0 ) && ( PID_R->Setpoint < PID_R->Actual ) ) ){}
						else{
							PID_R->Sum += PID_R->Setpoint - PID_R->Actual;
							float I =  0.0001 * Scale * (int16_t)erw(&PID_E->Kp) * PID_R->Sum  * erw(&PID_E->Sample) / (int16_t)erw(&PID_E->Ki);
							if ( I> 10000 ) PID_R->I = 10000;
							if ( I < -10000 ) PID_R->I = -10000;
							if (( I > -10000) && ( I < 10000 )) PID_R->I = I;
						}
					}
					if(Scale<0){
						if ( ( ( PID_R->Output >= 1000 ) && ( PID_R->Setpoint < PID_R->Actual ) ) ||
							( ( PID_R->Output <= 0 ) && ( PID_R->Setpoint > PID_R->Actual ) ) ){}
						else{
							PID_R->Sum += PID_R->Setpoint - PID_R->Actual;
							float I =  0.0001 * Scale * (int16_t)erw(&PID_E->Kp) * PID_R->Sum * erw(&PID_E->Sample) / (int16_t)erw(&PID_E->Ki);
							if ( I> 10000 ) PID_R->I = 10000;
							if ( I < -10000 ) PID_R->I = -10000;
							if (( I > -10000) && ( I < 10000 )) PID_R->I = I;
						}
					}
					// ------ D
					float D =  1.0 * Scale * (int16_t)erw(&PID_E->Kp) * (int16_t)erw(&PID_E->Kd) * (PID_R->Actual_Old - PID_R->Actual) / (float)erw(&PID_E->Sample);
					if ( D > 10000 ) PID_R->D = 10000;
					if ( D < -10000 ) PID_R->D = -10000;
					if (( D > -10000) && ( D < 10000 )) PID_R->D = D;
				// ------ PID Limit
					PID_R->Output = PID_R->P + PID_R->I + PID_R->D;
					if (PID_R->Output > 1000) PID_R->Output = 1000;
					if (PID_R->Output < 0) PID_R->Output = 0;
			}
			// -------	Lower Band
			if( PID_R->Actual < ( PID_R->Setpoint - (int16_t)erw(&PID_E->PBand) ) ){
				PID_Init(PID_R, PID_E);
				if(Scale > 0){
					PID_R->P = 1000;
					PID_R->Output = 1000;
				}
				else{
					PID_R->P = 0;
					PID_R->Output = 0;
				}
			}
			// -------	Higher Band
			if( PID_R->Actual > ( PID_R->Setpoint + (int16_t)erw(&PID_E->PBand) ) ){
				PID_Init(PID_R, PID_E);
				if(Scale < 0){
					PID_R->Output = 1000;
					PID_R->P = 1000;
				}
				else {
					PID_R->P = 0;
					PID_R->Output = 0;
				}
			}
		} //In Deadband
		PID_R->Actual_Old = PID_R->Actual;
	}//	if( Timer16Stopp(erb(&PID_F->Timer)) )
}
