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

    T0PR = 14; //uzycie preskalera spowoduje ze licznik wieksza sie co 1us, wiec znacznie wolniej
		while(T0TC != uiTicksToWait) //timer moze pominac wartosc, petla while taktuje z inna czestotliwoscia niz timer
    {
	
    }
}

void InitTimer0Match0(unsigned int iDelayTime)
{
    T0MR0 = iDelayTime * 15; //wpisanie do rejestru Match Register wartosci porownania (us)

    T0MCR |= (MR0I_bm | MR0R_bm); //interrupt + reset, gdy TC osiagnie wartosc z MR

    T0TCR |= COUNTER_RESET_bm; //reset licznika timera
    T0TCR &= ~COUNTER_RESET_bm; //zakonczenie resetu timera
    T0TCR |= COUNTER_ENABLE_bm; //uruchomienie timera
}

void WaitOnTimer0Match0(void)
{
    while((T0IR & T0IR_bm) == 0){} //oczekiwanie na ustawienie flagi przerwania
    T0IR = T0IR | T0IR_bm; //wyzerowanie flagi, suma logiczna moze skasowac niezamierzone flagi
} 



	
	
	
