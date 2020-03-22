#include "stm32f10x.h"
#include "led.h"
#include "lcd.h"
#include "pwm.h"
#include "usart.h"
#include "motor.h"

int main(void)
{	
//	int i;
	led_init();
	pwm_init();
	usart_init();
//	lcd_init();
//	display_name();
//	lcd_test();
	while(1)
	{
		if ((USART3_RX_STA&0x8000)==0x8000)
		{
			if (USART3_RX_BUF[0] == 'm'){
				motor();
				led_turn();
			}
			USART3_RX_STA=0;
		}
	//	USART_SendData(USART1, 'A');
		
	//	if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
	//	{
	//		led_turn();
	//		delay(1000);
	//	}
		
/*		for (i=0; i<900; i++)
		{
			TIM_SetCompare3(TIM3, i);
			TIM_SetCompare4(TIM3, i);
			delay(2);
		}
*/		
		
//		motor_up(50, 0);
/*		for (i=0; i<=50; i++)
		{
			motor_up(i);
			led_turn();
			delay(200);
		}
		
		for (i=0; i<=50; i++)
		{
			led_turn_on();
			motor_down(i);
			delay(200);
		}
		*/
		
/*		
		if ((USART3_RX_STA&0x8000)==0x8000)
		{
			led_turn();
			lcd_show_8X16char((uchar)(USART3_RX_STA&0x7fff)+'0', 0, 0);
			lcd_show_8X16string("display ok", 0, 1);
			lcd_show_8X16string(USART3_RX_BUF, 1, 0);
			USART3_RX_STA=0;
		}
*/
	/*	for (i=900; i>0; i--)
		{
			TIM_SetCompare4(TIM3, i);
			delay(2);
		}
		*/
	}
}
	
