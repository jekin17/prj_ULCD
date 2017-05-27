#ifndef	__LCD_rm68120_DRIVER_H
#define	__LCD_rm68120_DRIVER_H
//=====================================================================//
//LCD_BL		PA8				lcd(backlight)_pin
//LCD_RES		PG15			lcd(reset)_pin
//NE4			PG12
//nOE			PD4				out(en)_pin
//nWE			PD5				write(en)_pin
//A0			PF0				cmd/data_pin
//D0			PD14
//D1			PD15
//D2			PD0
//D3			PD1
//D4			PE7
//D5			PE8
//D6			PE9
//D7			PE10
//D8			PE11
//D9			PE12
//D10			PE13
//D11			PE14
//D12			PE15
//D13			PD8
//D14			PD9
//D15			PD10

#define		LCD_D				(*((volatile uint16_t*) 0x6C000002))			// nc4 для выбора LCD в режими данные (ВАЖНО!!! в 16-bit режиме шины адреса (A24:A1) смещены на 1 бит влево!!!)
#define		LCD_R			 	(*((volatile uint16_t*) 0x6C000000))			// nc4 для выбора LCD в режими комада

#define		lcdSendCmd(Index) 		(LCD_R = Index)
#define		lcdSendData(Data)		(LCD_D = Data)
#define		lcdGetData()			(LCD_D)
#define		LCD_BL_On			(GPIOA->BSRR |= GPIO_BSRR_BS8)
//******************************************************************//
#define		reg_NOP											0x0000
#define		reg_SOFT_RES									0x0100
//#define		reg_READ_DDB_START							0x04
#define		reg_GET_POWER_MODE								0x0A00
#define		reg_GET_ADDRESS_MODE							0x0B00
#define		reg_PIXEL_FORMAT								0x0C00
#define		reg_GET_DISPLAY_MODE							0x0D00
#define		reg_GET_SIGNAL_MODE								0x0E00
#define		reg_GET_DIAGNOSTIC_RESULT						0x0F00
#define		reg_ENTER_SLEEP_MODE							0x1000
#define		reg_EXIT_SLEEP_MODE								0x1100
#define		reg_ENTER_PARTIAL_MODE							0x1200
#define		reg_ENTER_NORMAL_MODE							0x1300
#define		reg_EXIT_INVERT_MODE							0x2000
#define		reg_ENTER_INVERT_MODE							0x2100
#define		reg_SET_DISPLAY_OFF								0x2800
#define		reg_SET_DISPLAY_ON								0x2900
#define		reg_SET_COLUMN_ADDRESS							0x2A00
#define		reg_SET_PAGE_ADDRESS							0x2B00
#define		reg_WRITE_MEMORY_START							0x2C00
#define		reg_READ_MEMORY_START							0x2E00
#define		reg_SET_PARTIAL_AREA							0x3000
#define		reg_SET_SCROLL_AREA								0X3300
#define		reg_SET_TEAR_OFF								0x3400
#define		reg_SET_TEAR_ON									0x3500
#define		reg_SET_ADDRESS_MODE							0x3600
#define		reg_SET_SCROLL_START							0x3700
#define		reg_EXIT_IDLE									0x3800
#define		reg_ENTER_IDLE_MODE								0x3900
#define		reg_SET_PIXEL_FORMAT							0x3A00
#define		reg_WRITE_MEMORY_CONTINUE						0x3C00
#define		reg_READ_MEMORY_CONTINUE						0x3E00
#define		reg_SET_TEAR_SCANLINE							0x4400
#define		reg_GET_SCANLINE								0x4500
#define		reg_READ_DDB_START								0xA100
#define		reg_READ_DDB_CONTINUE							0xA800
//ADDITIONAL USER COMMAND
#define		reg_MANUFACTURE_COMMAND_ACCSESS_PROTECT			0xB000
#define		reg_LPM_CONTROL									0xB100
#define		reg_FRAME_MEMOMORY_ACCSESS_INTERFACE_SETING		0xB300
#define		reg_DISPLAY_MODE_FRAME_MEMORY_WRITE_MODE_SETING	0xB400
#define		reg_PANEL_DRIVING_SETING						0xC000
#define		reg_DISPLAY_TIMING_SETTING_FOR_NORMAL_MODE		0xC100
#define		reg_DISPLAY_TIMING_SETTING_FOR_PARTIAL_MODE		0xC200
#define		reg_DISPLAY_TIMING_SETTING_FOR_IDLE_MODE		0xC300
#define		reg_SOURCE_VCOM_GATE_DRIVING_TIMING_SITTING		0xC400
#define		reg_INTERFACE_SETTING							0xC600
#define		reg_GAMMA_CONTROL								0xC800
#define		reg_POWER_SETTING								0xD000
#define		reg_VCOM_SETTING								0xD100
#define		reg_POWER_SETTING_FOR_NORMAL_MODE				0xD200
#define		reg_POWER_SETTING_FOR_PARTIAL_MODE				0xD300
#define		reg_POWER_SETTING_FOR_IDLE_MODE					0xD400

#define		reg_ID1											0xDA00
#define		reg_ID2											0xDB00
#define		reg_ID3											0xDC00
//******************************************************************//

#define		RED												0b1111100000000000
#define		GREEN											0b0000011111100000
#define		BLUE											0b0000000000011111
#define		MAGNETO											0b1111100000011111
#define		YELLOW											0b1111111111100000
#define		CYAN											0b0000011111111111
#define		WHITE											0b1111111111111111
#define		BLACK											0b0
//******************************************************************//
extern void lcdResetHW(void);
extern void lcdInit(void);
extern void lcdSetWindow(unsigned int xSP, unsigned int xEP, unsigned int ySP, unsigned int yEP);
extern void lcdClrArea(unsigned int xSP, unsigned int xEP, unsigned int ySP, unsigned int yEP);
extern void lcdSetFon_Color_Area(unsigned int xSP, unsigned int xEP, unsigned int ySP, unsigned int yEP, unsigned long color);
extern void lcdDaving(unsigned int xSP, unsigned int xEP, unsigned int ySP, unsigned int yEP);
//=====================================================================//
#endif
