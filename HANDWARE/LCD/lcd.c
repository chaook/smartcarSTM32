#include "lcd.h"
#include "stm32f10x_gpio.h"

#define  Display  0xAF  	//��ʾ����
#define  Power    0x2F	   //��Դȫ��
#define  VO       0x24     //�Աȶȵ���	     
#define  AllPoint 0xA4	   //��ȫ����ʾ
#define  ADCset   0xA1    	//����131-4
#define  COMset   0xc0    	//com0-com63
#define  ELECTVO  0x81     //���ȵ���	 ������ɫ 	��ͬ��ģ����Ҫ��ͬ��  ELECTSET
#define  ELECTSET 0x2a	   //������ֵ	 ������ɫ 	��ͬ��ģ����Ҫ��ͬ��	��ֵ
#define  BIASSET  0xA2    //ռ�ձ�1/9

/* �� �� �� */
uchar name[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xD0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,
0xE0,0xE0,0xE0,0x60,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xE0,0xF0,0xF8,0xDC,0xDC,0xCE,0xCF,0xC7,0xC7,0x43,0x43,0x41,0x41,0x61,
0x60,0x60,0x60,0x60,0x60,0x60,0x70,0x70,0x70,0x70,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,
0xE0,0xE0,0xE0,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x08,0x08,0x08,0x08,0x08,0x18,0x18,0x1C,0x1C,0x1C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,
0x0E,0x06,0x06,0x06,0x06,0x06,0x07,0x07,0xC7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,
0x1F,0x0F,0x06,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x18,0x38,0x38,0x78,0x70,0x70,0xF0,0xF0,
0xF0,0xE0,0xE0,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE3,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0x0F,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x02,0x02,0x06,0x04,0x0C,0x0C,0x1C,0x18,0x38,0x38,0x70,0x70,0xF0,
0xE0,0xE0,0xE0,0xC0,0xE0,0xF0,0xFC,0xFF,0xFF,0x7F,0x3F,0x1F,0x07,0x03,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10,
0x10,0x20,0x20,0x60,0xE0,0xE0,0xE0,0xE0,0xF0,0xF8,0xFE,0xFF,0xFF,0xFF,0x7F,0x3F,
0x1F,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,
0x7E,0x3F,0x3F,0x1F,0x0F,0x07,0x07,0x0F,0x1F,0x1F,0x3F,0x7E,0x7E,0xFC,0xFC,0xF8,
0xF8,0xF0,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xE0,0xE0,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x20,
0x20,0x20,0x30,0x30,0x30,0x31,0x33,0x33,0x33,0x33,0x31,0x31,0x30,0x30,0x38,0x38,
0x18,0x18,0x18,0x18,0x18,0x1C,0x3C,0x3C,0x7C,0xFC,0xF8,0xF8,0xF8,0xF8,0xF8,0xF0,
0xF0,0xF0,0x70,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x20,
0x20,0x30,0x30,0x18,0x18,0x1C,0x0E,0x0E,0x07,0x07,0x03,0x03,0x01,0x01,0x00,0x00,
0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x81,0x81,
0x83,0x83,0xC3,0xC3,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC1,0xC1,0xC1,
0xC0,0xC0,0xC0,0xC0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0x60,0x60,0x60,0x60,0x60,0x60,
0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,
0x60,0x60,0x20,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x1F,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
0x03,0x03,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x20,0x60,0xE0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0x80,0xC0,0xC0,0xE0,0xF0,0xF8,0xFE,0xFF,0xFF,0xFF,0xFF,0x7F,0x1F,0x07,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x0F,
0x0F,0x0F,0x0F,0x0F,0x07,0x07,0x07,0x03,0x03,0x01,0x01,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x70,0xF0,0xF0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,
0xC0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0x07,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xFC,
0xFE,0xFC,0xFC,0xFC,0xFC,0xFC,0xF8,0x78,0x78,0x78,0x70,0x30,0x30,0x20,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x02,0x06,0x06,0x0E,0x0E,0x1E,0x1E,0x3E,0x3E,0x3C,0x3C,0x3C,
0x38,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x18,0x0C,0x0C,0x0E,0x07,0x07,0x03,
0x03,0x83,0x81,0x81,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x30,0x30,0x30,0x30,0x70,0x70,0x70,0x70,
0x70,0x70,0x70,0x70,0x70,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,
0x98,0x9C,0xDC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0x7C,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xCE,0x8E,0x8E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0F,0x0F,0x0F,0x0F,0x07,0x07,0x07,
0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x03,0x03,0x03,0x03,0x02,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x80,0x80,0xC0,0xE0,0xE0,0xF0,0xF8,0xF8,0xFC,0x7E,0x3E,0x3F,
0x1F,0x1F,0x0F,0x07,0x07,0x03,0x01,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x01,0x03,0x03,0x07,0x07,0x0E,0x0E,0x1C,0x1C,0x38,0x38,0x78,0xF0,0xF0,0xF0,0xE0,
0xE0,0xC0,0xC0,0xC0,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xC0,0xC0,0xE0,0xE0,0xF0,0x70,0x78,0x78,0x3C,
0x3C,0x1E,0x1E,0x0F,0x0F,0x07,0x07,0x03,0x03,0x01,0x01,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,
0x03,0x03,0x07,0x07,0x0F,0x0F,0x1F,0x1F,0x3F,0x3F,0x7F,0x7E,0x7E,0xFE,0xFC,0xFC,
0xFC,0xFC,0xF8,0xF8,0xF8,0xF8,0xF8,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xE0,0xE0,0xE0,
0xE0,0xE0,0xE0,0xE0,0xC0,0xC0,0xC0,0xC0,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x0C,0x0C,0x04,
0x06,0x06,0x07,0x03,0x03,0x03,0x03,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x07,0x03,0x01,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x38,0xF8,0xF0,0xF0,0xF0,0xF0,
0xF0,0xE0,0xE0,0xE0,0xE0,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x81,0x83,0x87,0x8F,0x9F,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xC2,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xC0,0xC0,0xC0,0xE0,0xE0,0xE0,0xE0,0xE0,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xE7,0xE3,0x61,0x60,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,
0x70,0x70,0x78,0x78,0x70,0x70,0x70,0x70,0x70,0x60,0x60,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x01,0x01,0x03,0x03,0x03,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,
0x07,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x83,0x83,0x03,0x03,0x03,0x01,0x01,0x01,
0x0F,0x1F,0x3F,0x3F,0x0F,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x80,0x80,0x80,
0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x30,0x3C,0x1F,0x1F,0x0F,0x07,0x03,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF8,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x3E,0x1E,
0x1E,0x0C,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x07,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x1E,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x80,0x80,0xC0,0xE0,0xE0,0xF0,0xF8,0xFC,0xFF,0x7F,0x7F,0x7F,0x3F,0x3E,0x1E,
0x1C,0x1C,0x0C,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,0xE0,0xF0,0xF8,
0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xCF,0x87,0x03,0x03,0x01,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xF0,0x70,0x78,0x38,0x3C,0x3C,0x1E,0x1E,0x0F,
0x0F,0x07,0x07,0x07,0x03,0x03,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xC0,0xC0,0x60,
0x60,0x70,0x30,0x38,0x3C,0x1C,0x1E,0x0E,0x0F,0x0F,0x07,0x07,0x03,0x03,0x01,0x01,
0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,
0x10,0x10,0x18,0x18,0x08,0x0C,0x0C,0x0C,0x0E,0x06,0x06,0x07,0x07,0x03,0x03,0x03,
0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xC0,0xF8,0xFC,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,
0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x03,0x0F,0x1F,0x3F,0x7F,0x7F,0xFE,0xFC,0xF8,0xF0,0xF0,0xF0,0xE0,0xE0,0xE0,0xE0,
0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,
0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xF0,0xF0,0xF0,0xF0,0xF8,0xF8,0xFC,
0xFF,0xFF,0xFF,0x7F,0x7F,0x7C,0x78,0x30,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
0x03,0x07,0x0F,0x0F,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

void lcd_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	GPIO_ResetBits(GPIOA, LCD_CS);
	GPIO_ResetBits(GPIOA, LCD_RST);
	delay(200);
	GPIO_SetBits(GPIOA, LCD_RST);
	delay(1000);	
	  	/*
		write_cmd(BIASSET);	
		write_cmd(ADCset);
		write_cmd(COMset);
    	write_cmd(AllPoint);  
		write_cmd(VO);	  
		write_cmd(ELECTVO);	 
		write_cmd(ELECTSET);   
		write_cmd(Power);	 
		write_cmd(Display);	

			*/
	
		write_cmd(0xe2);//system reset
		delay(200);
		
		write_cmd(0x24);//SET VLCD RESISTOR RATIO
		write_cmd(0xa2);//BR=1/9
		write_cmd(0xa0);//set seg direction
		write_cmd(0xc8);//set com direction
		write_cmd(0x2f);//set power control
		write_cmd(0x40);//set scroll line
		write_cmd(0x81);//SET ELECTRONIC VOLUME
		write_cmd(0x20);//set pm: ͨ���ı��������ֵ���ı��ѹ 
		//write_cmd(0xa6);//set inverse display	   a6 off, a7 on
		//write_cmd(0xa4);//set all pixel on
		write_cmd(0xaf);//set display enable
    LcmClear();
}

void delay(uint ms)
{  uint k;
	 uint j=0;
   for(k=0;k<ms;k++)
		for(j=0;j<8500;j++);
}
/********************
������λ  ���λ���룬
********************/
void SendByte(uchar Dbyte)
{
         uchar i,TEMP; 
				 TEMP=Dbyte;
         for(i=0;i<8;i++)
         {
					 GPIO_ResetBits(GPIOA, LCD_SCK);
				 //  delay(1);
					 if((TEMP&0x80)==0x80)
						 GPIO_SetBits(GPIOA, LCD_SID);
					 else
						 GPIO_ResetBits(GPIOA, LCD_SID);
					 TEMP=TEMP<<1; 
					 GPIO_SetBits(GPIOA, LCD_SCK);
					// delay(1);
         }
}

/****************
дָ��
**************/
void write_cmd( uchar Cbyte )
{
	GPIO_ResetBits(GPIOA, LCD_CS);
	GPIO_ResetBits(GPIOA, LCD_A0);
  SendByte(Cbyte);
}

/***************
д����
******************/
void write_data( uchar Dbyte )
{
	GPIO_ResetBits(GPIOA, LCD_CS);
	GPIO_SetBits(GPIOA, LCD_A0);  
  SendByte(Dbyte);
}

/*************************
8*8�ַ���ȡģ˳��������ʽ��
���ϵ��£���λ��ǰ�������ң�
��ѡ��ҳ��ַ0-7����ѡ����0-130
ҳ����ֱ�Ӷ�ȡ8λ������Ϊ��ַ��
�����ȶ�ȡ����λ�����ȡ����λ��
**********************/
void  PUTchar8x8(uchar row,uchar col,uchar count,uchar *put)
{	
	uchar i, j;
	uint X=0;
		write_cmd(0xb0+row);
	  	write_cmd(0x10+(8*col/16));		
		write_cmd(0x00+(8*col%16));
		for(j=0;j<count;j++)
	    for(i=0;i<8;i++) write_data(put[X++]); 	
}


/*****************
8*16�ַ���ȡģ˳��������ʽ��
���ϵ��£���λ��ǰ�������ң�
��ѡ��ҳ��ַ0-7����ѡ����0-127
ҳ����ֱ�Ӷ�ȡ8λ������Ϊ��ַ��
�����ȶ�ȡ����λ�����ȡ����λ��
**********************/
void  PUTchar8x16(uchar row,uchar col,uchar count,uchar *put)
{		
	uint X=0;
	uchar i, j;
	write_cmd(0xb0+row);
	write_cmd(0x10+(8*col/16));		
	write_cmd(0x00+(8*col%16));
	for(j=0;j<count;j++)
	{ 
		for(i=0;i<8;i++) 
			write_data(put[X++]);
	  write_cmd(0xb1+row);
		write_cmd(0x10+(8*col/16));
		write_cmd(0x00+(8*col%16));
		for(i=0;i<8;i++) 
			write_data(put[X++]);
	  write_cmd(0xb0+row);
		col=col+1;
	} 
}

void display_name()
{
	uint X=0;
	uchar i, j, k;
	for (k=1; k<4; k++)
	{
		for(j=0;j<8;j++)
		{
			write_cmd(0xb0+j); 
			write_cmd(0x10);		
			write_cmd(0x00);
			for(i=0;i<128;i++) 
				write_data(name[X++]); 	
		}
		delay(1000);
	}
}


/*****************
16*16�ַ���ȡģ˳��������ʽ��
���ϵ��£���λ��ǰ�������ң�
��ѡ��ҳ��ַ0-7����ѡ����0-127
ҳ����ֱ�Ӷ�ȡ8λ������Ϊ��ַ��
�����ȶ�ȡ����λ�����ȡ����λ��
**********************/
void PUTchar16x16(uchar row,uchar col,uchar count,uchar *put)
{	
		uint X=0;
		uchar i, j;
		write_cmd(0xb0+row);
	  write_cmd(0x10+(8*col/16));		
		write_cmd(0x00+(8*col%16));
		for(j=0;j<count;j++)
		{ 
			for(i=0;i<16;i++) 
				write_data(put[X++]); 
	  	write_cmd(0xb1+row);	
		  write_cmd(0x10+(8*col/16));		
		  write_cmd(0x00+(8*col%16));
		  for(i=0;i<16;i++) 
				write_data(put[X++]);
	    write_cmd(0xb0+row);	 
		  col=col+2; 
		}
}

/*****************
24*24�ַ���ȡģ˳��������ʽ��
���ϵ��£���λ��ǰ�������ң�
��ѡ��ҳ��ַ0-7����ѡ����0-127
ҳ����ֱ�Ӷ�ȡ8λ������Ϊ��ַ��
�����ȶ�ȡ����λ�����ȡ����λ��
**********************/
void  PUTchar24x24(uchar row,uchar col,uchar count,uchar *put)
{		
	uchar i, j;
	uint X=0;
		write_cmd(0xb0+row);
	  	write_cmd(0x10+(8*col/16));		
		write_cmd(0x00+(8*col%16));
		for(j=0;j<count;j++)
		{ for(i=0;i<24;i++) write_data(put[X++]); 
	  	  write_cmd(0xb1+row);	
		  write_cmd(0x10+(8*col/16));		
		  write_cmd(0x00+(8*col%16));
		  for(i=0;i<24;i++) write_data(put[X++]);
	      write_cmd(0xb2+row);	
		  write_cmd(0x10+(8*col/16));		
		  write_cmd(0x00+(8*col%16));
		  for(i=0;i<24;i++) write_data(put[X++]);
		  write_cmd(0xb0+row);
		  col=col+3; }
}

/*****************
ͼƬ��ȡģ˳��������ʽ��
���ϵ��£�����ǰ�������ң�
��ѡ��ҳ��ַ0-7����ѡ����0-127
ҳ����ֱ�Ӷ�ȡ8λ������Ϊ��ַ��
�����ȶ�ȡ����λ�����ȡ����λ��
**********************/
void  PUTBMP(uchar *put)
{		uint X=0;
	uchar i, j;
		for(j=0;j<8;j++)
		{write_cmd(0xb0+j); 
		 write_cmd(0x10);		
		 write_cmd(0x00);
	     for(i=0;i<128;i++) write_data(put[X++]); }	

}

/*****************
ͼƬ���ԣ�ȡģ˳��������ʽ��
���ϵ��£�λ��ǰ�������ң�
��ѡ��ҳ��ַ0-7����ѡ����0-127
ҳ����ֱ�Ӷ�ȡ8λ������Ϊ��ַ��
�����ȶ�ȡ����λ�����ȡ����λ��
**********************/
void  PUTREVERSEBMP(uchar *put)
{		uint X=0;
	uchar i, j;
		for(j=0;j<8;j++)
		{write_cmd(0xb0+j); 
		 write_cmd(0x10);		
		 write_cmd(0x00);
	    for(i=0;i<128;i++) write_data(~put[X++]); }	

}

/*****************
������ȡģ˳��������ʽ��
���ϵ��£���λ��ǰ�������ң�
��ѡ��ҳ��ַ0-7����ѡ����0-127
ҳ����ֱ�Ӷ�ȡ8λ������Ϊ��ַ��
�����ȶ�ȡ����λ�����ȡ����λ��
**********************/
void LcmClear()
{	 uchar x,y;
	 for(y=0;y<8;y++)
	  {    
		write_cmd(0xb0+y);
	  	write_cmd(0x10);		
		write_cmd(0x00);
        for(x=0;x<132;x++)  write_data(0); }	
}	 
/**************
O���߳���
************/
void  ohengxian()
{
     uchar x,y;
	 for(y=0;y<8;y++)
	  {    
		write_cmd(0xb0+y);
	  	write_cmd(0x10);		
		write_cmd(0x00);
        for(x=0;x<128;x++) 
	     write_data(0x55); }	 
}

/**************
����߳���
************/
void  jihengxian()
{
     uchar x,y;
	 for(y=0;y<8;y++)
	  {    
		write_cmd(0xb0+y);
	  	write_cmd(0x10);		
		write_cmd(0x00);
        for(x=0;x<128;x++) 
	     write_data(0xAA); }	 
}

/***********************
O���߳���
***********************/
void  oshuxian()
{
     uchar x,y;
	 for(y=0;y<8;y++)
	  {    
		write_cmd(0xb0+y);
	  	write_cmd(0x10);		
		write_cmd(0x00);
        for(x=0;x<128;x++) 
	    if(x%2==0)write_data(0xFF);
		else  write_data(0); }	 
} 

/***********************
�����߳���
***********************/
void  jishuxian()
{
     uchar x,y;
	 for(y=0;y<8;y++)
	  {    
		write_cmd(0xb0+y);
	  	write_cmd(0x10);		
		write_cmd(0x00);
        for(x=0;x<128;x++) 
	    if(x%2==0) write_data(0); 
		else write_data(0xFF); }	 
}

/*******************
����ʾ����
************************/
void  dianxian()
{
     uchar x,y;
	 for(y=0;y<8;y++)
	  {    
			write_cmd(0xb0+y);
			write_cmd(0x10);		
			write_cmd(0x00);
			for(x=0;x<128;x++) 
				if(x%2==0) 
					write_data(0xAA); 
				else
					write_data(0x55); 
		}	 
}

uchar charset[][16] = {  

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*" ",0*/

{0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33,0x00,0x00,0x00,0x00},/*"!",1*/

{0x00,0x10,0x0C,0x02,0x10,0x0C,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*""",2*/

{0x00,0x40,0xC0,0x78,0x40,0xC0,0x78,0x00,0x00,0x04,0x3F,0x04,0x04,0x3F,0x04,0x00},/*"#",3*/

{0x00,0x70,0x88,0x88,0xFC,0x08,0x30,0x00,0x00,0x18,0x20,0x20,0xFF,0x21,0x1E,0x00},/*"$",4*/

{0xF0,0x08,0xF0,0x80,0x60,0x18,0x00,0x00,0x00,0x31,0x0C,0x03,0x1E,0x21,0x1E,0x00},/*"%",5*/

{0x00,0xF0,0x08,0x88,0x70,0x00,0x00,0x00,0x1E,0x21,0x23,0x2C,0x19,0x27,0x21,0x10},/*"&",6*/

{0x00,0x12,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"'",7*/

{0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00,0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00},/*"(",8*/

{0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00,0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00},/*")",9*/

{0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00},/*"*",10*/

{0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x0F,0x01,0x01,0x01},/*"+",11*/

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0x70,0x00,0x00,0x00,0x00,0x00},/*",",12*/

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x00},/*"-",13*/

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00},/*".",14*/

{0x00,0x00,0x00,0x00,0xC0,0x38,0x04,0x00,0x00,0x60,0x18,0x07,0x00,0x00,0x00,0x00},/*"/",15*/

{0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00},/*"0",16*/

{0x00,0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00},/*"1",17*/

{0x00,0x70,0x08,0x08,0x08,0x08,0xF0,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00},/*"2",18*/

{0x00,0x30,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x18,0x20,0x21,0x21,0x22,0x1C,0x00},/*"3",19*/

{0x00,0x00,0x80,0x40,0x30,0xF8,0x00,0x00,0x00,0x06,0x05,0x24,0x24,0x3F,0x24,0x24},/*"4",20*/

{0x00,0xF8,0x88,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x20,0x20,0x20,0x11,0x0E,0x00},/*"5",21*/

{0x00,0xE0,0x10,0x88,0x88,0x90,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x20,0x1F,0x00},/*"6",22*/

{0x00,0x18,0x08,0x08,0x88,0x68,0x18,0x00,0x00,0x00,0x00,0x3E,0x01,0x00,0x00,0x00},/*"7",23*/

{0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00},/*"8",24*/

{0x00,0xF0,0x08,0x08,0x08,0x10,0xE0,0x00,0x00,0x01,0x12,0x22,0x22,0x11,0x0F,0x00},/*"9",25*/

{0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00},/*":",26*/

{0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00},/*";",27*/

{0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00},/*"<",28*/

{0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x00},/*"=",29*/

{0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00},/*">",30*/

{0x00,0x70,0x48,0x08,0x08,0x88,0x70,0x00,0x00,0x00,0x00,0x30,0x37,0x00,0x00,0x00},/*"?",31*/

{0xC0,0x30,0xC8,0x28,0xE8,0x10,0xE0,0x00,0x07,0x18,0x27,0x28,0x2F,0x28,0x17,0x00},/*"@",32*/

{0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20},/*"A",33*/

{0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00},/*"B",34*/

{0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00},/*"C",35*/

{0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00},/*"D",36*/

{0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00},/*"E",37*/

{0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00},/*"F",38*/

{0xC0,0x30,0x08,0x08,0x08,0x38,0x00,0x00,0x07,0x18,0x20,0x20,0x22,0x1E,0x02,0x00},/*"G",39*/

{0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x20,0x3F,0x21,0x01,0x01,0x21,0x3F,0x20},/*"H",40*/

{0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00},/*"I",41*/

{0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,0x00},/*"J",42*/

{0x08,0xF8,0x88,0xC0,0x28,0x18,0x08,0x00,0x20,0x3F,0x20,0x01,0x26,0x38,0x20,0x00},/*"K",43*/

{0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x20,0x30,0x00},/*"L",44*/

{0x08,0xF8,0xF8,0x00,0xF8,0xF8,0x08,0x00,0x20,0x3F,0x01,0x3E,0x01,0x3F,0x20,0x00},/*"M",45*/

{0x08,0xF8,0x30,0xC0,0x00,0x08,0xF8,0x08,0x20,0x3F,0x20,0x00,0x07,0x18,0x3F,0x00},/*"N",46*/

{0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,0x00},/*"O",47*/

{0x08,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,0x20,0x3F,0x21,0x01,0x01,0x01,0x00,0x00},/*"P",48*/

{0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x10,0x28,0x28,0x30,0x50,0x4F,0x00},/*"Q",49*/

{0x08,0xF8,0x88,0x88,0x88,0x88,0x70,0x00,0x20,0x3F,0x20,0x00,0x03,0x0C,0x30,0x20},/*"R",50*/

{0x00,0x70,0x88,0x08,0x08,0x08,0x38,0x00,0x00,0x38,0x20,0x21,0x21,0x22,0x1C,0x00},/*"S",51*/

{0x18,0x08,0x08,0xF8,0x08,0x08,0x18,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00},/*"T",52*/

{0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00},/*"U",53*/

{0x08,0x78,0x88,0x00,0x00,0xC8,0x38,0x08,0x00,0x00,0x07,0x38,0x0E,0x01,0x00,0x00},/*"V",54*/

{0x08,0xF8,0x00,0xF8,0x00,0xF8,0x08,0x00,0x00,0x03,0x3E,0x01,0x3E,0x03,0x00,0x00},/*"W",55*/

{0x08,0x18,0x68,0x80,0x80,0x68,0x18,0x08,0x20,0x30,0x2C,0x03,0x03,0x2C,0x30,0x20},/*"X",56*/

{0x08,0x38,0xC8,0x00,0xC8,0x38,0x08,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00},/*"Y",57*/

{0x10,0x08,0x08,0x08,0xC8,0x38,0x08,0x00,0x20,0x38,0x26,0x21,0x20,0x20,0x18,0x00},/*"Z",58*/

{0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00},/*"[",59*/

{0x00,0x04,0x38,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x06,0x38,0xC0,0x00},/*"\",60*/

{0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00},/*"]",61*/

{0x00,0x00,0x04,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"^",62*/

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x00},/*"-",63*/

{0x00,0x04,0x38,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x06,0x38,0xC0,0x00},/*"\",64*/

{0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x19,0x24,0x24,0x12,0x3F,0x20,0x00},/*"a",65*/

{0x10,0xF0,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x3F,0x11,0x20,0x20,0x11,0x0E,0x00},/*"b",66*/

{0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x0E,0x11,0x20,0x20,0x20,0x11,0x00},/*"c",67*/

{0x00,0x00,0x80,0x80,0x80,0x90,0xF0,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20},/*"d",68*/

{0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x24,0x24,0x24,0x24,0x17,0x00},/*"e",69*/

{0x00,0x80,0x80,0xE0,0x90,0x90,0x20,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00},/*"f",70*/

{0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x6B,0x94,0x94,0x94,0x93,0x60,0x00},/*"g",71*/

{0x10,0xF0,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20},/*"h",72*/

{0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00},/*"i",73*/

{0x00,0x00,0x00,0x80,0x98,0x98,0x00,0x00,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00},/*"j",74*/

{0x10,0xF0,0x00,0x00,0x80,0x80,0x80,0x00,0x20,0x3F,0x24,0x06,0x29,0x30,0x20,0x00},/*"k",75*/

{0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00},/*"l",76*/

{0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F},/*"m",77*/

{0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20},/*"n",78*/

{0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00},/*"o",79*/

{0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,0x80,0xFF,0x91,0x20,0x20,0x11,0x0E,0x00},/*"p",80*/

{0x00,0x00,0x00,0x80,0x80,0x00,0x80,0x00,0x00,0x0E,0x11,0x20,0x20,0x91,0xFF,0x80},/*"q",81*/

{0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x20,0x20,0x3F,0x21,0x20,0x00,0x01,0x00},/*"r",82*/

{0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x33,0x24,0x24,0x24,0x24,0x19,0x00},/*"s",83*/

{0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x1F,0x20,0x20,0x10,0x00},/*"t",84*/

{0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20},/*"u",85*/

{0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x03,0x0C,0x30,0x0C,0x03,0x00,0x00},/*"v",86*/

{0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x01,0x0E,0x30,0x0C,0x07,0x38,0x06,0x01},/*"w",87*/

{0x00,0x80,0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x20,0x31,0x0E,0x2E,0x31,0x20,0x00},/*"x",88*/

{0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0x81,0x86,0x78,0x18,0x06,0x01,0x00},/*"y",89*/

{0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x21,0x30,0x2C,0x22,0x21,0x30,0x00},/*"z",90*/

{0x00,0x00,0x00,0x00,0x00,0xFC,0x02,0x02,0x00,0x00,0x00,0x00,0x01,0x3E,0x40,0x40},/*"{",91*/

{0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00},/*"|",92*/

{0x02,0x02,0xFC,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x3E,0x01,0x00,0x00,0x00,0x00},/*"}",93*/

{0x00,0x02,0x01,0x02,0x02,0x04,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"~",94*/


};

void  zifu16x16xian()
{ 
	uchar k;
  for(k=0;k<4;k++)
		PUTchar16x16(2*k,0,16,"");
}

void show_8X16char(uchar dat[], uchar row, uchar col)
{
	int i;
	write_cmd(0xb0+row*2); 
	write_cmd(0x10+(8*col/16));		
	write_cmd(0x00+(8*col%16));
	for (i=0; i<16; i++)
	{
		if (i==8)
		{
			write_cmd(0xb0+row*2+1); 
			write_cmd(0x10+(8*col/16));		
			write_cmd(0x00+(8*col%16));
		}
		write_data(dat[i]);
	}
}

void lcd_show_8X16char(uchar dat, uchar row, uchar col)
{
	if (dat>127||dat<32)
		dat = 32;
	show_8X16char(charset[dat-32], row, col);
}

void lcd_show_8X16string(uchar *dat, uchar row, uchar col)
{
	
	while((*dat) != '\0')
	{
		if (*dat>127||*dat<32)
			*dat = 32;
		show_8X16char(charset[(*dat)-32], row, col++);
		dat++;
		if (col>=16)
		{
			row++;
			col = 0;
		}
	}
}



void lcd_test()
{
//	lcd_show_string("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 0, 0);
	
	/*
	lcd_show_8X16char('B', 0, 0);
	lcd_show_8X16char('B', 1, 0);
	lcd_show_8X16char('B', 2, 0);
	lcd_show_8X16char('B', 3, 0);
//	lcd_show_8X16char('B', 0, 1);
//	lcd_show_8X16char('y', 0, 15);
//	lcd_show_8X16char('A', 3, 3);
//	lcd_show_8X16char('8', 2, 3);
	
//	uchar t[] = charset[1];
	lcd_display_16char(charset[1], 0, 0);
	lcd_display_16char(charset[2], 0, 1);
	lcd_display_16char(charset[7], 0, 2);
	lcd_display_16char(charset[8], 0, 3);
	lcd_display_16char(charset[10], 0, 4);
	lcd_display_16char(charset[20], 0, 5);
	lcd_display_16char(charset[15], 0, 6);
}
	*/
}