#include "servo.h"
#include "keyboard.h"
#include "led.h"
#include "uart.h"
#include "servo.h"

extern char cOdebranyZnak;

int main(void)
{
	
	UART_InitWithInt(9600);
	LedInit();
	ServoInit(150);
	
	while(1)
	{
		switch(cOdebranyZnak)
		{
			case '1':
				ServoGoTo(90);
				cOdebranyZnak = 0;
				break;
			
			case '2':
				ServoGoTo(180);
				cOdebranyZnak = 0;
				break;
			
			case '3':
				ServoGoTo(270);
				cOdebranyZnak = 0;
				break;
			
			case '4':
				ServoGoTo(600);
				cOdebranyZnak = 0;
				break;
			
			case 'c':
			case 'C':
				ServoCallib();
				cOdebranyZnak = 0;
				break;
			
			default:
				break;
		}
	}
}
