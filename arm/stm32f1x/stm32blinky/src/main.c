#include <arch/antares.h>
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

static GPIO_InitTypeDef gpa = {
	.GPIO_Pin = GPIO_Pin_5,
	.GPIO_Speed = GPIO_Speed_50MHz,
	.GPIO_Mode = GPIO_Mode_Out_PP
};


ANTARES_INIT_LOW(gpio_init)
{
	RCC_AHBPeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_Init(GPIOA, &gpa);
}


#ifdef CONFIG_ANTARES_STARTUP
ANTARES_APP(blinky) {
#else
int main() {
	gpio_init();	
#endif

	int i=1005000;
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	while(i--) 
		asm ("nop;nop;nop;");
	i=50500;
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	while(i--) 
		asm ("nop;nop;nop;");

}


