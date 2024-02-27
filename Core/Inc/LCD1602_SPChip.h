#ifndef __LCD1602_SPChip_H__
#define __LCD1602_SPChip_H__

#include "stm32f1xx_hal.h"

#define D4_Pin GPIO_PIN_4
#define D4_GPIO_Port GPIOA
#define D5_Pin GPIO_PIN_5
#define D5_GPIO_Port GPIOA
#define D6_Pin GPIO_PIN_6
#define D6_GPIO_Port GPIOA
#define D7_Pin GPIO_PIN_7
#define D7_GPIO_Port GPIOA
#define EN_Pin GPIO_PIN_0
#define EN_GPIO_Port GPIOB
#define RS_Pin GPIO_PIN_1
#define RS_GPIO_Port GPIOB

void LCD_Init(void);
void LCD_Put_Cur(int row, int col);
void LCD_SendCommand(uint8_t command);
void LCD_SendData(uint8_t data);
void LCD_Send(uint8_t value, uint8_t mode);
void LCD_Clear(void);
void LCD_WriteString(char* str);

























#endif // __LCD1602_SPChip_H__
