#include <arch/antares.h>
#include <msp430.h>
#include <arch/lib/delaylib.h>


ANTARES_INIT_LOW(wdt_dsbl)
{
	WDTCTL = WDTPW | WDTHOLD;	
}

ANTARES_INIT_LOW(led_init)
{
	P1DIR |=  (1 | 1<<6);
	P1OUT |= 0x1;
	P1IE |= 1<<3; /* Enable button ISR */
}

/* This 'app' will be called over and over in a loop */
ANTARES_APP(blinker_app)
{
	P1OUT^= (1 | 1<<6);
	delay_s(1);
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
        while (!(P1IN & (1<<3)));; /* debounce */
	P1IFG &= ~(1<<3); /* Clear the isr flag */
	P1OUT^=1<<6;
}
