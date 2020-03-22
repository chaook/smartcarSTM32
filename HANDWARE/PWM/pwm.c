#include "pwm.h"

void RCC_Configuration(void)	
{
//	SystemInit();	//????
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // ?? ????
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	// ??????IO??
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	// ??TIM3?????
}
 
/* ????? */
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	//???LED D1 GPIOB
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	//???????(PWM??)
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	//???????(PWM??)
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
}
 
/* ?? TIM3 ??? */
void TIM3_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	// ??????
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
		
	// ??????
	TIM_TimeBaseStructure.TIM_Period = 4000-1;		// ??
	TIM_TimeBaseStructure.TIM_Prescaler = 0;		// ????,???????1
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;	// ????
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// ????
	TIM_TimeBaseInit(TIM3, & TIM_TimeBaseStructure);
		
	// PWM ???
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;		// ????
	
	TIM_OC1Init(TIM3, & TIM_OCInitStructure);
	TIM_OC2Init(TIM3, & TIM_OCInitStructure);
	TIM_OC3Init(TIM3, & TIM_OCInitStructure);
	TIM_OC4Init(TIM3, & TIM_OCInitStructure);

	
	// ??????TIMx?CCR2????????
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM3, ENABLE);		//????????
}


void pwm_init()
{
	RCC_Configuration();
	GPIO_Configuration();
	TIM3_Configuration();
}
