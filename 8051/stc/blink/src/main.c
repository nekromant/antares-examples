#include <arch/stc.h>

int delay;
int main()
{
	while(1)
	{
		P0M0=0xff;
		P0=0xf0;
		delay=0xffff;
		while(delay--);;
		P0M0=0xff;
		P0=0x0f;
		delay=0xffff;
		while(delay--);;
	}
}
