

void delay(volatile int d)
{
	while(d--);
}


int main(void)
{
	volatile unsigned int *pGPFCON = (volatile unsigned int *)0x56000050;
	volatile unsigned int *pGPFDAT = (volatile unsigned int *)0x56000054;
	int val = 0;	/* val: 0b001->0b010->0b100 */
	int tmp = 1;
	/* 设置GPFCON让GPF4/5/6配置为输出引脚，既01 */
	*pGPFCON &= ~((3<<8) | (3<<10) | (3<<12));
	*pGPFCON |=  ((1<<8) | (1<<10) | (1<<12));


	*pGPFDAT &= ~(7<<4);
	*pGPFDAT |=  (7<<4);
	delay(90000);

	/* 循环点亮 */
	while(1)
	{
		*pGPFDAT &= ~(7<<4);
		*pGPFDAT |= ~(tmp<<4);
		delay(50000);
		tmp=(tmp<<1);
		if(tmp == 8)
			tmp =1;
	}

	return 0;
}






















