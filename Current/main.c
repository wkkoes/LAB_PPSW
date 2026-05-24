#include "servo.h"
#include "keyboard.h"
#include "led.h"
#include "uart.h"

extern char cOdebranyZnak;

int main(void)
{
	
	UART_InitWithInt(9600);
	LedInit();
	
	while(1)
	{
		switch(cOdebranyZnak)
		{
			case '1':
				LedOn(0);
				cOdebranyZnak = 0;
				break;
			
			case '2':
				LedOn(1);
				cOdebranyZnak = 0;
				break;
			
			case '3':
				LedOn(2);
				cOdebranyZnak = 0;
				break;
			
			case '4':
				LedOn(3);
				cOdebranyZnak = 0;
				break;
			
			case 'c':
			case 'C':
				LedOn(5);
				cOdebranyZnak = 0;
				break;
			
			default:
				break;
		}
	}
}
