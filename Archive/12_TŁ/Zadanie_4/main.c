#include <LPC21xx.H>

#include "servo.h"
#include "uart.h"
#include "command_decoder.h"
#include "timer_interrupts.h"
#include "keyboard.h"
#include "string.h"

int main(void)
{
		unsigned int uiCounter = 0;
		char cMsg[30];
	
    UART_InitWithInt(9600);
	
		while(1)
		{
			if(Transmiter_GetStatus() == FREE)
			{
				CopyString("licznik 0x", cMsg);
				AppendUIntToString(uiCounter, cMsg);
				Transmiter_SendString(cMsg);
				uiCounter++;
			}
		}
}
		
