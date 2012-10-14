#include <arch/stc.h>
#include <lib/urpc.h>
#include <arch/lib/delaylib.h>

__sbit __at(__SFR_P3^3) BEEP;

void set_led(char* data) {
	P1 = *data;
}

void set_seg(char* data) {
	P0 = *data;
}

void beep(char* len) {

        BEEP=0;
        delay_ms((int)*len);
        BEEP=1;
}

struct urpc_object urpc_exports[] = {
	{
		.flags = FLAG_URPC_METHOD,
		.name = "set_bar",
		.data = "1u;",
		.method = set_led,
	},
	{
		.flags = FLAG_URPC_METHOD,
		.name = "beep",
		.data = "1u",
		.method = beep,
	},
	{
		.flags = FLAG_URPC_METHOD,
		.name = "set_seg",
		.data = "1u;1u",
		.reply = "1u",
		.method = set_seg,
	},
	{
		.flags = FLAG_URPC_EVENT,
		.name = "btn_pressed",
		.data = "1u;1u",
		.method = set_seg,
	},
	{ .flags = 0x0, },
};
