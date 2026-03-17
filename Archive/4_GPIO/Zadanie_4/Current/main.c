#include <LPC21xx.H>

void Delay(void)
{
	int iLoopCounter;
	for(iLoopCounter = 0; iLoopCounter < 1000; iLoopCounter++){}
}
	
	
int main()
{
	IO1DIR = IO1DIR | 0x00010000;
		
while(1)
{
	IO1SET = 0x00010000;
	Delay();
	
	IO1CLR = 0x00010000;
	Delay();
}
}