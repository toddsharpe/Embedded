.syntax unified

.global SVC_Handler
.thumb_func
.section .text.SVC_Handler,"ax",%progbits
SVC_Handler:
	cpsid if // Disable interrupts

	bl GetCurrentStack

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

	mrs r0, psp
	stmfd r0!, {r4-r11, lr}

	bl ThreadSwap
	
	ldmfd r0!, {r4-r11, lr}
	msr psp, r0

	cpsie i
	bx lr
	.size PendSV_Handler, .-PendSV_Handler
