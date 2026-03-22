#include <LPC21xx.H>
#define LED0_bm 0x00010000
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000
#define BUT0_bm 0x00000010

void Delay(int iDelayInMs)
{
    int iLoopCounter;
    
    iDelayInMs = iDelayInMs * 2450;
    for(iLoopCounter = 0; iLoopCounter < iDelayInMs; iLoopCounter++){}
}

void LedInit(void)
{
	IO1DIR |= (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
	IO1SET = LED0_bm;
}

void LedOn(unsigned char ucLedIndeks)
{
	IO1CLR |= (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
	
	switch(ucLedIndeks)
	{
		case(0):
			IO1SET = LED0_bm;
			break;
		case(1):
			IO1SET = LED1_bm;
			break;
		case(2):
			IO1SET = LED2_bm;
			break;
		case(3):
			IO1SET = LED3_bm;
			break;
		default:
			break;
	}
}	

int ReadButton1(void)
{
	if((IO0PIN & BUT0_bm) == 0)
	{
		return 1;
	}
	else
	{
	return 0;
	}
}
	
int main()
{
	LedInit();
	
	while(1)
	{
		if (ReadButton1() == 1)
		{
			LedOn(1);
		}
		else
		{
			LedOn(0);
		}
	}
}

