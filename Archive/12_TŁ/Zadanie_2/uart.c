#include <LPC210X.H>
#include "uart.h"
#include "string.h"
/************ UART ************/
// U0LCR Line Control Register
#define mDIVISOR_LATCH_ACCES_BIT                   0x00000080
#define m8BIT_UART_WORD_LENGTH                     0x00000003

// UxIER Interrupt Enable Register
#define mRX_DATA_AVALIABLE_INTERRUPT_ENABLE        0x00000001
#define mTHRE_INTERRUPT_ENABLE                     0x00000002

// UxIIR Pending Interrupt Identification Register
#define mINTERRUPT_PENDING_IDETIFICATION_BITFIELD  0x0000000F
#define mTHRE_INTERRUPT_PENDING                    0x00000002
#define mRX_DATA_AVALIABLE_INTERRUPT_PENDING       0x00000004

/************ Interrupts **********/
// VIC (Vector Interrupt Controller) channels
#define VIC_UART0_CHANNEL_NR  6
#define VIC_UART1_CHANNEL_NR  7

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE  0x00000020

void Receiver_PutCharacterToBuffer(char cCharacter);

////////////// Zmienne globalne ////////////
char cOdebranyZnak;

struct ReceiverBuffer
{
    char cData[RECEIVER_SIZE];
    unsigned char ucCharCtr;
    enum eReceiverStatus eStatus;
};

struct ReceiverBuffer sRxBuffer;

struct TransmiterBuffer
{
    char cData[TRANSMITER_SIZE];
    enum eTransmiterStatus eStatus;
    unsigned char fLastCharacter;
    unsigned char cCharCtr;
};
struct TransmiterBuffer sTransmiterBuffer;

///////////////////////////////////////////
__irq void UART0_Interrupt (void) {
   // Odczyt U0IIR powoduje jego kasowanie wiec lepiej pracowac na kopii
   unsigned int uiCopyOfU0IIR = U0IIR; 

   if ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mRX_DATA_AVALIABLE_INTERRUPT_PENDING) // odebrano znak
   {
      Receiver_PutCharacterToBuffer(U0RBR);
   } 
   else if ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mTHRE_INTERRUPT_PENDING)             // wyslano znak - nadajnik pusty 
   {
       char cKolejnyZnak = Transmiter_GetCharacterFromBuffer(); 
       if(cKolejnyZnak != '\0')
       {
           U0THR = cKolejnyZnak;
       }
   }

   VICVectAddr = 0; // Acknowledge Interrupt
}

////////////////////////////////////////////
void UART_InitWithInt(unsigned int uiBaudRate){

   // UART0
   // Ustawienie pinów: P0.0 na TxD0 oraz P0.1 na RxD0 (wartosc 0x05)
   PINSEL0 = PINSEL0 | 0x05;                                   
   
   U0LCR  |= m8BIT_UART_WORD_LENGTH | mDIVISOR_LATCH_ACCES_BIT; // dlugosc slowa, DLAB = 1
   U0DLL   = ((15000000)/16)/uiBaudRate;                        // predkosc transmisji 
   U0LCR  &= (~mDIVISOR_LATCH_ACCES_BIT);                       // DLAB = 0
   
   // Aktywacja zglaszania przerwania po odebraniu pojedynczego znaku do bufora RBR
   U0IER  |= mRX_DATA_AVALIABLE_INTERRUPT_ENABLE | mTHRE_INTERRUPT_ENABLE;                

   // INT - Konfiguracja Vectored Interrupt Controller
   VICVectAddr1  = (unsigned long) UART0_Interrupt;             // set interrupt service routine address
   VICVectCntl1  = mIRQ_SLOT_ENABLE | VIC_UART0_CHANNEL_NR;     // use it for UART 0 Interrupt
   VICIntEnable |= (0x1 << VIC_UART0_CHANNEL_NR);               // Enable UART 0 Interrupt Channel
}

void Receiver_PutCharacterToBuffer(char cCharacter)
{
    if (sRxBuffer.ucCharCtr == RECEIVER_SIZE)
    {
        sRxBuffer.eStatus = OVERFLOW;
    }
    else if (cCharacter == TERMINATOR)
    {
        sRxBuffer.cData[sRxBuffer.ucCharCtr] = '\0';
        sRxBuffer.eStatus = READY;
    }
    else
    {
        sRxBuffer.cData[sRxBuffer.ucCharCtr] = cCharacter;
        sRxBuffer.ucCharCtr++;
    }
}

enum eReceiverStatus eReceiver_GetStatus(void)
{
    return sRxBuffer.eStatus;
}

void Receiver_GetStringCopy(char *ucDestination)
{
    CopyString(sRxBuffer.cData, ucDestination);
    sRxBuffer.eStatus = EMPTY;
    sRxBuffer.ucCharCtr = 0;
}

char Transmiter_GetCharacterFromBuffer(void)
{
    if(sTransmiterBuffer.fLastCharacter == 1)
    {
        sTransmiterBuffer.eStatus = FREE;
        sTransmiterBuffer.fLastCharacter = 0;
        sTransmiterBuffer.cCharCtr = 0;
        return '\0';
    }
    else if(sTransmiterBuffer.cData[sTransmiterBuffer.cCharCtr] == '\0')
    {
        sTransmiterBuffer.fLastCharacter = 1;
        return TERMINATOR;
    }
    else
    {
        char cAktualnyZnak = sTransmiterBuffer.cData[sTransmiterBuffer.cCharCtr];
        sTransmiterBuffer.cCharCtr++;
        return cAktualnyZnak;
    }
}

void Transmiter_SendString(char cString[])
{
    CopyString(cString, sTransmiterBuffer.cData);
    sTransmiterBuffer.eStatus = BUSY;
    sTransmiterBuffer.cCharCtr = 0;
    sTransmiterBuffer.fLastCharacter = 0;
    U0THR = Transmiter_GetCharacterFromBuffer();
}    

enum eTransmiterStatus Transmiter_GetStatus(void)
{
    return sTransmiterBuffer.eStatus;
}
