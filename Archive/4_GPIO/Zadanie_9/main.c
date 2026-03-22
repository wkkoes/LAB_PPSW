#include <LPC21xx.H>
#define LED0_bm 0x00010000

void Delay(int iDelayInMs)
{
    int iLoopCounter;
    
    iDelayInMs = iDelayInMs * 2450;
    for(iLoopCounter = 0; iLoopCounter < iDelayInMs; iLoopCounter++){}
}

int main()
{
  IO1DIR |= LED0_bm;
  
	while(1)
	{
		IO1SET = LED0_bm;
    Delay(50);
		
		IO1CLR = LED0_bm;
    Delay(50);
    }
}
