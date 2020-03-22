#include "led.h"
#include "stm32f10x_gpio.h"

unsigned char LED_FLAG = 0;

void led_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	led_turn_off();
}

void led_turn_on()
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	LED_FLAG = 1;
}
	
void led_turn_off()
{
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	LED_FLAG = 0;
}

void led_turn()
{
	if(LED_FLAG == 0)
		led_turn_on();
	else
		led_turn_off();
}

