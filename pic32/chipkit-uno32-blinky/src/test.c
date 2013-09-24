#include <plib.h>

// Define timing constants
#define SHORT_DELAY (500*8)
#define LONG_DELAY  (4000*8)



int main()
{
	mJTAGPortEnable(DEBUG_JTAGPORT_OFF);
	mPORTFClearBits(BIT_0);

	// Make all lower 8-bits of PORTA as output
	mPORTFSetPinsDigitalOut( BIT_0 );

	// Start timer1, Fpb/256, max period
	OpenTimer1(T1_ON | T1_PS_1_256 | T1_SOURCE_INT, 0xFFFF);

	// The main loop
	while( 1)
	{
		WriteTimer1(0);
		while ( TMR1 < LONG_DELAY);
		PORTF ^= BIT_0;
		
	} 
}
