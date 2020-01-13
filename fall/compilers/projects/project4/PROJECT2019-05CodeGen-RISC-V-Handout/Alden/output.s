 #pre main code
.text 
.section .rodata 
.align 3 

	.text
	.align 1
	.globl foo
	.type foo, @function
foo:
	addi sp, sp, -1024
	sd ra, 8(sp)
	sd s0, 16(sp)
	sd s1, 24(sp)
	addi s0, sp, 40
	addi s1,sp,0
