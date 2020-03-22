#ifndef _LCD_H
#define _LCD_H

#define uchar unsigned char 
#define uint unsigned int
#define ulong unsigned long

	
#define LCD_SID GPIO_Pin_7
#define LCD_SCK GPIO_Pin_6
#define LCD_A0 GPIO_Pin_5
#define LCD_RST GPIO_Pin_4
#define LCD_CS GPIO_Pin_3

void lcd_init(void);
void delay(uint ms);
void write_cmd( uchar Cbyte );
void write_data( uchar Dbyte );
void LcmClear(void);
void  zifu16x16xian(void);
void  zifu8x16xian(void);
void  dianxian(void);
void  jishuxian(void);
void  oshuxian(void);
void  jihengxian(void);
void  ohengxian(void);
void  PUTBMP(uchar *put);
void  PUTREVERSEBMP(uchar *put);
void display_name(void);
void show_bad_apple(void);
void lcd_show_8X16char(uchar dat, uchar row, uchar col);
void lcd_show_8X16string(uchar *dat, uchar row, uchar col);

void lcd_test(void);

#endif
