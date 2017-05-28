#include <lcd_rm68120_drv.h>
#include "stm32f4xx_hal.h"
#include "lcd_low_layer.h"






//=====================================================================================================//
void lcdResetHW(void)
{
	HAL_GPIO_WritePin(lcd_RESET_GPIO_Port, lcd_RESET_Pin, GPIO_PIN_SET);						// ����� � ���������� ��������� ������
	HAL_Delay(1);																				// ��������
	HAL_GPIO_WritePin(lcd_RESET_GPIO_Port, lcd_RESET_Pin, GPIO_PIN_RESET);						// ����� � �������� ��������� ������
	HAL_Delay(2);																				// ������������� ������
	HAL_GPIO_WritePin(lcd_RESET_GPIO_Port, lcd_RESET_Pin, GPIO_PIN_SET);						// ����� � ���������� ��������� ������
	HAL_Delay(120);																				// �������� ����������� ������ �������
}
//=====================================================================================================//
void lcdInit(void)
{
	lcdResetHW();
	lcdSendCmd(reg_SOFT_RES);
	lcdSendCmd(reg_EXIT_SLEEP_MODE);
	lcdSendCmd(reg_SET_DISPLAY_ON);
	lcdSendCmd(reg_SET_PIXEL_FORMAT);
	lcdSendData(0xff);
	lcdSendData(0b00000101);
	lcdSendCmd(0x2C00);
	lcdClrArea(0,480,0,800);
}
//=====================================================================================================//
void lcdSetWindow(unsigned int xSP, unsigned int xEP, unsigned int ySP, unsigned int yEP)
{
	lcdSendCmd(reg_SET_COLUMN_ADDRESS);
	lcdSendData((unsigned char)(xSP >> 8));
	lcdSendCmd(reg_SET_COLUMN_ADDRESS+1);
	lcdSendData((unsigned char) xSP);
	lcdSendCmd(reg_SET_COLUMN_ADDRESS+2);
	lcdSendData((unsigned char)(xEP >> 8));
	lcdSendCmd(reg_SET_COLUMN_ADDRESS+3);
	lcdSendData((unsigned char) xEP);
	lcdSendCmd(reg_SET_PAGE_ADDRESS);
	lcdSendData((unsigned char)(ySP >> 8));
	lcdSendCmd(reg_SET_PAGE_ADDRESS+1);
	lcdSendData((unsigned char) ySP);
	lcdSendCmd(reg_SET_PAGE_ADDRESS+2);
	lcdSendData((unsigned char)(yEP >> 8));
	lcdSendCmd(reg_SET_PAGE_ADDRESS+3);
	lcdSendData((unsigned char) yEP);
}

//=====================================================================================================//
void lcdClrArea(unsigned int xSP, unsigned int xEP, unsigned int ySP, unsigned int yEP)
{
unsigned int Pixels;
	
	Pixels = ((xEP+1) - xSP) * ((yEP+1) - ySP);
	lcdSetWindow(xSP, xEP, ySP, yEP);							// устновить область для вывода
	lcdSendCmd(reg_WRITE_MEMORY_START);										// команда на запись фрейма
	for( ; Pixels > 0; Pixels--)
	{
		lcdSendData(WHITE);
	}
}
//=====================================================================================================//
void lcdSetFonColorArea(unsigned int xSP, unsigned int xEP, unsigned int ySP, unsigned int yEP, unsigned long color)
{
unsigned int Pixels;
unsigned char R, G, B;	
unsigned int Pixel_color;
	
	Pixel_color = color;
	Pixels = ((xEP+1) - xSP) * ((yEP+1) - ySP);
	lcdSetWindow(xSP, xEP, ySP, yEP);						// устновить область для вывода
	lcdSendCmd(reg_WRITE_MEMORY_START);									// команда на запись фрейма
	do
	{
		lcdSendData(Pixel_color);
	}
	while(--Pixels);
}
//=====================================================================================================//
void lcdDaving(unsigned int xSP, unsigned int xEP, unsigned int ySP, unsigned int yEP)
{
	LCD_Set_Window(xSP, xEP, ySP, yEP);						// устновить область для вывода
	lcdSendCmd(reg_WRITE_MEMORY_START);									// команда на запись фрейма
}
