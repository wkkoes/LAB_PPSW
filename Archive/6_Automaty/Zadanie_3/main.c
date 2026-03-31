#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

void Delay(int iDelayInMs)
{
    int iLoopCounter;
    
    iDelayInMs = iDelayInMs * 2450;
    for(iLoopCounter = 0; iLoopCounter < iDelayInMs; iLoopCounter++){}
}

enum LedState{STATE_LEFT, STATE_RIGHT};
unsigned char ucStepCounter = 0;

int main()
{
	LedInit();
	enum LedState eLedState = STATE_LEFT;
	
	while(1)
	{
		switch(eLedState)
		{
			case STATE_LEFT:
			LedStepLeft();
			ucStepCounter++;
			if(ucStepCounter >= 3)
			{
				eLedState = STATE_RIGHT;
				ucStepCounter = 0;
			}
			break;
			
			case STATE_RIGHT:
			LedStepRight();
			ucStepCounter++;
			if(ucStepCounter >=3)
			{
				eLedState = STATE_LEFT;
				ucStepCounter = 0;
			}
			break;
		}
		Delay(250);
	}
}
				
			
		
	
	
