		.extern main
	
		#ifdef RTOS_UCLINUX
			.extern func_irq_swi
		#endif

		// S�MBOLOS DO LINKER SCRIPT
		.extern _stack					// Endere�o inicial da RAM para as STACKS. Topo da RAM
		.extern _etext					// Endere�o final da mem�ria de programa. Contendo as sec��es .text(c�digo execut�vel) e .rodata (contantes)
		.extern _data					// Endere�o inicial da �rea de RAM da sec��o .data (vari�veis inicializadas)
		.extern _edata					// Endere�o final da �rea de RAM da sec��o .data
		.extern _bss					// Endere�o inicial da �rea de RAM da sec��o .bss (vari�veis n�o inicializadas)
		.extern _ebss					// Endere�o final da �rea de RAM da sec��o .bss

		// CONSTANTES DO STARTUP
		.set  MODE_USR, 0x10            // Modo user
		.set  MODE_FIQ, 0x11            // Modo fiq
		.set  MODE_IRQ, 0x12            // Modo irq
		.set  MODE_SVC, 0x13            // Modo supervisor
		.set  MODE_ABT, 0x17            // Modo abort
		.set  MODE_UND, 0x1B            // Modo undefined
		.set  MODE_SYS, 0x1F            // Modo system

		.equ  IRQ_DISABLE, 0x80         // Quando o bit (I) � setado, IRQ � dasabilitado
		.equ  FIQ_DISABLE, 0x40         // Quando o bit (F) � setado, FIQ � dasabilitado

		.text
		.code 32
		.align 0

// ##########################################################################################################################
// VETORES DE EXCE��ES
// 	O vetor de exe��es deve estar localizadao em um dos 4 locais, FLASH, SRAM interma, BOOT ou mem�ria externa.
// 		o local � especificado no link script junto com registrador MEMAP do ARM
// ##########################################################################################################################
        .global _vector
        .func   _vector

_vector:
		b     _start							// Exce��o de reset. 					Chamar a fun��o _start
		ldr   pc, _undef_addr					// Exce��o indefinida. 					Carrega PC com endere�o da fun��o que tratar� essa exce��o
		ldr   pc, _swi_addr						// Exce��o de interrup��o por software. Carrega PC com endere�o da fun��o que tratar� essa exce��o
		ldr   pc, _pabt_addr					// Exce��o prefetch abort.				Carrega PC com endere�o da fun��o que tratar� essa exce��o
		ldr   pc, _dabt_addr					// Exce��o data abort.					Carrega PC com endere�o da fun��o que tratar� essa exce��o
		nop										// Exce��o reserveda
	#if defined(LPC2468)
		ldr   pc, [pc, #-0x120]					// Exce��o IRQ. 						Carrega PC com endere�o da fun��o contida no registrador VicVectAddr
	#else
		ldr   pc, [pc, #-0xFF0]					// Exce��o IRQ. 						Carrega PC com endere�o da fun��o contida no registrador VicVectAddr
	#endif
		ldr   pc, _fiq_addr						// Exce��o FIQ.							Carrega PC com endere�o da fun��o que tratar� essa exce��o

// DEFININDOS ENDERE�OS DE SALTO
#if defined(RTOS_NONE)
	_undef_addr: .word 	__default_handler         // Captura o endere�o da fun��o padr�o
	_swi_addr:   .word 	__default_handler         // Captura o endere�o da fun��o padr�o
	_pabt_addr:  .word 	__default_handler         // Captura o endere�o da fun��o padr�o
	_dabt_addr:  .word 	__default_handler         // Captura o endere�o da fun��o padr�o
	_fiq_addr:   .word 	__default_handler         // Captura o endere�o da fun��o padr�o
#elif defined(RTOS_UCLINUX)
	_undef_addr: .word 	0x81000004                // Captura o endere�o da fun��o que trata instru��es indefinidas
	_swi_addr:   .word 	0x81000008                // Captura o endere�o da fun��o que trata a interrup��o por software
	_pabt_addr:  .word 	0x8100000C                // Captura o endere�o da fun��o que trata prefetch abort
	_dabt_addr:  .word 	0x81000010                // Captura o endere�o da fun��o que trata data abort
	_fiq_addr:   .word 	0x8100001C                // Captura o endere�o da fun��o que trata interrup��o r�pida
#elif defined(FREE_RTOS)
	_undef_addr: .word 	__default_handler         // Captura o endere�o da fun��o padr�o
	_swi_addr:   .word 	vPortYieldProcessor       // Captura o endere�o da fun��o que trata a interrup��o por software
	_pabt_addr:  .word 	__default_handler         // Captura o endere�o da fun��o padr�o
	_dabt_addr:  .word 	__default_handler         // Captura o endere�o da fun��o padr�o
	_fiq_addr:   .word 	__default_handler 		  // Captura o endere�o da fun��o padr�o
#endif

// FUN��O PADR�O DE SALTO
__default_handler:  b .

        .size _vector, . - _vector
        .endfunc


// ##########################################################################################################################
// PROGRAMA STARTUP QUE SER� EXECUATDO NA EXCE��O RESET
// ##########################################################################################################################
        .global _start
        .func   _start

#ifdef RTOS_UCLINUX
_swiirq:
swiirq:
        ldr   r10,=func_irq_swi
        mov   lr,pc
        bx    r10                       // enter main()
#endif

_start:
// -------------------------------------------------------------------------------------------------------------------------
// CONFIGURA A RAM EXTERNA SE FOR USADA
// -------------------------------------------------------------------------------------------------------------------------
#ifdef USE_EXT_STATIC_RAM
	#if defined(LPC2468)
	
	#else	// PARA O LPC22xx
        .set BCFG0_OFS,    0x00        // BCFG0 Offset
        .set BCFG1_OFS,    0x04        // BCFG1 Offset
        .set BCFG2_OFS,    0x08        // BCFG2 Offset
        .set BCFG3_OFS,    0x0C        // BCFG3 Offset

		// AJUSTA OS PINOS PARA INTERFACEAR COM A RAM
		ldr     R0, =PINSEL_ADDR
       	ldr     R1, =PINSEL_VALUE
        str     R1, [R0]
 
 		// CONFIGURA O BARRAMENTO
 		ldr     R0, =BCFG_BASE

        ldr     R1, =BCFG0_VALUE
        str     R1, [R0, #BCFG0_OFS]
        ldr     R1, =BCFG1_VALUE
        str     R1, [R0, #BCFG1_OFS]
        ldr     R1, =BCFG2_VALUE
        str     R1, [R0, #BCFG2_OFS]
        ldr     R1, =BCFG3_VALUE
        str     R1, [R0, #BCFG3_OFS]
	#endif
#endif

// -------------------------------------------------------------------------------------------------------------------------
// AJUSTANDO OS STACKS DE CADA MODO DE OPERA��O DO PROCESSADOR ARM
// -------------------------------------------------------------------------------------------------------------------------
		ldr   r0, =_stack
		
		// STACK PARA MODO FIQ
		msr   CPSR_c, #MODE_FIQ|IRQ_DISABLE|FIQ_DISABLE
		mov   sp, r0
		sub   r0, r0, #FIQ_STACK_SIZE
		
		// STACK PARA MODO IRQ
		msr   CPSR_c, #MODE_IRQ|IRQ_DISABLE|FIQ_DISABLE
		mov   sp, r0
		sub   r0, r0, #IRQ_STACK_SIZE
		
		// STACK PARA MODO SUPERVISOR
		msr   CPSR_c, #MODE_SVC|IRQ_DISABLE|FIQ_DISABLE
		mov   sp, r0
		sub   r0, r0, #SVC_STACK_SIZE
		
		// STACK PARA MODO INDEFINIDO
		msr   CPSR_c, #MODE_UND|IRQ_DISABLE|FIQ_DISABLE
		mov   sp, r0
		sub   r0, r0, #UND_STACK_SIZE
		
		// STACK PARA MODO ABORTO
		msr   CPSR_c, #MODE_ABT|IRQ_DISABLE|FIQ_DISABLE
		mov   sp, r0
		sub   r0, r0, #ABT_STACK_SIZE
		
		// STACK PARA MODO DE SISTEMA E USU�RIO
		msr   CPSR_c, #MODE_SYS|IRQ_DISABLE|FIQ_DISABLE
		mov   sp, r0

// -------------------------------------------------------------------------------------------------------------------------
// ATRIBUI OS VALORES INICIAIS DAS VARI�VEIS DA SEC��O .data
// -------------------------------------------------------------------------------------------------------------------------
#ifdef ROM_RUN
        ldr   r0,=_etext               			// Endere�o final da sec��o .text e .rodata. Onde cont�m os valores da vari�veis inicializadas
        ldr   r1,=_data                			// Endere�o inicial da �rea de RAM da sec��o .data (vari�veis inicializadas)
        ldr   r2,=_edata                		// Endere�o final da �rea de RAM da sec��o .data
_copy_data:      
		cmp   r1,r2                     		 
        ldrne r3,[r0],#4                		
        strne r3,[r1],#4
        bne   _copy_data                    	
#endif

// -------------------------------------------------------------------------------------------------------------------------
// LIMPA A �REA DE RAM DAS VARI�VEIS N�O INICIALIZADAS
// -------------------------------------------------------------------------------------------------------------------------
        ldr   r0, =0                     		// Pega o valor 0
        ldr   r1, =_bss         				// Endere�o inicial da �rea de RAM da sec��o .bss (vari�veis n�o inicializadas)
        ldr   r2, =_ebss           				// Endere�o final da �rea de RAM da sec��o .bss
_clear_bss:      
		cmp   r1,r2                    		 	// check if data to clear
        strne r0,[r1],#4                		// clear 4 bytes
        bne   _clear_bss                   		// loop until done


// -------------------------------------------------------------------------------------------------------------------------
//
// -------------------------------------------------------------------------------------------------------------------------
#ifndef RTOS_UCLINUX
		// 	Desejamos que a cpu inicie no modo supervisor. 
		// 	O sistema operacional ir� para modo system quando iniciar a primeira tarefa
		msr   CPSR_c, #MODE_SVC|IRQ_DISABLE|FIQ_DISABLE
#endif

// -------------------------------------------------------------------------------------------------------------------------
// CHAMA O PROGRAMA MAIN SEM PASSAGEM DE PARAMETROS
// -------------------------------------------------------------------------------------------------------------------------
		#ifdef USE_MY_SYSCALL
			bl	syscalls_Init					// Incializa syscalls newlib
		#endif
		
        mov   r0,#0                    			// Sem argumentos (argc = 0)
        mov   r1,r0
        mov   r2,r0
        mov   fp,r0                     		// null frame pointer
        mov   r7,r0                     		// null frame pointer for thumb
        ldr   r10,=main
        mov   lr,pc
   
        bx    r10                       		// Entra no c�digo C (main()). Utilize  a instru��o BX para nunca voltar
        										// Utilize BLX (?) se voce deseja usar o c++

		.size   _start, . - _start
        .endfunc
	
		.end
