#include <LPC21xx.H>

#include "servo.h"
#include "uart.h"
#include "command_decoder.h"
#include "timer_interrupts.h"
#include "keyboard.h"
#include "string.h"

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
            DecodeMsg(cOdebranaKomenda);
            
            if (ucTokenNr > 0 && asToken[0].eType == KEYWORD) 
            {
                switch (asToken[0].uValue.eKeyword) 
                {
                    case CAL:
                        ServoCallib();
                        break;
                        
                    case GT:
                        if (ucTokenNr > 1 && asToken[1].eType == NUMBER) 
                        {
                            ServoGoTo(asToken[1].uValue.uiNumber);
                        }
                        break;
                        
                    default:
                        break;
                }
            }
        }
    }
}
