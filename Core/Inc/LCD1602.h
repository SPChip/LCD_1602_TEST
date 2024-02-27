
#ifndef __LCD1602_H__
#define __LCD1602_H__

#include "stm32f1xx_hal.h"


#define RS_PORT     GPIOB
#define RS_PIN      GPIO_PIN_10
#define RW_PORT     GPIOB
#define RW_PIN      GPIO_PIN_1
#define EN_PORT     GPIOB
#define EN_PIN      GPIO_PIN_0
#define D0_PORT     GPIOA
#define D0_PIN      GPIO_PIN_0
#define D1_PORT     GPIOA
#define D1_PIN      GPIO_PIN_1
#define D2_PORT     GPIOA
#define D2_PIN      GPIO_PIN_2
#define D3_PORT     GPIOA
#define D3_PIN      GPIO_PIN_3
#define D4_PORT     GPIOA
#define D4_PIN      GPIO_PIN_4
#define D5_PORT     GPIOA
#define D5_PIN      GPIO_PIN_5
#define D6_PORT     GPIOA
#define D6_PIN      GPIO_PIN_6
#define D7_PORT     GPIOA
#define D7_PIN      GPIO_PIN_7


void send_to_lcd (char data, int rs);
void lcd_send_cmd (char cmd);
void lcd_send_data (char data);
void lcd_put_cur(int row, int col);
void lcd_init (void);
void lcd_send_string (char *str);
void lcd_clear (void);

#endif // __LCD1602_H__
