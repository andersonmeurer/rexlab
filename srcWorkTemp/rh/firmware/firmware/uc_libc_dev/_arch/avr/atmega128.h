#ifndef __ATMEGA128_H
#define __ATMEGA128_H

#include "uc_libdefs.h"
	
// ########################################################################################################################################
// ADC0
#define AD0_INTERRUPT_HANDLER		ISR

// DEFINE O TIPO DE CONVERSÃO DOS DADOS
#define AD0_MODE_NORMAL  			0x00		// Modo não continuo. Tendo necessidade de executar a função adc_StartConvert()
#define AD0_MODE_AUTO 				0x01		// Modo continuo

// DEFINE O TIPO DE ALINHAMENTO DOS DADOS CONVERTIDOS DO ADC
#define AD0_CONVERT_RIGHT  			0x00 		// Dados alinhados a direita
#define AD0_CONVERT_LEFT 			0x01		// Dados alinhados a esquerda

// DEFININDO TIMER DE CLOCK PARA CONVERSÃO, QUANTO MAIOR DIVISÃO MAIOR A PRECISÃO E MAIOR O TEMPO DE CONVERSÃO
#define AD0_PRESCALE_DIV2   		0x00	///< 0x01,0x00 -> CPU clk/2
#define AD0_PRESCALE_DIV4  			0x02	///< 0x02 -> CPU clk/4
#define AD0_PRESCALE_DIV8  			0x03	///< 0x03 -> CPU clk/8
#define AD0_PRESCALE_DIV16  		0x04	///< 0x04 -> CPU clk/16
#define AD0_PRESCALE_DIV32  		0x05	///< 0x05 -> CPU clk/32
#define AD0_PRESCALE_DIV64  		0x06	///< 0x06 -> CPU clk/64
#define AD0_PRESCALE_DIV128 		0x07	///< 0x07 -> CPU clk/128
#define AD0_PRESCALE_MASK  			0x07


// A REFERENCIA DA CONVERSÃO DO ADC É FEITO POR 3 OPÇÕES. 
#define AD0_REFERENCE_AREF   		0x00	// Referencia do adc via pino REF
#define AD0_REFERENCE_AVCC  		0x01	// Referencia do adc via Avcc interno
#define AD0_REFERENCE_256V 			0x03	// Referencia do adc via 2.56V interno
#define AD0_REFERENCE_MASK  		0xC0

// CHANNEL DEFINES (FOR REFERENCE AND USE IN CODE)  THESE CHANNELS SUPPORTED BY ALL AVRS WITH A2D
#define AD0_CHANNEL0   				0x00
#define AD0_CHANNEL1 				0x01
#define AD0_CHANNEL2 				0x02
#define AD0_CHANNEL3 				0x03
#define AD0_CHANNEL4 				0x04
#define AD0_CHANNEL5 				0x05
#define AD0_CHANNEL6 				0x06
#define AD0_CHANNEL7 				0x07
#define AD0_CHANNEL122V 			0x1E	// 1.22V voltage reference
#define AD0_CHANNELAGND 			0x1F	// AGND

// DIFERENTIAL
#define AD0_CHANNEL0_1_DIFF1X 		0x10
#define AD0_CHANNEL1_1_DIFF1X 		0x11
#define AD0_CHANNEL2_1_DIFF1X 		0x12
#define AD0_CHANNEL3_1_DIFF1X 		0x13
#define AD0_CHANNEL4_1_DIFF1X 		0x14
#define AD0_CHANNEL5_1_DIFF1X 		0x15
#define AD0_CHANNEL6_1_DIFF1X 		0x16
#define AD0_CHANNEL7_1_DIFF1X 		0x17
#define AD0_CHANNEL0_2_DIFF1X 		0x18
#define AD0_CHANNEL1_2_DIFF1X 		0x19
#define AD0_CHANNEL2_2_DIFF1X 		0x1A
#define AD0_CHANNEL3_2_DIFF1X 		0x1B
#define AD0_CHANNEL4_2_DIFF1X 		0x1C
#define AD0_CHANNEL5_2_DIFF1X 		0x1D

#define AD0_MUX_MASK  				0x1F

#define AD0_CHANNEL0_0_DIFF10X  	0x08
#define AD0_CHANNEL1_0_DIFF10X 		0x09
#define AD0_CHANNEL0_0_DIFF200X 	0x0A
#define AD0_CHANNEL1_0_DIFF200X 	0x0B
#define AD0_CHANNEL2_2_DIFF10X 		0x0C
#define AD0_CHANNEL3_2_DIFF10X 		0x0D
#define AD0_CHANNEL2_2_DIFF200X 	0x0E
#define AD0_CHANNEL3_2_DIFF200X 	0x0F


// ########################################################################################################################################
// SPI

#define SPI_MODE_SLAVE				0
#define SPI_MODE_MASTER				1

#define SPI_SPEED_F_DIV_4			0
#define SPI_SPEED_F_DIV_16			_BV(SPR0)
#define SPI_SPEED_F_DIV_64			_BV(SPR1)
#define SPI_SPEED_F_DIV_128			_BV(SPR1) | _BV(SPR0)
#define SPI_SPEED_F_DIV_2 			0x80 | SPI_SPEED_F_DIV_4
#define SPI_SPEED_F_DIV_8 			0x80 | SPI_SPEED_F_DIV_16
#define SPI_SPEED_F_DIV_32			0x80 | SPI_SPEED_F_DIV_64

#define SPI_CPHA_1			0
#define SPI_CPHA_2			(1<<2)
#define SPI_CLK_LOW_IDLE 	0
#define SPI_CLK_HIGH_IDLE	(1<<3)
#define SPI_MSB				0
#define SPI_LSB				(1<<5)

#define SPI_INTERRUPT_HANDLER	ISR	// Type of interrupt handler to use for uart interrupts.

// ########################################################################################################################################
// TIMER 0
//u16 __attribute__ ((progmem)) TimerPrescaleFactor[] = {0,1,8,32,64,128,256,1024};
	
// MASCARA DE INTERRUPÇÃO - TIMSK
#define TIMER0_NO_INT 					0x00 		// Sem interrupção
#define TIMER0_ENABLE_INT_OVERFLOW  	0x01 		// TOIE0
#define TIMER0_ENABLE_INT_COMPARE 		0x02 		// OCIE0

// VETOR DE INTERRUPÇÃO
#define TIMER0_VETOR_INT_OVERFLOW  		0			// Indece da função para interrupção de overflow no vetor de interrupções
#define TIMER0_VETOR_INT_COMPARE   		1			// Indece da função para interrupção de comparação no vetor de interrupções
#define TIMER0_NUM_INTERRUPTS			2			// Quantidade de funções de tratamento de interrupções no vetor de interrupções

// PRESCALER - TCCR0	
#define TIMER0_PRESCALE_STOP 			0x00
#define TIMER0_PRESCALE_DIV1 			0x01
#define TIMER0_PRESCALE_DIV8 			0x02
#define TIMER0_PRESCALE_DIV32 			0x03
#define TIMER0_PRESCALE_DIV64 			0x04
#define TIMER0_PRESCALE_DIV128 			0x05
#define TIMER0_PRESCALE_DIV256 			0x06
#define TIMER0_PRESCALE_DIV1024			0x07
#define TIMER0_PRESCALE_MASK 			0x07

// PRESCALER - TCCR0	
#define TIMER0_RTC_CLK_STOP				0x00	///< RTC Timer Stopped
#define TIMER0_RTC_CLK_DIV1				0x01	///< RTC Timer clocked at CPU
#define TIMER0_RTC_CLK_DIV8				0x02	///< RTC Timer clocked at CPU/8
#define TIMER0_RTC_CLK_DIV32			0x03	///< RTC Timer clocked at CPU/32
#define TIMER0_RTC_CLK_DIV64			0x04	///< RTC Timer clocked at CPU/64
#define TIMER0_RTC_CLK_DIV128			0x05	///< RTC Timer clocked at CPU/128
#define TIMER0_RTC_CLK_DIV256			0x06	///< RTC Timer clocked at CPU/256
#define TIMER0_RTC_CLK_DIV1024			0x07	///< RTC Timer clocked at CPU/1024
#define TIMER0_RTC_PRESCALE_MASK		0x07	///< RTC Timer Prescaler Bit-Mask

#define TIMER0_INTERRUPT_HANDLER		ISR		// Type of interrupt handler to use for timer interrupts

// ########################################################################################################################################
// TIMER 1

// MASCARA DE INTERRUPÇÃO - TIMSK
#define TIMER1_NO_INT 					0x00 	// Sem interrupção
#define TIMER1_ENABLE_INT_OVERFLOW 		0x04 	// TOIE1
#define TIMER1_ENABLE_INT_COMPARE_A 	0x10	// OCIE1A
#define TIMER1_ENABLE_INT_COMPARE_B 	0x08 	// OCIE1B
#define TIMER1_ENABLE_INT_COMPARE_C 	0x100 	// OCIE1C
#define TIMER1_ENABLE_INT_CAPTURE 		0x20 	// TICIE1

// VETOR DE INTERRUPÇÃO
#define TIMER1_VETOR_INT_OVERFLOW  		0		// Indece da função para interrupção de overflow no vetor de interrupções
#define TIMER1_VETOR_INT_COMPARE_A 		1		// Indece da função para interrupção A de comparação no vetor de interrupções
#define TIMER1_VETOR_INT_COMPARE_B 		2		// Indece da função para interrupção B de comparação no vetor de interrupções
#define TIMER1_VETOR_INT_COMPARE_C 		3		// Indece da função para interrupção C de comparação no vetor de interrupções
#define TIMER1_VETOR_INT_CAPTURE   		4		// Indece da função para interrupção de captura do pino externo no vetor de interrupções
#define TIMER1_NUM_INTERRUPTS 			5		// Quantidade de funções de tratamento de interrupções no vetor de interrupções

#define TIMER1_OC1A_OFF  				0x00	// Desconecta o pino OC1A da comparação
#define TIMER1_OC1A_CHANGE 				0x40	// Conecta o pino OC1A da comparação modo de troca
#define TIMER1_OC1A_NORMAL 				0x80	// Conecta o pino OC1A da comparação modo não invertido
#define TIMER1_OC1A_INV 				0xC0	// Conecta o pino OC1A da comparação modo invertido
#define TIMER1_OC1A_MASK 				0xC0	// Mascara para configuração das portas OC1A
	
#define TIMER1_OC1B_OFF 				0x00	// Desconecta o pino OC1B da comparação
#define TIMER1_OC1B_CHANGE 				0x10	// Conecta o pino OC1B da comparação modo de troca
#define TIMER1_OC1B_NORMAL 				0x20	// Conecta o pino OC1B da comparação modo não invertido
#define TIMER1_OC1B_INV 				0x30	// Conecta o pino OC1B da comparação modo invertido
#define TIMER1_OC1B_MASK 				0x30	// Mascara para configuração das portas OC1B
	
#define TIMER1_OC1C_OFF 				0x00	// Desconecta o pino OC1C da comparação
#define TIMER1_OC1C_CHANGE 				0x04	// Conecta o pino OC1C da comparação modo de troca
#define TIMER1_OC1C_NORMAL 				0x08	// Conecta o pino OC1C da comparação modo não invertido
#define TIMER1_OC1C_INV 				0x0C	// Conecta o pino OC1C da comparação modo invertido
#define TIMER1_OC1C_MASK 				0x0C	// Mascara para configuração das portas OC1C
		
#define TIMER1_ICP_DDR 					DDRD	// Porta de configuração do pino ICP
#define TIMER1_ICP_PIN 					PD4		// Pino ICP de entrada o gatilho para comparação do Timer1 
#define TIMER1_OC1A_DDR 				DDRB 	// Porta de configuração do pino OC1A
#define TIMER1_OC1A_PIN 				PB5		// Porta de saida do pino OC1A
#define TIMER1_OC1B_DDR 				DDRB	// Porta de configuração do pino OC1B
#define TIMER1_OC1B_PIN  				PB6		// Porta de saida do pino OC1B	
#define TIMER1_OC1C_DDR  				DDRB	// Porta de configuração do pino OC1C
#define TIMER1_OC1C_PIN 				PB7		// Porta de saida do pino OC1C

// PRESCALER - TCCR1B
#define TIMER1_PRESCALE_STOP 			0x00
#define TIMER1_PRESCALE_DIV1 			0x01
#define TIMER1_PRESCALE_DIV8			0x02
#define TIMER1_PRESCALE_DIV64			0x03
#define TIMER1_PRESCALE_DIV256			0x04
#define TIMER1_PRESCALE_DIV1024			0x05
#define TIMER1_PRESCALE_EXT_T1_FALL		0x06
#define TIMER1_PRESCALE_EXT_T1_RISE		0x07
#define TIMER1_PRESCALE_MASK 			0x07

// CONFIGURAÇÃO DO PINO EXTERNO DE CAPTURA
#define TIMER1_ICP_NOISE_CANCELER_ON 	0x80
#define TIMER1_ICP_NOISE_CANCELER_OFF	0x00
#define TIMER1_ICP_FALLING_EDGE 		0x00	// Captura o valor do clock para o registrador ICP durante a borda de descida do pino IC
#define TIMER1_ICP_RISING_EDGE 			0x40	// Captura o valor do clock para o registrador ICP durante a borda de subida do pino IC
#define TIMER1_ICP_MASK 				0xC0

// BITS DE RESOLUÇÃO DO TIMER PARA PWM
#define TIMER1_PWM_MODE_8BITS 			8
#define TIMER1_PWM_MODE_9BITS 			9
#define TIMER1_PWM_MODE_10BITS 			10
	
#define TIMER1_INTERRUPT_HANDLER		ISR		// Type of interrupt handler to use for timer interrupts


// ########################################################################################################################################
// TIMER 2

// MASCARA DE INTERRUPÇÃO - TIMSK
#define TIMER0_NO_INT 					0x00 	// Sem interrupção
#define TIMER2_ENABLE_INT_OVERFLOW  	0x40 	// TOIE2
#define TIMER2_ENABLE_INT_COMPARE 		0x80 	// OCIE2

// VETOR DE INTERRUPÇÃO
#define TIMER2_VETOR_INT_OVERFLOW  		0		// Indece da função para interrupção de overflow no vetor de interrupções
#define TIMER2_VETOR_INT_COMPARE   		1		// Indece da função para interrupção de comparação no vetor de interrupções
#define TIMER2_NUM_INTERRUPTS			2		// Quantidade de funções de tratamento de interrupções no vetor de interrupções

// PRESCALER - TCCR2
#define TIMER2_PRESCALE_STOP			0x00
#define TIMER2_PRESCALE_DIV1			0x01
#define TIMER2_PRESCALE_DIV8			0x02
#define TIMER2_PRESCALE_DIV64			0x03
#define TIMER2_PRESCALE_DIV256			0x04
#define TIMER2_PRESCALE_DIV1024			0x05
#define TIMER2_PRESCALE_EXT_T2_FALL		0x06
#define TIMER2_PRESCALE_EXT_T2_RISE		0x07
#define TIMER2_PRESCALE_MASK 			0x07

#define TIMER2_INTERRUPT_HANDLER		ISR

// ########################################################################################################################################
// TIMER 3

// MASCARA DE INTERRUPÇÃO - TIMSK
#define TIMER3_NO_INT 					0x00 	// Sem interrupção
#define TIMER3_ENABLE_INT_OVERFLOW 		0x04 	// TOIE3
#define TIMER3_ENABLE_INT_COMPARE_A 	0x10 	// OCIE3A
#define TIMER3_ENABLE_INT_COMPARE_B 	0x08 	// OCIE3B
#define TIMER3_ENABLE_INT_COMPARE_C 	0x02 	// OCIE3C
#define TIMER3_ENABLE_INT_CAPTURE 		0x20 	// TICIE3

// VETOR DE INTERRUPÇÃO
#define TIMER3_VETOR_INT_OVERFLOW  		0		// Indece da função para interrupção de overflow no vetor de interrupções
#define TIMER3_VETOR_INT_COMPARE_A 		1		// Indece da função para interrupção A de comparação no vetor de interrupções
#define TIMER3_VETOR_INT_COMPARE_B 		2		// Indece da função para interrupção B de comparação no vetor de interrupções
#define TIMER3_VETOR_INT_COMPARE_C 		3		// Indece da função para interrupção C de comparação no vetor de interrupções
#define TIMER3_VETOR_INT_CAPTURE   		4		// Indece da função para interrupção de captura do pino externo no vetor de interrupções
#define TIMER3_NUM_INTERRUPTS 			5		// Quantidade de funções de tratamento de interrupções no vetor de interrupções

#define TIMER3_OC3A_DDR 				DDRE 	// Porta de configuração do pino OC3A
#define TIMER3_OC3A_PIN 				PE3		// Porta de saida do pino OC3A
#define TIMER3_OC3B_DDR  				DDRE	// Porta de configuração do pino OC3B
#define TIMER3_OC3B_PIN 				PE4		// Porta de saida do pino OC3B
#define TIMER3_OC3C_DDR  				DDRE	// Porta de configuração do pino OC3C
#define TIMER3_OC3C_PIN 				PE5		// Porta de saida do pino OC3C

#define TIMER3_OC3A_OFF  				0x00	// Desconecta o pino OC3A da comparação
#define TIMER3_OC3A_CHANGE 				0x40	// Conecta o pino OC3A da comparação modo de troca
#define TIMER3_OC3A_NORMAL 				0x80	// Conecta o pino OC3A da comparação modo não invertido
#define TIMER3_OC3A_INV 				0xC0	// Conecta o pino OC3A da comparação modo invertido
#define TIMER3_OC3B_OFF 				0x00	// Desconecta o pino OC3B da comparação
#define TIMER3_OC3B_CHANGE 				0x10	// Conecta o pino OC3B da comparação modo de troca
#define TIMER3_OC3B_NORMAL 				0x20	// Conecta o pino OC3B da comparação modo não invertido
#define TIMER3_OC3B_INV 				0x30	// Conecta o pino OC3B da comparação modo invertido
#define TIMER3_OC3C_OFF 				0x00	// Desconecta o pino OC3C da comparação
#define TIMER3_OC3C_CHANGE 				0x04	// Conecta o pino OC3C da comparação modo de troca
#define TIMER3_OC3C_NORMAL 				0x08	// Conecta o pino OC3C da comparação modo não invertido
#define TIMER3_OC3C_INV 				0x0C	// C onecta o pino OC3C da comparação modo invertido
#define TIMER3_OC3A_MASK 				0xC0	// Mascara para configuração das portas OC3A
#define TIMER3_OC3B_MASK 				0x30	// Mascara para configuração das portas OC3B
#define TIMER3_OC3C_MASK 				0x0C	// Mascara para configuração das portas OC3C

#define TIMER3_ICP_DDR 					DDRE	// Porta de configuração do pino ICP
#define TIMER3_ICP_PIN 					PE7		// Pino ICP de entrada o gatilho para comparação do Timer3

// PRESCALER - TCCR3B
#define TIMER3_PRESCALE_STOP 			0x00
#define TIMER3_PRESCALE_DIV1			0x01
#define TIMER3_PRESCALE_DIV8			0x02
#define TIMER3_PRESCALE_DIV64			0x03
#define TIMER3_PRESCALE_DIV256			0x04
#define TIMER3_PRESCALE_DIV1024			0x05
#define TIMER3_PRESCALE_EXT_T1_FALL		0x06
#define TIMER3_PRESCALE_EXT_T1_RISE		0x07
#define TIMER3_PRESCALE_MASK 			0x07

// CONFIGURAÇÃO DO PINO EXTERNO DE CAPTURA
#define TIMER3_ICP_NOISE_CANCELER_ON 	0x80
#define TIMER3_ICP_NOISE_CANCELER_OFF	0x00
#define TIMER3_ICP_FALLING_EDGE 		0x00	// Captura o valor do clock para o registrador ICP durante a borda de descida do pino IC
#define TIMER3_ICP_RISING_EDGE 			0x40	// Captura o valor do clock para o registrador ICP durante a borda de subida do pino IC
#define TIMER3_ICP_MASK 				0xC0

// BITS DE RESOLUÇÃO DO TIMER PARA PWM
#define TIMER3_PWM_MODE_8BITS 			8
#define TIMER3_PWM_MODE_9BITS 			9
#define TIMER3_PWM_MODE_10BITS 			10

#define TIMER3_INTERRUPT_HANDLER		ISR	// Type of interrupt handler to use for timer interrupts

// ########################################################################################################################################
// UART 0
#define UART0_INTERRUPT_HANDLER	ISR // Type of interrupt handler to use for uart interrupts.

// ########################################################################################################################################
// UART 1
#define UART1_INTERRUPT_HANDLER	ISR // Type of interrupt handler to use for uart interrupts.


#endif
