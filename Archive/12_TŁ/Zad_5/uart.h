#define RECEIVER_SIZE 30
#define TERMINATOR '\r'
#define TRANSMITER_SIZE 30


__irq void UART0_Interrupt (void);
void UART_InitWithInt(unsigned int uiBaudRate);
void Receiver_PutCharacterToBuffer(char cCharacter);
enum eReceiverStatus eReceiver_GetStatus(void);
void Receiver_GetStringCopy(char *ucDestination);
enum eReceiverStatus {EMPTY, READY, OVERFLOW};
extern char cOdebranyZnak;

enum eTransmiterStatus{FREE, BUSY};
char Transmiter_GetCharacterFromBuffer(void);
void Transmiter_SendString(char cString[]);
enum eTransmiterStatus Transmiter_GetStatus(void);




