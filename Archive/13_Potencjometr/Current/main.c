#include <LPC21xx.H>

#include "servo.h"
#include "uart.h"
#include "command_decoder.h"
#include "timer_interrupts.h"
#include "keyboard.h"
#include "string.h"

void ADC_Init(void)
{
	PINSEL1 |= (1 << 24);
	PINSEL1 &= ~(1 << 25);
	
	ADCR = (1 << 1) | (4 << 8) | (1 << 21);
}

unsigned int ADC_Read(void)
{
	ADCR |= (1 << 24);
	while ((ADDR & (1UL << 31)) == 0){}
	return (ADDR >> 6) & 0x3FF;
}

int main()
{
	ServoInit(50);
	ADC_Init();
	
	while(1)
	{
		unsigned int uiWartoscPot = ADC_Read();
		unsigned int uiPozycjaServo = (uiWartoscPot * 48) / 1023;
		ServoGoTo(uiPozycjaServo);
	}
}
