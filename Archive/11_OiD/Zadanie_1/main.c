#include "servo.h"
#include "keyboard.h"
#include "led.h"
#include "uart.h"
#include "servo.h"
#define RECEIVER_SIZE 4

extern char cOdebranyZnak;

int main(void)
{
	char cTest[10];
	
	Receiver_PutCharacterToBuffer('k');
  Receiver_PutCharacterToBuffer('o');
  Receiver_PutCharacterToBuffer('d');
 	Receiver_PutCharacterToBuffer(TERMINATOR);
	
	Receiver_GetStringCopy(cTest);

  Receiver_PutCharacterToBuffer('k');
  Receiver_PutCharacterToBuffer('o');
  Receiver_PutCharacterToBuffer('d');
  Receiver_PutCharacterToBuffer('1');
  Receiver_PutCharacterToBuffer(TERMINATOR);
	
	while(1){}
}
