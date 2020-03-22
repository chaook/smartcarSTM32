#include "motor.h"
#include "pwm.h"
#include "usart.h"

/**
* 
* @ param s is 0-50
*
*/

void motor()
{
	if (USART3_RX_BUF[1]=='-')
	{
		motor_down(USART3_RX_BUF[2]);
	}
	else
	{
		motor_up(USART3_RX_BUF[2]);
	}
}

void motor_up(char s)
{
//	s = s * 4000 / 50;  //s*3000/50
	//turn left
	if (USART3_RX_BUF[3]=='-')
	{
		//right
		TIM_SetCompare1(TIM3, s*77);
		TIM_SetCompare2(TIM3, 0);
		//left
		TIM_SetCompare3(TIM3, s*(80 - USART3_RX_BUF[4]));
		TIM_SetCompare4(TIM3, 0);
	}
	else 
	{
		//right
		TIM_SetCompare1(TIM3, s*(77 - USART3_RX_BUF[4]));
		TIM_SetCompare2(TIM3, 0);
		//left
		TIM_SetCompare3(TIM3, s*80);
		TIM_SetCompare4(TIM3, 0);
	}
}
	
void motor_down(char s)
{
//	s = s * 4000 / 50;  //s*3000/50
	//turn left
	if (USART3_RX_BUF[3]=='-')
	{
		//right
		TIM_SetCompare1(TIM3, 0);
		TIM_SetCompare2(TIM3, s*78);
		//left
		TIM_SetCompare3(TIM3, 0);
		TIM_SetCompare4(TIM3, s*(80 - USART3_RX_BUF[4]));
	}
	else
	{
		TIM_SetCompare1(TIM3, 0);
		TIM_SetCompare2(TIM3, s*(78 - USART3_RX_BUF[4]));
		TIM_SetCompare3(TIM3, 0);
		TIM_SetCompare4(TIM3, s*80);
	}
}
	
