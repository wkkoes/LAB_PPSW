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
			
void ServoInit(unsigned int uiServoFrequency)
{
		unsigned int uiServoPeroid = 1000000 / uiServoFrequency;
		sServo.eState = CALLIB;
		LedInit();
		DetectorInit();
		Timer0Interrupts_Init(uiServoPeroid, &Automat);
}
	
void ServoCallib()
{
		sServo.eState = CALLIB;
}

void ServoGoTo(unsigned int uiPosition)
{
	sServo.uiDesiredPosition = uiPosition;
}
  
    
 int main()
 {
	 KeyboardInit();
	 ServoInit(200);
	 
	 while(1)
	 {
		 switch(eKeyboardRead())
		 {
			 case BUTTON_0:
				 ServoCallib();
				 break;
			 
			 case BUTTON_1:
				 ServoGoTo(12);
				 break;
			 
			 case BUTTON_2:
				 ServoGoTo(24);
				 break;
			 
			 case BUTTON_3:
				 ServoGoTo(36);
				 break;
			
			 default:
				 break; 
	 }
 }
}
	 
		
			
		
