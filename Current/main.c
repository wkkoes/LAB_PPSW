#include "servo.h"
#include "keyboard.h"
//git test
int main(void) 
{
    KeyboardInit();
    ServoInit(200); 
		
	ServoGoTo(24);
		ServoGoTo(12);
    while(1) 
    {
        switch(eKeyboardRead()) 
        {
            case BUTTON_0:
                ServoCallib();
                break;
            case BUTTON_1:
                ServoGoTo(48);
                break;
            case BUTTON_2:
                ServoGoTo(150);
                break;
            case BUTTON_3:
                ServoGoTo(500);
                break;
            default:
                break;
        }
    }
}
