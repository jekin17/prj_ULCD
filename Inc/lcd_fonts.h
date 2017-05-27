#ifndef		__LCD_FONTS_
#define		__LCD_FONTS_
//=====================================================================//
/* select desired fonts. (Simply comment out those not needed) */
typedef struct {											// 񲰳볳𠠨诡𠦥 񨬢ﬠ
	const char* Gliph;										// 󪠧᳥켠𬕢𸁩򮢠騮Ⱡ禭鿠񨬢ﬠ
	unsigned char Gliph_wight;								// 𨰨騮Ⱡ箨󠱨񋠠⡡鳠񠍊	 
	unsigned char Gliph_height;								// 㼱ﳠ 騮Ⱡ禭鿠񨬢ﬠ ⡡鳠񍊽 
} tImage;	

typedef struct {											// 񲰳볳𠠱魢ﬠ
    unsigned int Code;										// 믤 񨬢ﬠ
    const tImage* Image;									// 󪠧᳥켠񲰳볳𳠨诡𠦥 񨬢ﬠ 
} tChars;

typedef struct {											// 񲰳볳𠠸𨴲͊    
	unsigned int Length;									// 믫鸥񲢮 񨬢אַ⡢ 𰨴򥍊    
	unsigned int Font_offset;
    const tChars* Char;										// 󪠧᳥켠񲰳볳𳠨硬Ჱ飠 񲰳볳𠱨񋯢
} tFonts;


extern const tFonts Font[];									// 񲰳볳𠠸𨴲͊
extern const tChars Char[];									// 𬕢𸆋𜳳𠱨񋯢
extern const tImage Image;									// 񲰳볳𠠨诡𠦥 񨬢ﬠ


#define	Eng				0
//#define	Rus				1
#define	Digit				1

//=====================================================================//
#endif
