// Este startup � usado somenete nos ARM7 com exce��o do LPC2468
// Isto porque usando o startup.c as chamadas de fun��es de dentro de cada fun��o trava o uC

 		.global main
		.global exit
		.extern arm_Init
		.extern irq_Disable
		.extern vic_Init
		
		#if defined(USE_EXT_SRAM) || defined(USE_EXT_SDRAM)
		.extern ramext_Init
		#endif

		#ifdef RTOS_UCLINUX
		.global func_irq_swi
		#endif

		// S�MBOLOS DO LINKER SCRIPT
		.global _stack					// Endere�o inicial da RAM para as STACKS. Topo da RAM
		.global _etext					// Endere�o final da mem�ria de programa. Contendo as sec��es .text(c�digo execut�vel) e .rodata (contantes)
		.global _data					// Endere�o inicial da �rea de RAM da sec��o .data (vari�veis inicializadas)
		.global _edata					// Endere�o final da �rea de RAM da sec��o .data
		.global _bss					// Endere�o inicial da �rea de RAM da sec��o .bss (vari�veis n�o inicializadas)
		.global _ebss					// Endere�o final da �rea de RAM da sec��o .bss

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
// DESABILITA TODAS AS INTERRUP��ES
// -------------------------------------------------------------------------------------------------------------------------
		#if defined (RTOS_NONE)
		bl irq_Disable
		#endif

// -------------------------------------------------------------------------------------------------------------------------
// CONFIGURA PROCESSADOR ARM
// 		AS CONFIGURA��ES DO ARM DEVE SER FEITA ANTES, ISTO PORQUE EM ALGUMAS CONFIGURA��ES ABAIXO PRECISAMOS DO TEMPOS 
//			CALCULADOS PELA FREQUENCIA DO PROCESSADOR
// -------------------------------------------------------------------------------------------------------------------------
		bl	arm_Init

// -------------------------------------------------------------------------------------------------------------------------
// CONFIGURA PROCESSADOR ARM
// 	As configura��es do arm deve ser feita antes, isto porque em algumas configura��es abaixo
//	 necessitam de delays para inicializa��es baseadas na frequencia do processador
// -------------------------------------------------------------------------------------------------------------------------
		#if defined(USE_EXT_SRAM) || defined(USE_EXT_SDRAM)
		// CONFIGURA SRAM e sdram caso for lpc2468
    	bl 	ramext_Init   		
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
#if defined(RUN_MODE1) || defined(RUN_MODE2) || defined (RUN_MODEBOOT1) || defined (RUN_MODEBOOT2)
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
// INICAR O MODO SUPERVISOR PARA O FREERTOS
// -------------------------------------------------------------------------------------------------------------------------
		#if defined (FREE_RTOS) && defined (arm7tdmi)
		// TODO - ainda n�o testada, pode ser que a instru��o assember n�o foi convertida de .S para .C
		// 	Desejamos que a cpu inicie no modo supervisor. A maioria dos OS tempo real tantos os processos do kernel como as tarefas
		//		das aplica��es s�o executadas no modo supervisor
		msr   CPSR_c, #MODE_SVC|IRQ_DISABLE|FIQ_DISABLE
		#endif

// -------------------------------------------------------------------------------------------------------------------------
// INICIALIZA OS CANAIS IRQ VETORADO PARA O ARM7TDMI
// -------------------------------------------------------------------------------------------------------------------------
		#if defined (arm7tdmi)
		bl vic_Init
		#endif

// -------------------------------------------------------------------------------------------------------------------------
// CHAMA O PROGRAMA MAIN SEM PASSAGEM DE PARAMETROS
// -------------------------------------------------------------------------------------------------------------------------		
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
