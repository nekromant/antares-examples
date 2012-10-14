#include <arch/stc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <arch/lib/stc/iap.h>
#include <lib/urpc.h>

#define F_CPU 11059200L
#define br 19200
#define MAKEBRT(baud) (256 - F_CPU/32/baud) 

void gotchar(char);
static unsigned char cnt;

void rxbyte() __interrupt 4
{
	char r;
	if (TI) TI = 0;                     
	if (RI)                             
		RI = 0;                         
	r = SBUF;
	//P1=r;
	if (r==0x7f) {
		cnt++;
		if (cnt == 0xf0) 
			iap_reboot2isp();
	} else { 
		cnt=0;
		gotchar(r);
	}
}


void putchar(char c) {
		ES=0;
		TI=0;
		SBUF=c;
		while (!TI);;
		TI=0;
		ES=1;
	}


	unsigned char* idata_point = (unsigned char*) 0xF1;

//static uint16_t servo_nextpos[32];
//static uint16_t servo_pos[32];
	char r=0;
	int main()
	{
		P0M0=0xff;
		P0=0xff;
		SCON = 0x50;
		AUXR = 0x95;
		BRT = MAKEBRT(br); 
		ES = 1;     
		EA = 1;
		TMOD=0x1; /* 16 bit counter mode */

		while(1)
		{
			urpc_loop();
		}
	}
