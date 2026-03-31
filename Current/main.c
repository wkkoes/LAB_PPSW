#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

void Delay(int iDelayInMs)
{
    int iLoopCounter;
    
    iDelayInMs = iDelayInMs * 2450;
    for(iLoopCounter = 0; iLoopCounter < iDelayInMs; iLoopCounter++){}
}

enum LedState{STATE_LEFT, STATE_STOP, STATE_RIGHT};
unsigned char ucStepCounter = 0;

int main()
{
	LedInit();
	KeyboardInit();
	enum LedState eLedState = STATE_STOP;
	
	while(1)
	{
		switch(eLedState)
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
		Delay(100);
	}
}
	
				
	
	
