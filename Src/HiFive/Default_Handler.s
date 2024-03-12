#if __riscv_xlen == 64
# define LREG ld
# define SREG sd
# define REGBYTES 8
#else
# define LREG lw
# define SREG sw
# define REGBYTES 4
#endif

.align 4
.global Default_Handler
Default_Handler:

	addi sp, sp, -32 * REGBYTES

	//PC at sp[0]
	sw x1, 1*REGBYTES(sp)
	sw x2, 2*REGBYTES(sp)
	sw x3, 3*REGBYTES(sp)
	sw x4, 4*REGBYTES(sp)
	sw x5, 5*REGBYTES(sp)
	sw x6, 6*REGBYTES(sp)
	sw x7, 7*REGBYTES(sp)
	sw x8, 8*REGBYTES(sp)
	sw x9, 9*REGBYTES(sp)
	sw x10, 10*REGBYTES(sp)  
	sw x11, 11*REGBYTES(sp)
	sw x12, 12*REGBYTES(sp)
	sw x13, 13*REGBYTES(sp)
	sw x14, 14*REGBYTES(sp)
	sw x15, 15*REGBYTES(sp)
	sw x16, 16*REGBYTES(sp)
	sw x17, 17*REGBYTES(sp)
	sw x18, 18*REGBYTES(sp)
	sw x19, 19*REGBYTES(sp)
	sw x20, 20*REGBYTES(sp)
	sw x21, 21*REGBYTES(sp)
	sw x22, 22*REGBYTES(sp)
	sw x23, 23*REGBYTES(sp)
	sw x24, 24*REGBYTES(sp)
	sw x25, 25*REGBYTES(sp)
	sw x26, 26*REGBYTES(sp)
	sw x27, 27*REGBYTES(sp)
	sw x28, 28*REGBYTES(sp)
	sw x29, 29*REGBYTES(sp)
	sw x30, 30*REGBYTES(sp)
	sw x31, 31*REGBYTES(sp)

	//Save PC
	csrr t0, mepc
	sw t0, 0*REGBYTES(sp)

	csrr a0, mcause
	mv a1, sp
	call HandleException
	add sp, a0, 0

	//Load desired PC for new thread
	lw a0, 0*REGBYTES(sp)
	csrw mepc, a0

	//PC at sp[0]
	lw x1, 1*REGBYTES(sp)
	//lw x2, 2*REGBYTES(sp)
	//lw x3, 3*REGBYTES(sp) GP
	//lw x4, 4*REGBYTES(sp) TP
	lw x5, 5*REGBYTES(sp)
	lw x6, 6*REGBYTES(sp)
	lw x7, 7*REGBYTES(sp)
	lw x8, 8*REGBYTES(sp)
	lw x9, 9*REGBYTES(sp)
	lw x10, 10*REGBYTES(sp)
	lw x11, 11*REGBYTES(sp)
	lw x12, 12*REGBYTES(sp)
	lw x13, 13*REGBYTES(sp)
	lw x14, 14*REGBYTES(sp)
	lw x15, 15*REGBYTES(sp)
	lw x16, 16*REGBYTES(sp)
	lw x17, 17*REGBYTES(sp)
	lw x18, 18*REGBYTES(sp)
	lw x19, 19*REGBYTES(sp)
	lw x20, 20*REGBYTES(sp)
	lw x21, 21*REGBYTES(sp)
	lw x22, 22*REGBYTES(sp)
	lw x23, 23*REGBYTES(sp)
	lw x24, 24*REGBYTES(sp)
	lw x25, 25*REGBYTES(sp)
	lw x26, 26*REGBYTES(sp)
	lw x27, 27*REGBYTES(sp)
	lw x28, 28*REGBYTES(sp)
	lw x29, 29*REGBYTES(sp)
	lw x30, 30*REGBYTES(sp)
	lw x31, 31*REGBYTES(sp)

	addi sp, sp, 32*REGBYTES

	//Return to new thread
	mret
