#include "LCD1602_SPChip.h"
#include "stm32f1xx_hal.h"
#include "stdio.h"

extern TIM_HandleTypeDef htim1;
void delay_us(uint16_t us) {
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	while (__HAL_TIM_GET_COUNTER(&htim1) < us)
		;
}

void LCD_Init(void) {

	// 4 bit initialisation
	HAL_Delay(50);  // wait for >40ms
	LCD_SendCommand(0x30);
	HAL_Delay(5);  // wait for >4.1ms
	LCD_SendCommand(0x30);
	HAL_Delay(1);  // wait for >100us
	LCD_SendCommand(0x30);
	HAL_Delay(10);
	LCD_SendCommand(0x20);  // 4bit mode
	HAL_Delay(10);

	// dislay initialisation
	LCD_SendCommand(0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	LCD_SendCommand(0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off выключаем дисплей
	HAL_Delay(1);
	LCD_SendCommand(0x01); // clear display       очищаем дисплей
	HAL_Delay(1);
	LCD_SendCommand(0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	LCD_SendCommand(0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)

}

void LCD_Put_Cur(int row, int col) {
	switch (row) {
	case 0:
		col |= 0x80;
		break;
	case 1:
		col |= 0xC0;
		break;
	}
	LCD_SendCommand(col);
}



void LCD_Clear(void) {
	LCD_SendCommand(0x01);
	HAL_Delay(2);
}
void LCD_WriteString(char *str) {
	while (*str) {
		LCD_SendData(*str++);
		HAL_Delay(1);
	}
}

void LCD_SendCommand(uint8_t command) {
	LCD_Send(command, 0);
}

void LCD_SendData(uint8_t data) {
	LCD_Send(data, 1);
}

void LCD_Send(uint8_t value, uint8_t mode) {
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, mode); //установка пина в 0 - отправка команды
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, (value >> 4) & 1);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, (value >> 5) & 1);
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, (value >> 6) & 1);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, (value >> 7) & 1);
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET); //установка пина в 0
	delay_us(1);
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);  //установка пина в 1
	delay_us(1);
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET); //установка пина в 0
	delay_us(100);
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, value & 1);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, (value >> 1) & 1);
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, (value >> 2) & 1);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, (value >> 3) & 1);
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET); //установка пина в 0
	delay_us(1);
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);  //установка пина в 1
	delay_us(1);
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET); //установка пина в 0
	delay_us(100);
}

