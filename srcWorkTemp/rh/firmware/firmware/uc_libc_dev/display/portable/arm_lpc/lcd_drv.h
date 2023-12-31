#ifndef __LCD_DRV_H
#define __LCD_DRV_H

#include "_config_cpu_.h"
#include "_config_cpu_display.h"
#include "delay.h"

#if (LCD_CONNECTION == LCD_CONNECTION_GPIO)
	void lcd_write(u8 reg, u8 rs);
	#define lcd_write_command(reg)	lcd_write(reg, 0)
	#define lcd_write_data(reg)		lcd_write(reg, 1)

	u8 lcd_read(u8 rs);
	#define lcd_read_command()		lcd_read(0)
	#define lcd_read_data()			lcd_read(1)	
	
	void lcd_config_ports(void);
#elif (LCD_CONNECTION == LCD_CONNECTION_IOMAP)
	// ACESSO DIRETO IOMAP RAM
	static volatile u8
		*reg1 = (u8 *) LCD_ADDR_CMD, 	// read status and write command
		*reg2 = (u8 *) LCD_ADDR_DATA; 	// read last address data and write data
#else
	#error N�O FOI DEFINIDO O TIPO DE CONEX�O DO LPC. VEJA _CONFIG_LCD.H
#endif                       
	
#endif
