#include <LPC21xx.H>

void Delay(int iDelayInMs)
{
	int iLoopCounter;
	
	iDelayInMs = iDelayInMs * 2450;
	for(iLoopCounter = 0; iLoopCounter < iDelayInMs; iLoopCounter++){}
}
	
	
int main()
{
	IO1DIR = IO1DIR | 0x00010000;
		
while(1)
{
	IO1SET = 0x00010000;
	Delay(1);
	
	IO1CLR = 0x00010000;
	Delay(1);
}
}