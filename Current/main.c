#include <LPC21xx.H>
#define LED0_bm 0x00010000
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000

void Delay(int iDelayInMs)
{
    int iLoopCounter;
    
    iDelayInMs = iDelayInMs * 2450;
    for(iLoopCounter = 0; iLoopCounter < iDelayInMs; iLoopCounter++){}
}

int main()
{
  IO1DIR |= (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
  
	IO1SET = LED0_bm;
	IO1SET = LED1_bm;
	IO1SET = LED2_bm;
	IO1SET = LED3_bm;
	
	while(1){}
}
