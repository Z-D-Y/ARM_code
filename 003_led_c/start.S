
 .text
 .global _start
 
 _start:

	/* 设置内存: sp 栈 */
	ldr sp, =4096;	/* nand启动 0地址开始的4K空间为片内内存，
									 * 把栈设置在4K内存的顶部
									 */
	//ldr sp, =0x40000000 + 4096;	/* n0r启动 */
	
	/* 调用main */
	bl main

halt:
	b halt












	
