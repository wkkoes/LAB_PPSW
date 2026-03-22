#include <LPC21xx.H>
#define LED3_bm 0x00080000

void Delay(int iDelayInMs)
{
    int iLoopCounter;
    
    iDelayInMs = iDelayInMs * 2450;
    for(iLoopCounter = 0; iLoopCounter < iDelayInMs; iLoopCounter++){}
}

int main()
{
  IO1DIR |= LED3_bm;
  
	while(1)
	{
		IO1SET = LED3_bm;
    Delay(50);
		
		IO1CLR = LED3_bm;
    Delay(50);
    }
}
