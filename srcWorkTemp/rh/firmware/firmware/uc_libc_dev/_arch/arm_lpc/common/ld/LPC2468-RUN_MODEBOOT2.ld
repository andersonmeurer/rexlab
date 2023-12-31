/*
	Linkscrit para o bootloader
	Este linkscript gera c�digo para ser rodado no final da mem�ria FLASH interna do ARM
	e utilizando os vetores de interrup��es na SRAM interna
	O STACK POINT vai ser compensado para usar as fun��es IAP do bootROM
	ATEN��O. O compilador ainda aloca os vetores de interrup��es na mem�ria FLASH
		No pr�prio bootloader transferimos o conte�do dos vetores para a SRAM e
			depois chaveamos para SRAM (MEMMAP=2)
*/

/* Indica o ponto de entada. O nosso ponto de entrada esta no STARTUP fun��o _vector */
ENTRY(_vector)

/* ############################################################################################################ */
/* DEFININDO MAPA DE MEM�RIA																					*/
/* ############################################################################################################ */
/* Endere�os s�o em bytes */
/* Para mais informa��es sobre setores e endere�os da FLASH 
   consulte o datasheet do lpc2468 sec��o Sector Number p�gina 681 */

/* Reservado os �ltimos 88KB da FLASH para o bootloader */
MEMORY {
	FLASH_VECTOR  	(rx)	: ORIGIN = 0x00000000, LENGTH = 416k	/* Local da FLASH interna para o vetores de inst */
	FLASH  			(rx)	: ORIGIN = 0x00068000, LENGTH = 84k		/* Local da FLASH interna para o bootloader */
	DATASTORE		(rw)	: ORIGIN = 0x0007D000, LENGTH = 4k		/* Local da FLASH interna para o DATASTORE */
	RAM				(rw)	: ORIGIN = 0x40000040, LENGTH = 64k	 	/* Local da SRAM interna para o bootloader */
																	/*	Defendendo os vetores de interrup��es */
	
}

/* ############################################################################################################ */
/* DEFININDO STACK - Levar em considera��o da utiliza��o de ferramentas para debug, pois elas usam RAM interna	*/
/* ############################################################################################################ */
/* Definindo o stack point no topo da mem�ria interna */
/* Vamos descontar 64 bytes por causa do deslocamento da SRAM 
	para defender o vetor de exec��es */
/* e como o bootloader vai trabalhar com IAP � preciso reservar 
	32 bytes do topo da RAM para suas fun��es */
_stack = ORIGIN(RAM) + LENGTH(RAM) - 96;

/* ############################################################################################################ */
/* DEFININDO inicio dos vetores de exce��es e de programa na FLASH
/* ############################################################################################################ */
_ivector = ORIGIN(FLASH_VECTOR);
_itext = ORIGIN(FLASH);
_idatastore = ORIGIN(DATASTORE);

/* ############################################################################################################ */
/* DEFININDO SEC��ES DE MEM�RIA																					*/
/* ############################################################################################################ */
SECTIONS {
	/* -------------------------------------------------------------------------------------------------------- */
	/* SEC��O .vector para os vetores de exce��es no inicio da FLASH											*/
	/* -------------------------------------------------------------------------------------------------------- */
	.vector : {
		*vectors_arm7tdmi.o (.text)	/* Tabela de vetores de exece��es do ARM */
	} > FLASH_VECTOR
	. = ALIGN(4);
	_evector = . ; /* Capturando o endere�o final do vetor de interrup��o*/
	
	/* -------------------------------------------------------------------------------------------------------- */
	/* SEC��O .text C�DIGO EXECUTAVEL																			*/
	/* -------------------------------------------------------------------------------------------------------- */
	.text : {
		*startup.o (.text)  /* C�digo de inicializa��o do processador */
		*(.text)
		/* *(.gnu.linkonce.t.*) */
		*(.glue_7)
		*(.glue_7t)
	/* *(.gcc_except_table) */
	} > FLASH
	. = ALIGN(4);
	
	/* -------------------------------------------------------------------------------------------------------- */
	/* SEC��O .rodata (somente leitura (constantes) vari�veis inicializadas) 									*/
	/* -------------------------------------------------------------------------------------------------------- */
	.rodata : {
		*(.rodata)	                 
		*(.rodata*)	
		/* *(.gnu.linkonce.r.*) */
	} > FLASH
	. = ALIGN(4);
  
	_etext = . ;
	
	/* -------------------------------------------------------------------------------------------------------- */
	/*  SEC��O .data (dados de leitura e escrita) LOCAL DAS VARIAVEIS INCIALIZADAS								*/
	/* 		Os valores das varaiaveis inicalizadas est�o armazenados na FLASH ap�s (.rodata).    		    	*/
	/* 		O STARTUP copia os valores da FLASH a partir do endere�o _etext para a RAM entre os        			*/
	/*		os endere�os _data e _edata														    				*/
	/* -------------------------------------------------------------------------------------------------------- */
	.data : AT (_etext) {
		_data = .;
		*(.data)
		*(.data.*)
		/* 	*(.gnu.linkonce.d*) */
		/* SORT(CONSTRUCTORS) */ /* mt 4/2005 */
		/* . = ALIGN(4); */
		/*  *(.fastrun) */ /* !!!! "RAM-Function" example */
	} > RAM
 
	. = ALIGN(4);
	_edata = . ;
	

	/* -------------------------------------------------------------------------------------------------------- */
	/* SEC��O .bss LOCAL DAS VARIAVEIS N�O INICIALIZAS															*/
	/*		Os s�mbolos definem os endere�os da RAM para serem limpas pelo STARTUP								*/
	/* -------------------------------------------------------------------------------------------------------- */
	.bss : {
		_bss = .;
		*(.bss)
		/* *(.gnu.linkonce.b*) */
		*(COMMON)
	} > RAM

	. = ALIGN(4);
	_ebss = . ;	
	_end = . ;
	PROVIDE (end = .);

  	/* -------------------------------------------------------------------------------------------------------- */
	/* SEC��O DE DEBUG																						    */
	/* -------------------------------------------------------------------------------------------------------- */
	.stab          0 : { *(.stab) }
	.stabstr       0 : { *(.stabstr) }
	.stab.excl     0 : { *(.stab.excl) }
	.stab.exclstr  0 : { *(.stab.exclstr) }
	.stab.index    0 : { *(.stab.index) }
	.stab.indexstr 0 : { *(.stab.indexstr) }
	.comment       0 : { *(.comment) }
	/* DWARF debug sections.
		Symbols in the DWARF debugging sections are relative to the beginning
		of the section so we begin them at 0.  */
	/* DWARF 1 */
	.debug          0 : { *(.debug) }
	.line           0 : { *(.line) }
	/* GNU DWARF 1 extensions */
	.debug_srcinfo  0 : { *(.debug_srcinfo) }
	.debug_sfnames  0 : { *(.debug_sfnames) }
	/* DWARF 1.1 and DWARF 2 */
	.debug_aranges  0 : { *(.debug_aranges) }
	.debug_pubnames 0 : { *(.debug_pubnames) }
	/* DWARF 2 */
	.debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
	.debug_abbrev   0 : { *(.debug_abbrev) }
	.debug_line     0 : { *(.debug_line) }
	.debug_frame    0 : { *(.debug_frame) }
	.debug_str      0 : { *(.debug_str) }
	.debug_loc      0 : { *(.debug_loc) }
	.debug_macinfo  0 : { *(.debug_macinfo) }
	/* SGI/MIPS DWARF 2 extensions */
	.debug_weaknames 0 : { *(.debug_weaknames) }
	.debug_funcnames 0 : { *(.debug_funcnames) }
	.debug_typenames 0 : { *(.debug_typenames) }
	.debug_varnames  0 : { *(.debug_varnames) }
}
