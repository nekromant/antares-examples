#include <arch/antares.h>
#include <arch/delay.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>

static GPIO_InitTypeDef GPIO_InitStruct = {
	.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15,
	.GPIO_Speed = GPIO_Speed_100MHz,
	.GPIO_Mode = GPIO_Mode_OUT,
        .GPIO_PuPd = GPIO_PuPd_NOPULL
};


ANTARES_INIT_LOW(gpio_init)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_Init(GPIOD, &GPIO_InitStruct);
}


#ifdef CONFIG_ANTARES_STARTUP
ANTARES_APP(blinky) {
#else
int main() {
	gpio_init();	
#endif

	GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
        delay_ms(500);
	GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
        delay_ms(500);
}


