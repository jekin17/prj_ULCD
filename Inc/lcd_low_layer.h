#ifndef		__LCD_TFT_LOW_LAYER_
#define		__LCD_TFT_LOW_LAYER_

extern unsigned char Bcd_data[5];
extern unsigned int Frame_buf[30][40];

extern unsigned int RGB888_To_RGB565_Convert(unsigned long RGB888);
extern void Bin_To_Bcd(unsigned int Bin_data);
extern void Put_Str_to_Lcd(unsigned int X_pos, unsigned int Y_pos, unsigned char Font_index, const char *Str, unsigned long Txt_color, unsigned long Back_color);
extern void Put_Val_to_Lcd(unsigned int X_pos, unsigned int Y_pos, unsigned char Font_index, unsigned int Bin_data, unsigned long Txt_color, unsigned long Back_color);
extern void Put_Image_to_Lcd(unsigned int X_pos, unsigned int Y_pos, const unsigned int *Img);
#endif
