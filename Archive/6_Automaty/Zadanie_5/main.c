#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

void Delay(int iDelayInMs)
{
    int iLoopCounter;
    
    iDelayInMs = iDelayInMs * 2450;
    for(iLoopCounter = 0; iLoopCounter < iDelayInMs; iLoopCounter++){}
}

enum LedState{STATE_START, STATE_STOP};
unsigned char ucStepCounter = 0;

int main()
{
	LedInit();
	KeyboardInit();
	enum LedState eLedState = STATE_START;
	
	while(1)
	{
		switch(eLedState)
		{
			case STATE_START:
			if(eKeyboardRead() == BUTTON_0)
			{
				eLedState = STATE_STOP;
			}
			else
			{
				LedStepRight();
				eLedState = STATE_START;
			}
			break;
			
			case STATE_STOP:
			if(eKeyboardRead() == BUTTON_1)
			{
				eLedState = STATE_START;
			}
			else
			{
				eLedState = STATE_STOP;
			}
		}
		Delay(250);		
	}
}
			
			
			
			
		
	
	
