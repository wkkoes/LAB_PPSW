#include <LPC21xx.H>

#include "servo.h"
#include "uart.h"


int main(void)
{
    char cOdebranaKomenda[RECEIVER_SIZE]; 
	
    UART_InitWithInt(9600);
    ServoInit(150);
	
    while(1)
    {
        if (eReceiver_GetStatus() == READY) 
        {
            
            Receiver_GetStringCopy(cOdebranaKomenda);
            
            
            if (cOdebranaKomenda[0] == 'c' && cOdebranaKomenda[1] == 'a' && 
                cOdebranaKomenda[2] == 'l' && cOdebranaKomenda[3] == 'l' && 
                cOdebranaKomenda[4] == 'i' && cOdebranaKomenda[5] == 'b' && 
                cOdebranaKomenda[6] == '\0') 
            {
                ServoCallib();
            }
            
            else if (cOdebranaKomenda[0] == 'l' && cOdebranaKomenda[1] == 'e' && 
                     cOdebranaKomenda[2] == 'f' && cOdebranaKomenda[3] == 't' && 
                     cOdebranaKomenda[4] == '\0') 
            {
                ServoGoTo(50);
            }
            
            else if (cOdebranaKomenda[0] == 'r' && cOdebranaKomenda[1] == 'i' && 
                     cOdebranaKomenda[2] == 'g' && cOdebranaKomenda[3] == 'h' && 
                     cOdebranaKomenda[4] == 't' && cOdebranaKomenda[5] == '\0') 
            {
                ServoGoTo(150);
            }
        }
    }
}
