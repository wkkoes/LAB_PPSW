#include <LPC21xx.H>

#define COUNTER_ENABLE_bm (1<<0) 
#define COUNTER_RESET_bm  (1<<1)

#define MR0I_bm (1<<0)
#define MR0R_bm (1<<1)
#define MR0S_bm (1<<2)

#define T0IR_bm (1<<0)


void InitTimer0(void)
{
    T0TCR |= COUNTER_ENABLE_bm;
}

void WaitOnTimer0(unsigned int uiTime)
{
    unsigned int uiTicksToWait = uiTime * 15;
    
    T0TCR |= COUNTER_RESET_bm;
    T0TCR &= ~COUNTER_RESET_bm;
    
    while(T0TC < uiTicksToWait)
    {
        
    }
}

void InitTimer0Match0(unsigned int iDelayTime)
{
	T0MR0 = iDelayTime * 15;
	
	T0MCR |= (MR0I_bm | MR0R_bm);
	
	T0TCR |= COUNTER_RESET_bm;
	T0TCR &= ~COUNTER_RESET_bm;
	T0TCR |= COUNTER_ENABLE_bm;
}

void WaitOnTimer0Match0(void)
{
	while((T0IR & T0IR_bm) == 0){}
	T0IR = T0IR_bm;
}



	
	
	
