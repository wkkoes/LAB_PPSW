#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

void Delay(int iDelayInMs)
{
    int iLoopCounter;
    
    iDelayInMs = iDelayInMs * 2450;
    for(iLoopCounter = 0; iLoopCounter < iDelayInMs; iLoopCounter++){}
}

enum LedState{STATE0, STATE1, STATE2, STATE3, STATE4, STATE5};

int main()
{
	LedInit();
	enum LedState eLedState = STATE3;
	
	while(1)
	{
		switch(eLedState)
		{
			case STATE0:
			LedStepRight();
			eLedState = STATE1;
			break;
			
			case STATE1:
			LedStepRight();
			eLedState = STATE2;
			break;
			
			case STATE2:
			LedStepRight();
			eLedState = STATE3;
			break;
			
			case STATE3:
			LedStepLeft();
			eLedState = STATE4;
			break;
			
			case STATE4:
			LedStepLeft();
			eLedState = STATE5;
			break;
			
			case STATE5:
			LedStepLeft();
			eLedState = STATE0;
			break;
		}
		Delay(250);
	}
}
				
	
	
