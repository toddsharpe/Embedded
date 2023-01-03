.syntax unified

.global arm_exception_handler
.thumb_func
.section .text.arm_exception_handler,"ax",%progbits
arm_exception_handler:
	cpsid if // Disable interrupts

	//R0: hardware context
	mov r0, SP

	//R1: software context
	push {R4-R11, LR}

	// Set handler arguments
	mov r1, SP
	bl exception_handler

	cpsie if // Enable interrupts
	pop {R4-R11, PC}
	.size arm_exception_handler, .-arm_exception_handler


.global SVC_Handler
.thumb_func
.section .text.SVC_Handler,"ax",%progbits
SVC_Handler:
	cpsid if // Disable interrupts

	ldr r0, =kernel
	bl _ZN4Rtos6Kernel13GetCurrentPSPEv

	ldmfd r0!, {r4-r11, lr}
	msr psp, r0
	
	cpsie i
	bx lr
	.size SVC_Handler, .-SVC_Handler


.global PendSV_Handler
.thumb_func
.section .text.PendSV_Handler,"ax",%progbits
PendSV_Handler:
	cpsid if

	mrs r1, psp
	stmfd r1!, {r4-r11, lr}

	ldr r0, =kernel
	bl _ZN4Rtos6Kernel14PendSV_HandlerEPv
	
	ldmfd r0!, {r4-r11, lr}
	msr psp, r0

	cpsie i
	bx lr
	.size PendSV_Handler, .-PendSV_Handler
