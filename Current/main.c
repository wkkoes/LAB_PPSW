#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

void Delay(int iDelayInMs)
{
    int iLoopCounter;
    
    iDelayInMs = iDelayInMs * 2450;
    for(iLoopCounter = 0; iLoopCounter < iDelayInMs; iLoopCounter++){}
}

enum LedState{STATE_LEFT, STATE_STOP, STATE_RIGHT, STATE_HIGH, STATE_LOW};
unsigned char ucStepCounter = 0;

int main()
{
	LedInit();
	KeyboardInit();
	enum LedState eLedState = STATE_STOP;
	unsigned char ucBlinkCounter = 0;
	unsigned char ucTickCounter = 0;
	
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
			
			else if(eKeyboardRead() == BUTTON_3)
			{
				ucTickCounter = 0;
				ucBlinkCounter = 0;
				eLedState = STATE_HIGH;
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
			
			case STATE_HIGH:
			LedOn(0);	
			
			if(eKeyboardRead() == BUTTON_1)
				{
					eLedState = STATE_STOP;
				}
			
			else if(ucTickCounter < 3)
			{
				ucTickCounter++;
				eLedState = STATE_HIGH;
			}
			else
			{
				ucTickCounter = 0;
				eLedState = STATE_LOW;
			}
			break;
			
			case STATE_LOW:
			LedOn(5); //zgaszenie diody
			
			if(eKeyboardRead() == BUTTON_1)
			{
				eLedState = STATE_STOP;
				LedOn(0);
			}
			
			else if(ucTickCounter < 3)
			{
				ucTickCounter++;
				eLedState = STATE_LOW;
			}
			else
			{
				ucBlinkCounter++;
				ucTickCounter = 0;
				if(ucBlinkCounter < 5)
				{
					eLedState = STATE_HIGH;
				}
				else
				{
					ucBlinkCounter = 0;
					eLedState = STATE_RIGHT;
				}
			}
			
			break;
				
				
		}
		Delay(100);
	}
}
	
				
	
	
