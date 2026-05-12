#include <LPC21xx.H>
#include "led.h"
#include "timer_interrupts.h"
#include "keyboard.h"
#define Detector_Out_bm (1<<10)

enum DetectorState {ACTIVE, INACTIVE};
enum ServoState {CALLIB, IDLE, IN_PROGRESS};
enum ServoState eServoState = CALLIB;


void DetectorInit()
{
	IO0DIR = IO0DIR & (~(Detector_Out_bm));
}

enum DetectorState eReadDetector()
{
	if((IO0PIN & Detector_Out_bm) == 0)
	{
		return ACTIVE;
	}
	else
	{
		return INACTIVE;
	}
}

void Automat(void)
{
  
    enum LedState{CALLIB, STATE_LEFT, STATE_STOP, STATE_RIGHT}; 
    static enum LedState eLedState = CALLIB; 
    
    switch(eLedState)
    {
        case CALLIB:
            if(eReadDetector() == INACTIVE) {
                LedStepLeft(); 
            } else {
                eLedState = STATE_STOP; 
            }
            break;

        case STATE_STOP:
            if(eKeyboardRead() == BUTTON_0) eLedState = STATE_LEFT;
            else if(eKeyboardRead() == BUTTON_2) eLedState = STATE_RIGHT;
            break;
            
        case STATE_LEFT:
            if(eKeyboardRead() == BUTTON_1) eLedState = STATE_STOP;
            else LedStepLeft();
            break;
            
        case STATE_RIGHT:
            if(eKeyboardRead() == BUTTON_1) eLedState = STATE_STOP;
            else LedStepRight();
            break;
    }
}
 int main()
 {
	 LedInit();
	 DetectorInit();
	 KeyboardInit();
	 Timer0Interrupts_Init(6000, &Automat);
	 while(1)
	 {
		 
	 }
 }
	 
		
			
		
