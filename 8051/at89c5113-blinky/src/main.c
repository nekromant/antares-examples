#include <8052.h>
#include <AT89C513xA.h>
#include <arch/lib/delaylib.h>

int main()
{
	while(1) {
		P4_0^=1;
		delay_ms(100);
		P4_1^=1;
	}
}
