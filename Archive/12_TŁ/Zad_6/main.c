#include <LPC21xx.H>

#include "servo.h"
#include "uart.h"
#include "command_decoder.h"
#include "timer_interrupts.h"
#include "keyboard.h"
#include "string.h"

struct Watch
{
    unsigned char ucMinutes; 
    unsigned char ucSecconds;
    unsigned char fSeccondsValueChanged;
    unsigned char fMinutesValueChanged;
};

struct Watch sWatch = {0,0,0,0};

void WatchUpdate(void)
{
    sWatch.ucSecconds++;
    sWatch.fSeccondsValueChanged = 1;
    
    if(sWatch.ucSecconds >= 60)
    {
        sWatch.ucSecconds = 0;
        sWatch.ucMinutes++;
        sWatch.fMinutesValueChanged = 1;
    }
}

char cMsg[30];
char cNum[30];

int main(void)
{
    UART_InitWithInt(9600);
    Timer0Interrupts_Init(1000000, &WatchUpdate);
    
    while(1)
    {
        if(Transmiter_GetStatus() == FREE)
        {
            if(eReceiver_GetStatus() == READY)
            {
                Receiver_GetStringCopy(cNum);
                DecodeMsg(cNum);
                
                if(ucTokenNr == 2)
                {
                
										if(cNum[0] == 'c' && cNum[1] == 'a' && cNum[2] == 'l' && cNum[3] == 'c')
                    {
                        unsigned int uiResult = (asToken[1].uValue.uiNumber) * 2;
                        
                        CopyString("calc 0x", cMsg);
                        AppendUIntToString(uiResult, cMsg);
                        Transmiter_SendString(cMsg);
                    }
                }
            }
            else if(sWatch.fMinutesValueChanged == 1)
            {
                sWatch.fMinutesValueChanged = 0;
                
                CopyString("min 0x", cMsg);
                AppendUIntToString(sWatch.ucMinutes, cMsg);
                Transmiter_SendString(cMsg);
            }
            else if(sWatch.fSeccondsValueChanged == 1)
            {
                sWatch.fSeccondsValueChanged = 0;
                
                CopyString("sec 0x", cMsg);
                AppendUIntToString(sWatch.ucSecconds, cMsg);
                Transmiter_SendString(cMsg);
            }
        }
    }
}
