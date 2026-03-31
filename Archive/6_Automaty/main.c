#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

void Delay(int iDelayInMs)
{
    int iLoopCounter;
    
    iDelayInMs = iDelayInMs * 2450;
    for(iLoopCounter = 0; iLoopCounter < iDelayInMs; iLoopCounter++){}
}

enum LedState{LED_LEFT, LED_RIGHT};

int main()
{
	LedInit();
	enum LedState eLedState = LED_LEFT;
	
	while(1)
	{
		switch(eLedState)
		{
			case LED_LEFT:
			LedStepLeft();
			eLedState = LED_RIGHT;
			break;
			
			case LED_RIGHT:
			LedStepRight();
			eLedState = LED_LEFT;
			break;
		}		
		Delay(250);
	}
}

