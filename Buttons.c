#include "Buttons.h"


void Buttons_init()
{
	unsigned long volatile delay;	
  SYSCTL_RCGC2_R |= 0x10;           // Port E clock
  delay = SYSCTL_RCGC2_R;           // wait 3-5 bus cycles
  GPIO_PORTE_DIR_R &= ~((1<<0)|(1<<1));        // PE2,1,0 input 
  GPIO_PORTE_AFSEL_R &= ~((1<<0)|(1<<1));      // not alternative
  GPIO_PORTE_AMSEL_R &= ~((1<<0)|(1<<1));      // no analog
  GPIO_PORTE_PCTL_R &= ~0x000000FF; // bits for PE4,PE2,PE1,PE0
  GPIO_PORTE_DEN_R |= ((1<<0)|(1<<1));         // enable PE4,PE2,PE1,PE0
}

unsigned long  Button_read0()
{
	return (GPIO_PORTE_DATA_R&1<<0);
}

unsigned long  Button_read1()
{
	return (GPIO_PORTE_DATA_R&1<<1);
}
