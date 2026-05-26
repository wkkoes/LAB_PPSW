#include <LPC210X.H>
#include "uart.h"
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

//enum eReceiverStatus {EMPTY, READY, OVERFLOW};

struct ReceiverBuffer
{
	char cData[RECEIVER_SIZE];
	unsigned char ucCharCtr;
	enum eReceiverStatus eStatus;
};

struct ReceiverBuffer sRxBuffer;

///////////////////////////////////////////
__irq void UART0_Interrupt (void) {
   // Odczyt U0IIR powoduje jego kasowanie wiec lepiej pracowac na kopii
   unsigned int uiCopyOfU0IIR = U0IIR; 

   if ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mRX_DATA_AVALIABLE_INTERRUPT_PENDING) // odebrano znak
   {
      Receiver_PutCharacterToBuffer(U0RBR);
   } 
   
   if ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mTHRE_INTERRUPT_PENDING)              // wyslano znak - nadajnik pusty 
   {
      // na razie nic nie wysylamy
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
   U0IER  |= mRX_DATA_AVALIABLE_INTERRUPT_ENABLE;               

   // INT - Konfiguracja Vectored Interrupt Controller
   VICVectAddr1  = (unsigned long) UART0_Interrupt;             // set interrupt service routine address
   VICVectCntl1  = mIRQ_SLOT_ENABLE | VIC_UART0_CHANNEL_NR;     // use it for UART 0 Interrupt
   VICIntEnable |= (0x1 << VIC_UART0_CHANNEL_NR);               // Enable UART 0 Interrupt Channel
}

void Receiver_PutCharacterToBuffer(char cCharacter)
{
	switch (sRxBuffer.eStatus)
	{
		case EMPTY:
		if(cCharacter == TERMINATOR)
			{
				sRxBuffer.cData[sRxBuffer.ucCharCtr] = '\0';
				sRxBuffer.eStatus = READY;
				sRxBuffer.ucCharCtr = 0;
			}
			
			else if(sRxBuffer.ucCharCtr < (RECEIVER_SIZE - 1))
			{
				sRxBuffer.cData[sRxBuffer.ucCharCtr] = cCharacter;
				sRxBuffer.ucCharCtr = sRxBuffer.ucCharCtr + 1;
			}
			
			else
			{
				sRxBuffer.eStatus = OVERFLOW;
			}
			
			break;
			
		case READY:
			break;
		
		case OVERFLOW:
			break;
	}
}

enum eReceiverStatus eReceiver_GetStatus(void)
{
	return sRxBuffer.eStatus;
}

void Receiver_GetStringCopy(char *ucDestination)
{
	unsigned char ucCopyCtr = 0;
	while(sRxBuffer.cData[ucCopyCtr] != '\0')
	{
		ucDestination[ucCopyCtr] = sRxBuffer.cData[ucCopyCtr];
		ucCopyCtr = ucCopyCtr + 1;
	}
	
	ucDestination[ucCopyCtr] = '\0';
	sRxBuffer.eStatus = EMPTY;
}



			
				
				
				
			
