__irq void UART0_Interrupt (void);
void UART_InitWithInt(unsigned int uiBaudRate);
void Receiver_PutCharacterToBuffer(char cCharacter);
enum eReceiverStatus eReceiver_GetStatus(void);
void Receiver_GetStringCopy(char *ucDestination);

extern char cOdebranyZnak;
#define TERMINATOR '\r'
#define RECEIVER_SIZE 4
