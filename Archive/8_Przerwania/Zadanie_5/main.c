#include "led.h"
#include "timer_interrupts.h"
#include "keyboard.h"

void Automat(void)
{
	enum LedState{STATE_LEFT, STATE_STOP, STATE_RIGHT};
	static enum LedState eLedState = STATE_STOP;
	
	switch(eLedState)
	{
		{
        case STATE_STOP:
            if(eKeyboardRead() == BUTTON_0)
            {
                eLedState = STATE_LEFT;
            }
            else if(eKeyboardRead() == BUTTON_2)
            {
                eLedState = STATE_RIGHT;
            }
            else
            {
                eLedState = STATE_STOP;
            }
            break;
            
        case STATE_LEFT:
            if(eKeyboardRead() == BUTTON_1)
            {
                eLedState = STATE_STOP;
            }
            else
            {
                LedStepLeft();
                eLedState = STATE_LEFT;
            }
            break;
            
        case STATE_RIGHT:
            if(eKeyboardRead() == BUTTON_1)
            {
                eLedState = STATE_STOP;
            }
            else
            {
                LedStepRight();
                eLedState = STATE_RIGHT;
            }
            break;
    }
	}
}	

int main (){
	unsigned int iMainLoopCtr = 0;
	LedInit();
	KeyboardInit();
	Timer0Interrupts_Init(20000, &Automat);

	while(1){
	 	iMainLoopCtr++;
	}
}
