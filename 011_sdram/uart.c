
#include "s3c2440_soc.h"


/* 15200,8n1 */
void uart0_init()
{
	/* 设置引脚用于串口 
	 * GPH2,3用于TxD0,RxD0 
	 */
	GPHCON &= ~((3<<4) | (3<<6));
	GPHCON |=  ((2<<4) | (2<<6));

	GPHUP &= ~((1<<2) | (1<<3)); /* 使能内部上拉使得引脚为高电平 */
	
	/* 设置波特率
	 * UBRDIV0 = (int)( UART clock / ( buad rate x 16) ) –1
	 * UART clock = PCLK = 50MHz
	 * UBRDIV0 = (int)( 50000000 / ( 115200 x 16) ) –1 = 26
	 */
	UCON0 = 0x00000005;	/* PCLK,中断/查询模式 
		 				 * UCON0[11:10] = 00(0x00000005),10(0x00000805) :选为PCLK
						 * UOCN0[3:2] = 01,Interrupt request or polling mode
						 * UOCN0[1:0] = 01,Interrupt request or polling mode
						 */
	UBRDIV0 = 26;

	/* 设置数据格式 */
	ULCON0 = 0x00000003;/* 8n1: 8个数据位，无校验位，一个停止位 
						 * ULCON0[5:4:3] = 0xx :No parity(无校验位)
						 * ULCON0[2] = 0 :One stop bit per frame(一个停止位)
						 * ULCON0[1:0] = 11 :8-bits(8个数据位)
						 */	
}

int putchar(int c)
{
	/* UTRSTAT0 */
	/* UTXH0 */

	while (!(UTRSTAT0 & (1<<2)));
	UTXH0 = (unsigned char)c;
}

int getchar(void)
{

	/* read UTXH0 */	
	while (!(UTRSTAT0 & (1<<0)));
	return 	URXH0;
}

int puts(const char *s)
{
	while(*s)
	{
		putchar(*s);
		s++;
	}

}
















