#include "led.h"
#include "timer_interrupts.h"
int main (){
	unsigned int iMainLoopCtr = 0;
	LedInit();
	Timer0Interrupts_Init(250000, &LedStepLeft);

	while(1){
	 	iMainLoopCtr++;
	}
}
