#include <LPC21xx.H>
#include "led.h"
#include "timer_interrupts.h"
#include "keyboard.h"
#define Detector_Out_bm (1<<10)

enum DetectorState {ACTIVE, INACTIVE};
enum ServoState {CALLIB, IDLE, IN_PROGRESS};

struct Servo
{
	enum ServoState eState;
	unsigned int uiCurrentPosition;
	unsigned int uiDesiredPosition;
};

struct Servo sServo = {CALLIB, 0, 0};



void DetectorInit()
{
	IO0DIR = IO0DIR & (~(Detector_Out_bm));
}

enum DetectorState eReadDetector()
{
	if((IO0PIN & Detector_Out_bm) == 0)
	{
		return ACTIVE;
	}
	else
	{
		return INACTIVE;
	}
}

void Automat(void)
{
	switch(sServo.eState)
	{
		case CALLIB:
			if(eReadDetector() == INACTIVE)
			{
				LedStepLeft();
			}
			else
			{
				sServo.eState = IDLE;
				sServo.uiCurrentPosition = 0; 
				sServo.uiDesiredPosition = 0;
			}
			break;
		
		case IDLE:
			if(sServo.uiCurrentPosition != sServo.uiDesiredPosition)
			{
				sServo.eState = IN_PROGRESS;
			}
			break;
			
		case IN_PROGRESS:
			if(sServo.uiCurrentPosition < sServo.uiDesiredPosition)
			{
				LedStepRight();
				sServo.uiCurrentPosition++;
			}
			else if(sServo.uiCurrentPosition > sServo.uiDesiredPosition)
			{
				LedStepLeft();
				sServo.uiCurrentPosition--;
			}
			else
			{
				sServo.eState = IDLE;
			}
			break;
		}
	}
			
				
			
  
    
 int main()
 {
	 LedInit();
	 DetectorInit();
	 KeyboardInit();
	 
	 Timer0Interrupts_Init(20000, &Automat);
	 
	 while(1)
	 {
		 switch(eKeyboardRead())
		 {
			 case BUTTON_0:
				 sServo.eState = CALLIB;
				 break;
			 
			 case BUTTON_1:
				 sServo.uiDesiredPosition = 12;
				 break;
			 case BUTTON_2:
				 sServo.uiDesiredPosition = 24;
				 break;
			 case BUTTON_3:
				 sServo.uiDesiredPosition = 150;
				 break;
			 default:
				 break; 
	 }
 }
}
	 
		
			
		
