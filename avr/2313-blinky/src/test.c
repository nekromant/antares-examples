#include <arch/antares.h> 
#include <avr/io.h> 
#include <util/delay.h>  


ANTARES_INIT_LOW(io_init) 
{ 
  DDRD=0xff; 
}

ANTARES_APP(blink) 
{ 
  while(1)
  {
    PORTD^=0xff; 
    _delay_ms(1000);
  }   
}

