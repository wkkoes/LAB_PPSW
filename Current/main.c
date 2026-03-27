#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

void Delay(int iDelayInMs)
{
    int iLoopCounter;
    
    iDelayInMs = iDelayInMs * 2450;
    for(iLoopCounter = 0; iLoopCounter < iDelayInMs; iLoopCounter++){}
}

int main()
{
	LedInit();
	KeyboardInit();
	
	while(1)
	{
		switch(eKeyboardRead())
		{
			case BUTTON_1:
				LedStepRight();
				Delay(250);
				break;
			
			case BUTTON_2:
				LedStepLeft();
				Delay(250);
				break;
			
			case RELEASED:
				break;
			
			default:
				break;
		}
	}
}
