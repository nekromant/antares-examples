#include <arch/antares.h>
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include <stdio.h>
#include <string.h>

static USART_InitTypeDef usart1 = {
	.USART_BaudRate = 115200,
	.USART_WordLength = USART_WordLength_8b,
	.USART_StopBits = USART_StopBits_1,
	.USART_Parity = USART_Parity_No,
	.USART_Mode = USART_Mode_Rx | USART_Mode_Tx,
	.USART_HardwareFlowControl = USART_HardwareFlowControl_None,	
};

static GPIO_InitTypeDef usart_tx = {
	.GPIO_Pin = GPIO_Pin_9,
	.GPIO_Speed = GPIO_Speed_50MHz,
	.GPIO_Mode = GPIO_Mode_AF_PP
};

static GPIO_InitTypeDef usart_rx = {
	.GPIO_Pin = GPIO_Pin_10,
	.GPIO_Speed = GPIO_Speed_50MHz,
	.GPIO_Mode = GPIO_Mode_IN_FLOATING
};

static USART_ClockInitTypeDef USART_ClockInitStructure;

ANTARES_INIT_LOW(usart1_init)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_Init(GPIOA, (GPIO_InitTypeDef*) &usart_tx);
	GPIO_Init(GPIOA, (GPIO_InitTypeDef*) &usart_rx);
	USART_ClockStructInit(&USART_ClockInitStructure);
	USART_ClockInit(USART1, &USART_ClockInitStructure);
	USART_Init(USART1, &usart1);
	USART_Cmd(USART1, ENABLE);
}

static GPIO_InitTypeDef gpc = {
	.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8,
	.GPIO_Speed = GPIO_Speed_50MHz,
	.GPIO_Mode = GPIO_Mode_Out_PP
};

ANTARES_INIT_LOW(gpio_init)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);
//	RCC->APB2ENR |= 0x10 | 0x04;					
	GPIO_Init(GPIOC, &gpc);
}

void greeter()
{
	int a;
	printf("Hello, world\n\r");
	scanf("%d", &a);
	printf("===> %d\n",a);
}




extern char _ebss;
ANTARES_APP(blinky) 
{
	GPIO_SetBits(GPIOC, GPIO_Pin_9);
	printf("Antares ST-Link terminal demo\n");
	printf("Antares v. " CONFIG_VERSION_STRING " git commit " CONFIG_VERSION_GIT "\n");
	printf("Heap end @ 0x%x; stack @ 0x%x \n", &_ebss, __get_MSP());
	while(1);;
}

