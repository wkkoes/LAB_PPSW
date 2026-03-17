#include <LPC21xx.H>

unsigned int uiINT;
int main()
{
	uiINT = uiINT | 0xB00000E8;

	while(1){}
}