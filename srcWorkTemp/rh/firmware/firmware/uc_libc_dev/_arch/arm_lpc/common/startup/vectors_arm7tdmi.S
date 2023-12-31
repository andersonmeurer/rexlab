		.text
		.code 32
		.align 0

        .global _vector
        .func   _vector

_vector:
		b     _start							// Exce��o de reset. 					Chamar a fun��o _start
		ldr   pc, _undef_addr					// Exce��o indefinida. 					Carrega PC com endere�o da fun��o que tratar� essa exce��o
		ldr   pc, _swi_addr						// Exce��o de interrup��o por software. Carrega PC com endere�o da fun��o que tratar� essa exce��o
		ldr   pc, _pabt_addr					// Exce��o prefetch abort.				Carrega PC com endere�o da fun��o que tratar� essa exce��o
		ldr   pc, _dabt_addr					// Exce��o data abort.					Carrega PC com endere�o da fun��o que tratar� essa exce��o
		nop										// Exce��o reservada para Checksum
		ldr   pc, _irq_addr						// Exce��o IRQ. 						Carrega PC com endere�o da fun��o contida no registrador VicVectAddr
		ldr   pc, _fiq_addr						// Exce��o FIQ.							Carrega PC com endere�o da fun��o que tratar� essa exce��o

// DEFININDOS ENDERE�OS DE SALTO
#if defined(RTOS_NONE)
	_undef_addr: .word 	vectorUndefHandler      	// Captura o endere�o da fun��o que trata instru��es indefinidas
	_swi_addr:   .word 	vectorSwiHandler       		// Captura o endere�o da fun��o que trata a interrup��o por software
	_pabt_addr:  .word 	vectorPrefetchAbortHandler  // Captura o endere�o da fun��o que trata prefetch abort
	_dabt_addr:  .word 	vectorDataAbortHandler      // Captura o endere�o da fun��o que trata data abort
	_irq_addr:   .word 	vectorIrqHandler          	// Captura o endere�o da fun��o que trata interrup��o IRQ
	_fiq_addr:   .word 	vectorFiqHandler 			// Captura o endere�o da fun��o que trata interrup��o FIQ
#elif defined(RTOS_UCLINUX)
	_undef_addr: .word 	0x81000004                	// Captura o endere�o da fun��o que trata instru��es indefinidas
	_swi_addr:   .word 	0x81000008                	// Captura o endere�o da fun��o que trata a interrup��o por software
	_pabt_addr:  .word 	0x8100000C                	// Captura o endere�o da fun��o que trata prefetch abort
	_dabt_addr:  .word 	0x81000010                	// Captura o endere�o da fun��o que trata data abort
	_irq_addr:   .word 	0x81000018                	// Captura o endere�o da fun��o que trata interrup��o IRQ
	_fiq_addr:   .word 	0x8100001C                	// Captura o endere�o da fun��o que trata interrup��o r�pida
#elif defined(FREE_RTOS)
	_undef_addr: .word 	vectorUndefHandler      	// Captura o endere�o da fun��o que trata instru��es indefinidas
	_swi_addr:   .word 	vPortYieldProcessor       	// Captura o endere�o da fun��o que trata a interrup��o por software
	_pabt_addr:  .word 	vectorPrefetchAbortHandler  // Captura o endere�o da fun��o que trata prefetch abort
	_dabt_addr:  .word 	vectorDataAbortHandler      // Captura o endere�o da fun��o que trata data abort
	_irq_addr:   .word 	vectorIrqHandler          	// Captura o endere�o da fun��o que trata interrup��o IRQ
	_fiq_addr:   .word 	vectorFiqHandler 			// Captura o endere�o da fun��o que trata interrup��o FIQ
#endif
		.end
