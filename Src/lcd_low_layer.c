#include "lcd_rm68120_drv.h"
#include "stm32f4xx_hal.h"
#include "lcd_fonts.h"
#include "lcd_low_layer.h"
//#include "fmc.h"


unsigned char Bcd_data[];
//=========================================================================================================//
//=========================================================================================================//
//

void Bin_To_Bcd(unsigned int Bin_data) {
	Bcd_data[0] = ' ';
	Bcd_data[1] = ' ';
	Bcd_data[2] = ' ';
	Bcd_data[3] = ' ';
	Bcd_data[4] = '0';
	if(Bin_data >= 10000) {
		Bcd_data[0]='0';
		Bcd_data[1]='0';
		Bcd_data[2]='0';
		Bcd_data[3]='0';
		Bcd_data[4]='0';
	}	
	while (Bin_data >= 10000) {
		Bin_data -= 10000;
		Bcd_data[0]++;
	}
	if(Bin_data >= 1000) {
		Bcd_data[1]='0';
		Bcd_data[2]='0';
		Bcd_data[3]='0';
		Bcd_data[4]='0';
	}
	while(Bin_data >= 1000) {
		Bin_data -= 1000;
		Bcd_data[1]++;
	}
	if(Bin_data >= 100) {
		Bcd_data[2]='0';
		Bcd_data[3]='0';
		Bcd_data[4]='0';
	}
	while(Bin_data >= 100) {
		Bin_data -= 100;
		Bcd_data[2]++;
	}
	if(Bin_data >= 10) {
		Bcd_data[3]='0';
		Bcd_data[4]='0';
	}
	while(Bin_data >= 10) {
		Bin_data -= 10;
		Bcd_data[3]++;
	}
	Bcd_data[4] += (unsigned char)Bin_data;
}

//=========================================================================================================//
//=========================================================================================================//
//
void Put_Str_to_Lcd(unsigned int X_pos, unsigned int Y_pos, unsigned char Font_index, const char *Str, unsigned long Txt_color, unsigned long Back_color) {	
 unsigned int 	Char_index = 0;															// 
 unsigned char 	Gliph = 0;																//  
 unsigned char 	Gliph_ptr = 0;															// 
 unsigned int 	X_pixel = 0;																// 
 unsigned int 	Y_pixel = 0;																// 								
 unsigned char 	Bit_mask = 0x80;															// 											// 
 unsigned int	X_X, Y_Y;	
 unsigned int 	X = X_pos;
 unsigned int 	Y = Y_pos;
 unsigned int 	Last_X_pos = X_pos;							// Last_X_pos = X_pos - if vertical orientation
 //unsigned int 	Last_Y_pos = Y_pos;						// Last_Y_pos = 0 - if horisontal orientation


	while(*Str!=0x00) {
		Char_index = (unsigned char) *Str;
		Char_index -= Font[Font_index].Font_offset;										/////////////////////
		//Y_pixel = Font[Font_index].Char[Char_index].Image->Gliph_wight;					//
		//X_pixel = Font[Font_index].Char[Char_index].Image->Gliph_height;					//
		Y_pixel = Font[Font_index].Char[Char_index].Image->Gliph_height;					//
		X_pixel = Font[Font_index].Char[Char_index].Image->Gliph_wight;					//
		X = (unsigned char)Last_X_pos;												// - if vertical orientation
		//Y = (unsigned int) Last_Y_pos;													// - if horisontal orientation
		X_X = X + X_pixel-1;
		Y_Y = Y + Y_pixel-1;
		lcdSetWindow(X, X_X, Y, Y_Y);
		lcdSendCmd(reg_WRITE_MEMORY_START);																// 衯鲼 ⡯᭿򼠤鲯즿
		while(Y_pixel != 0x00) {
			while(X_pixel != 0x00) {														// 沫衭塯𥢻񫨫衣𠭨򳠸鱨񨬢ﬠ 㼢泌졮󥰥宮顡鲍
				Gliph = Font[Font_index].Char[Char_index].Image->Gliph[Gliph_ptr];			// 㼡鱠欠︥𥤭褐⡩򠨧᧥ 񨬢ﬠ
				if(Bit_mask != 0x00) {														// 沫衭氰棻񨫨 婠ࡧﭠ⡩򠠯𮤮짠欍						
					if(Gliph & Bit_mask) {	
						lcdSendData(Txt_color);
					}	
					else {
						lcdSendData(Back_color);
					}
					X_pixel--;																// 󬥭𸠥족󸲷骠𨰨񨬢ﬠ
					Bit_mask >>= 1;															// 𬐠嬿 񫥤󾹥䮠⩲ࡨ诡𠦥
				}
				else {
					Bit_mask = 0x80;														// 󱲠쩢᦬ 𬓠嬿 ︥𥤭冷 ⡩򠠨诡𠦥 񨬢ﬠ
					Gliph_ptr++;															// 󢥫鸨㡥졳롧᳥켠- 񫥤󾹨顡᪲ 騮Ⱡ禭鿠񨬢ﬠ
				}	
			}
			Y_pixel--;
			Bit_mask = 0x80;															// 󱲠쩢᦬ 𬓠嬿 ︥𥤭冷 ⡩򠠨诡𠦥 񨬢ﬠ
			Gliph_ptr++;																// 󢥫鸨㡥졳롧᳥켠- 񫥤󾹨顡᪲ 騮Ⱡ禭鿠񨬢ﬠ																		// 
			X_pixel = Font[Font_index].Char[Char_index].Image->Gliph_wight;				//
		}
		//Y_pixel = Font[Font_index].Char[Char_index].Image->Gliph_height; 				//- if horisontal orientation
		Last_X_pos += X_pixel;															//- if vertical orientation	-
		//Last_Y_pos += Y_pixel;														//- if horisontal orientation
		Bit_mask = 0x80;
		Gliph_ptr = 0;
		Str++; 																			// 󢥫鸨㡥졳롧᳥켠嬿 㼡ﱪ衱즤󾹥䮠񨬢ﬠ 駠񲰮먍
	}	
}

void Put_Val_to_Lcd(unsigned int X_pos, unsigned int Y_pos, unsigned char Font_index, unsigned int Bin_data, unsigned long Txt_color, unsigned long Back_color) {
 unsigned int 	Char_index = 0;															// র步󠭠믤 񨬢ﬠ
 unsigned char 	Gliph = 0;																// র步󠭠⡩򠨧᧥ 񨬢ﬠ 
 unsigned char 	Gliph_ptr = 0;															// 񷸲󨪠੪񥫥顤쿠㩤毡󴥰͊
 unsigned int 	X_pixel = 0;																// 讠󥭨󠸨𨭻 񨬢ﬠ
 unsigned int 	Y_pixel = 0;																// 讠󥭨󠢻񮲻 񨬢ﬠ								
 unsigned char 	Bit_mask = 0x80;															// 𬐠嬿 㼡ﱠ ⩲ࡨ硡᪲ࡨ诡𠦥 񨬢ﬠ
 unsigned int	X_X, Y_Y;	
 unsigned int 	X = X_pos;
 unsigned int 	Y = Y_pos;
 //unsigned int 	Last_X_pos = 0;							// Last_X_pos = X_pos - if vertical orientation
 unsigned int 	Last_Y_pos = Y_pos;						// Last_Y_pos = 0 - if vertical orientation
 unsigned char 	Data_index;
 unsigned int 	Pixel_color, Fon_color;
	
	Pixel_color = RGB888_To_RGB565_Convert(Txt_color);
	Fon_color = RGB888_To_RGB565_Convert(Back_color);
	Bin_To_Bcd(Bin_data);
	Data_index = 0;
	while(Data_index <= 4) {
		Char_index = (unsigned char) Bcd_data[Data_index];
		Char_index -= Font[Font_index].Font_offset;										/////////////////////
		Y_pixel = Font[Font_index].Char[Char_index].Image->Gliph_wight;					// 
		X_pixel = Font[Font_index].Char[Char_index].Image->Gliph_height;					// ௫󷥭饠讠󥭨󠢻񮲻 񨬢ﬠ
		//X = (unsigned int)Last_X_pos;
		Y = (unsigned int) Last_Y_pos;													// - if horisontal orientation
		X_X = X + X_pixel-1;
		Y_Y = Y + Y_pixel-1;
		lcdSetWindow(X, X_X, Y, Y_Y);
		lcdSendCmd(reg_WRITE_MEMORY_START);																// 衯鲼 ⡯᭿򼠤鲯즿
		while(Y_pixel != 0x00) {
			while(X_pixel != 0x00) {														// 沫衭塯𥢻񫨫衣𠭨򳠸鱨񨬢ﬠ 㼢泌졮󥰥宮顡鲍
				Gliph = Font[Font_index].Char[Char_index].Image->Gliph[Gliph_ptr];			// 㼡鱠欠︥𥤭褐⡩򠨧᧥ 񨬢ﬠ
				if(Bit_mask != 0x00) {														// 沫衭氰棻񨫨 婠ࡧﭠ⡩򠠯𮤮짠欍
											
					if(Gliph & Bit_mask) {	
						lcdSendData(Pixel_color);
					}	
					else {
						lcdSendData(Fon_color);
					}
					X_pixel--;																// 󬥭𸠥족󸲷骠𨰨񨬢ﬠ
					Bit_mask >>= 1;															// 𬐠嬿 񫥤󾹥䮠⩲ࡨ诡𠦥
				}
				else {
					Bit_mask = 0x80;														// 󱲠쩢᦬ 𬓠嬿 ︥𥤭冷 ⡩򠠨诡𠦥 񨬢ﬠ
					Gliph_ptr++;															// 󢥫鸨㡥졳롧᳥켠- 񫥤󾹨顡᪲ 騮Ⱡ禭鿠񨬢ﬠ
				}	
			}
			Y_pixel--;
			Bit_mask = 0x80;															// 󱲠쩢᦬ 𬓠嬿 ︥𥤭冷 ⡩򠠨诡𠦥 񨬢ﬠ
			Gliph_ptr++;																// 󢥫鸨㡥졳롧᳥켠- 񫥤󾹨顡᪲ 騮Ⱡ禭鿠񨬢ﬠ																		// 
			X_pixel = Font[Font_index].Char[Char_index].Image->Gliph_height;			// ௫󷥭饠讠󥭨󠸨𨭻 񨬢ﬠ
		}
		Y_pixel = Font[Font_index].Char[Char_index].Image->Gliph_wight;
		//Last_X_pos += X_pixel;		//- if vertical orientation	- 
		Last_Y_pos += Y_pixel;			//- if horisontal orientation															
		Bit_mask = 0x80;
		Gliph_ptr = 0;
		Data_index++; 																			// 󢥫鸨㡥졳롧᳥켠嬿 㼡ﱪ衱즤󾹥䮠񨬢ﬠ 駠񲰮먍
	}	
}	

