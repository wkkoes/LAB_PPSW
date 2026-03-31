#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

void Delay(int iDelayInMs)
{
    int iLoopCounter;
    
    iDelayInMs = iDelayInMs * 2450;
    for(iLoopCounter = 0; iLoopCounter < iDelayInMs; iLoopCounter++){}
}

enum LedState{STATE_IDLE, STATE_RIGHT};
unsigned char ucStepCounter = 0;

int main()
{
	LedInit();
	KeyboardInit();
	enum LedState eLedState = STATE_RIGHT;
	
	while(1)
	{
		switch(eLedState)
		{
			case STATE_IDLE:
			if(eKeyboardRead() == BUTTON_0)
			{
				eLedState = STATE_RIGHT;
			}
			else
			{
				eLedState = STATE_IDLE;
			}
			break;
			
			case STATE_RIGHT:
			if(ucStepCounter < 2)
			{
				LedStepRight();
				ucStepCounter++;
				eLedState = STATE_RIGHT;
			}
			else
			{
				LedStepRight();
				ucStepCounter = 0;
				eLedState = STATE_IDLE;
			}
			break;
		}
		Delay(250);
	}
}
			
			
			
			
		
	
	
