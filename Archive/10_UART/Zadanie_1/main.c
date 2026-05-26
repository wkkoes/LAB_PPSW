#include "servo.h"
#include "keyboard.h"
#include "led.h"
#include "uart.h"
#include "servo.h"

extern char cOdebranyZnak;

int main(void)
{
	unsigned int uiZadanaPozycja = 0;
	
	UART_InitWithInt(9600);
	LedInit();
	ServoInit(155);
	
	while(1)
	{
		switch(cOdebranyZnak)
		{
			case '1':
				uiZadanaPozycja = uiZadanaPozycja + 50;
				ServoGoTo(uiZadanaPozycja);
				cOdebranyZnak = 0;
				break;
			
			case 'c':
			case 'C':
				ServoCallib();
				uiZadanaPozycja  = 0;
				cOdebranyZnak = 0;
				break;
			
			default:
				break;
		}
	}
}
