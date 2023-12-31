#ifndef __LCD_FONTS_H
#define __LCD_FONTS_H

//static unsigned char __attribute__ ((progmem)) lcd_fonts[] = { // Com esta declaracao estas constantes s�o armazenadas na ROM e n�o copiadas para RAM
static const u8 lcd_fonts[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// (space)		0
	0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x04,	// !			1
	0x0A, 0x0A, 0x0A, 0x00, 0x00, 0x00, 0x00, 	// "			2
	0x0A, 0x0A, 0x3F, 0x0A, 0x3F, 0x0A, 0x0A,	// #			3
	0x04, 0x0F, 0x14, 0x0E, 0x05, 0x1E, 0x04,	// $			4
	0x19, 0x19, 0x02, 0x04, 0x08, 0x13, 0x03,	// %			5
	0x08, 0x14, 0x14, 0x09, 0x15, 0x12, 0x0D,	// & 			6
	0x06, 0x08, 0x08, 0x10, 0x08, 0x08, 0x06,	// {  Excessao	7
	0x04, 0x08, 0x10, 0x10, 0x10, 0x08, 0x04,	// ( 			8
	0x10, 0x08, 0x04, 0x04, 0x04, 0x08, 0x10,	// ) 			9
	0x04, 0x15, 0x0E, 0x04, 0x0E, 0x15, 0x04,	// * 			10
	0x00, 0x04, 0x04, 0x1F, 0x04, 0x04, 0x00,	// + 			11
	0x00, 0x00, 0x00, 0x00, 0x18, 0x08, 0x10,	// , 			12
	0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00,	// - 			13
	0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18,	// . 			14
	0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x00,	// / 			15
	0x3E, 0x11, 0x13, 0x15, 0x19, 0x10, 0x0E,	// 0 			16
	0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x0E,	// 1 			17
	0x0E, 0x11, 0x01, 0x02, 0x04, 0x08, 0x1F,	// 2 			18
	0x1F, 0x02, 0x04, 0x02, 0x01, 0x11, 0x0E,	// 3 			19
	0x02, 0x06, 0x0A, 0x12, 0x1F, 0x02, 0x02,	// 4 			20
	0x1F, 0x10, 0x1E, 0x01, 0x01, 0x11, 0x0E,	// 5 			21
	0x06, 0x08, 0x10, 0x1E, 0x11, 0x11, 0x0E,	// 6 			22
	0x1F, 0x01, 0x02, 0x02, 0x04, 0x04, 0x04,	// 7 			23
	0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E,	// 8 			24
	0x0E, 0x11, 0x11, 0x0F, 0x01, 0x02, 0x0C,	// 9 			25
	0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00,	// : 			26
	0x00, 0x18, 0x18, 0x00, 0x18, 0x08, 0x00,	// ; 			27
	0x02, 0x04, 0x08, 0x10, 0x08, 0x04, 0x02,	// < 			28
	0x00, 0x00, 0x1F, 0x00, 0x1F, 0x00, 0x00,	// = 			29
	0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10,	// > 			30
	0x0E, 0x11, 0x01, 0x02, 0x04, 0x00, 0x04,	// ? 			31
	0x0E, 0x11, 0x17, 0x15, 0x17, 0x10, 0x0E,	// @ 			32
	0x04, 0x0A, 0x11, 0x11, 0x1F, 0x11, 0x11,	// A 			33
	0x1E, 0x11, 0x11, 0x1E, 0x11, 0x11, 0x1E,	// B 			34
	0x0E, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0E,	// C 			35
	0x1C, 0x12, 0x11, 0x11, 0x11, 0x12, 0x1C,	// D 			36
	0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x1F,	// E 			37
	0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x10,	// F 			38
	0x0E, 0x11, 0x10, 0x17, 0x11, 0x11, 0x0F,	// G 			39	
	0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11,	// H 			40
	0x0E, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E,	// I 			41
	0x07, 0x02, 0x02, 0x02, 0x02, 0x12, 0x0C,	// J 			42
	0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11,	// K  			43
	0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F,	// L  			44
	0x11, 0x1B, 0x15, 0x15, 0x11, 0x11, 0x11,	// M  			45
	0x11, 0x11, 0x19, 0x15, 0x13, 0x11, 0x11,	// N  			46
	0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E,	// O  			47
	0x1E, 0x11, 0x11, 0x1E, 0x10, 0x10, 0x10,	// P  			48
	0x0E, 0x11, 0x11, 0x11, 0x15, 0x12, 0x0D,	// Q  			49
	0x1E, 0x11, 0x11, 0x1E, 0x14, 0x12, 0x11,	// R  			50
	0x0E, 0x11, 0x10, 0x0E, 0x01, 0x11, 0x0E,	// S  			51
	0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,	// T  			52
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E,	// U  			53
	0x11, 0x11, 0x11, 0x11, 0x11, 0x0A, 0x04,	// V  			54
	0x11, 0x11, 0x11, 0x15, 0x15, 0x15, 0x0A,	// W  			55
	0x11, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x11,	// X  			56
	0x11, 0x11, 0x0A, 0x04, 0x04, 0x04, 0x04,	// Y  			57
	0x1F, 0x01, 0x02, 0x04, 0x08, 0x10, 0x1F,	// Z  			58
	0x1C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1C,	// [  			59
	0x00, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00,	// "\"  		60	
	0x1C, 0x04, 0x04, 0x04, 0x04, 0x04, 0x1C,	// ]   			61
	0x18, 0x04, 0x04, 0x02, 0x04, 0x04, 0x18,	// } Excessao  	62		
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F,	// _  			63
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,	// | Excessao  	64		
	0x00, 0x00, 0x0E, 0x01, 0x0F, 0x11, 0x0F,	// a  			65
	0x10, 0x10, 0x1E, 0x11, 0x11, 0x11, 0x1E,	// b  			66
	0x00, 0x00, 0x0F, 0x10, 0x10, 0x10, 0x0F,	// c  			67
	0x01, 0x01, 0x0F, 0x11, 0x11, 0x11, 0x0F,	// d  			68
	0x00, 0x00, 0x0E, 0x11, 0x1F, 0x10, 0x0E,	// e  			69
	0x03, 0x04, 0x1F, 0x04, 0x04, 0x04, 0x04,	// f  			70
	0x00, 0x00, 0x0F, 0x11, 0x0F, 0x01, 0x0E,	// g  			71
	0x10, 0x10, 0x16, 0x19, 0x11, 0x11, 0x11,	// h  			72
	0x04, 0x00, 0x0C, 0x04, 0x04, 0x04, 0x0E,	// i  			73 			
	0x02, 0x00, 0x06, 0x02, 0x02, 0x12, 0x0C,	// j  			74
	0x10, 0x10, 0x12, 0x14, 0x18, 0x14, 0x12,	// k  			75
	0x0C, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E,	// l  			76
	0x00, 0x00, 0x1A, 0x15, 0x15, 0x15, 0x15,	// m  			77
	0x00, 0x00, 0x16, 0x19, 0x11, 0x11, 0x11,	// n  			78
	0x00, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E,	// o  			79
	0x00, 0x00, 0x1E, 0x11, 0x1E, 0x10, 0x10,	// p   			80
	0x00, 0x00, 0x0F, 0x11, 0x0F, 0x01, 0x01,	// q   			81
	0x00, 0x00, 0x0B, 0x0C, 0x08, 0x08, 0x08,	// r   			82
	0x00, 0x00, 0x0E, 0x10, 0x0E, 0x01, 0x1E,	// s  			83
	0x04, 0x04, 0x1F, 0x04, 0x04, 0x04, 0x03,	// t  			84
	0x00, 0x00, 0x11, 0x11, 0x11, 0x13, 0x0D,	// u  			85
	0x00, 0x00, 0x11, 0x11, 0x11, 0x0A, 0x04,	// v  			86
	0x00, 0x00, 0x11, 0x11, 0x15, 0x15, 0x0A,	// w  			87
	0x00, 0x00, 0x11, 0x0A, 0x04, 0x0A, 0x11,	// x  			88
	0x00, 0x00, 0x11, 0x11, 0x0F, 0x01, 0x0E,	// y  			89
	0x00, 0x00, 0x1F, 0x02, 0x04, 0x08, 0x1F,	// z  			90
	//Execes�es
	0x0E, 0x13, 0x15, 0x19, 0x0E, 0x00, 0x00,	// 0 			91
	0x04, 0x0C, 0x04, 0x04, 0x0E, 0x00, 0x00, 	// 1 			92
	0x1F, 0x01, 0x1F, 0x10, 0x1F, 0x00, 0x00, 	// 2 			93
	0x1F, 0x01, 0x0F, 0x01, 0x1F, 0x00, 0x00, 	// 3 			94
	0x11, 0x11, 0x1F, 0x01, 0x01, 0x00, 0x00, 	// 4 			95
	0x1F, 0x10, 0x1F, 0x01, 0x1F, 0x00, 0x00, 	// 5 			
	0x10, 0x10, 0x1F, 0x11, 0x1F, 0x00, 0x00, 	// 6 			 
	0x1F, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 	// 7  			
	0x1F, 0x11, 0x1F, 0x11, 0x1F, 0x00, 0x00, 	// 8  			
	0x1F, 0x11, 0x1F, 0x01, 0x01, 0x00, 0x00,	// 9  			
	0x0E, 0x11, 0x1F, 0x11, 0x11, 0x00, 0x00,	// A  			
	0x1E, 0x11, 0x1E, 0x11, 0x1E, 0x00, 0x00,	// B  			
	0x0F, 0x10, 0x10, 0x10, 0x0F, 0x00, 0x00,	// C  			
	0x1E, 0x11, 0x11, 0x11, 0x1E, 0x00, 0x00,	// D  			
	0x1F, 0x10, 0x1E, 0x10, 0x1F, 0x00, 0x00,	// E  			
	0x1F, 0x10, 0x1E, 0x10, 0x10, 0x00, 0x00,	// F  			
	0x0F, 0x10, 0x17, 0x11, 0x0F, 0x00, 0x00,	// G  			
	0x11, 0x11, 0x1F, 0x11, 0x11, 0x00, 0x00,	// H  			
	0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00,	// I  			
	0x01, 0x01, 0x11, 0x11, 0x1F, 0x00, 0x00,	// J  			
	0x11, 0x12, 0x1C, 0x12, 0x11, 0x00, 0x00,	// K 
	0x10, 0x10, 0x10, 0x10, 0x1F, 0x00, 0x00,	// L 
	0x11, 0x1B, 0x15, 0x11, 0x11, 0x00, 0x00,	// M 
	0x11, 0x19, 0x15, 0x13, 0x11, 0x00, 0x00,	// N 
	0x1F, 0x11, 0x11, 0x11, 0x1F, 0x00, 0x00,	// O 
	0x1F, 0x11, 0x1F, 0x10, 0x10, 0x00, 0x00,	// P 
	0x0E, 0x11, 0x15, 0x12, 0x0D, 0x00, 0x00,	// Q 
	0x1E, 0x11, 0x1E, 0x11, 0x11, 0x00, 0x00,	// R 
	0x0F, 0x10, 0x0E, 0x01, 0x1F, 0x00, 0x00,	// S 
	0x1F, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00,	// T 
	0x11, 0x11, 0x11, 0x11, 0x1F, 0x00, 0x00,	// U 
	0x11, 0x11, 0x11, 0x0A, 0x04, 0x00, 0x00,	// V 
	0x11, 0x11, 0x15, 0x1B, 0x11, 0x00, 0x00,	// W 
	0x11, 0x0A, 0x04, 0x0A, 0x11, 0x00, 0x00,	// X 
	0x11, 0x11, 0x0A, 0x04, 0x04, 0x00, 0x00,	// Y 
	0x1F, 0x02, 0x04, 0x08, 0x1F, 0x00, 0x00,	// Z 
}; 
#endif //Fonts
