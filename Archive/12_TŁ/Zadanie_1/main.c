#include <LPC21xx.H>

#include "servo.h"
#include "uart.h"
#include "command_decoder.h"
#include "timer_interrupts.h"
#include "keyboard.h"
#include "string.h"

int main(void)
{
    UART_InitWithInt(9600);
    
		U0THR = 0;
	
		while(1){}

}
