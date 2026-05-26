__irq void UART0_Interrupt (void);
void UART_InitWithInt(unsigned int uiBaudRate);
void Receiver_PutCharacterToBuffer(char cCharacter);
enum eReceiverStatus eReceiver_GetStatus(void);
void Receiver_GetStringCopy(char *ucDestination);
enum eReceiverStatus {EMPTY, READY, OVERFLOW};
extern char cOdebranyZnak;
#define RECEIVER_SIZE 10

