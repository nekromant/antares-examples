#include <arch/antares.h>
#include <msp430.h>
#include <arch/lib/delaylib.h>


ANTARES_INIT_LOW(wdt_dsbl)
{
	WDTCTL = WDTPW | WDTHOLD;	
}

ANTARES_INIT_LOW(led_init)
{
	PJDIR |= 0x0f;
	P3DIR |= 0xf0;
	P3OUT |= 0xf0;
}

void frexp_leds(char leds)
{
	/* Reset bits */
	P3OUT&= ~0xf0;
	PJOUT&= ~0x0f;
	/* Write state */
	PJOUT |= leds & 0x0f;
	P3OUT |= leds & 0xf0;
}

/* This 'app' will be called over and over in a loop */
ANTARES_APP(blinker_app)
{
	int i;
#if defined(CONFIG_LED_LEFT) || defined(CONFIG_LED_KITT)
	for (i=0; i<8; i++) {
		frexp_leds( 1<<i );
		delay_s(CONFIG_LED_DELAY);
	}
#endif
#if defined(CONFIG_LED_RIGHT) || defined(CONFIG_LED_KITT)
	for (i=7; i>=0; i--) {
		frexp_leds( 1<<i );
		delay_s(CONFIG_LED_DELAY);
	}
#endif

}

