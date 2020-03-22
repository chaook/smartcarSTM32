#ifndef _USART_H
#define _USART_H

#include "stm32f10x.h"

#define USART3_MAX_RECV_LEN		100					//最大接收缓存字节数
#define USART3_MAX_SEND_LEN		400					//最大发送缓存字节数
#define USART3_RX_EN 			1					//0,不接收;1,接收.

extern u8 USART3_RX_BUF[USART3_MAX_RECV_LEN]; 		//接收缓冲,最大USART3_MAX_RECV_LEN字节
extern u8 USART3_TX_BUF[USART3_MAX_SEND_LEN]; 		//发送缓冲,最大USART3_MAX_SEND_LEN字节
extern short int USART3_RX_STA;   						//接收数据状态

void usart_init(void);

#endif
