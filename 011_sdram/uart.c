
#include "s3c2440_soc.h"


/* 15200,8n1 */
void uart0_init()
{
	/* �����������ڴ��� 
	 * GPH2,3����TxD0,RxD0 
	 */
	GPHCON &= ~((3<<4) | (3<<6));
	GPHCON |=  ((2<<4) | (2<<6));

	GPHUP &= ~((1<<2) | (1<<3)); /* ʹ���ڲ�����ʹ������Ϊ�ߵ�ƽ */
	
	/* ���ò�����
	 * UBRDIV0 = (int)( UART clock / ( buad rate x 16) ) �C1
	 * UART clock = PCLK = 50MHz
	 * UBRDIV0 = (int)( 50000000 / ( 115200 x 16) ) �C1 = 26
	 */
	UCON0 = 0x00000005;	/* PCLK,�ж�/��ѯģʽ 
		 				 * UCON0[11:10] = 00(0x00000005),10(0x00000805) :ѡΪPCLK
						 * UOCN0[3:2] = 01,Interrupt request or polling mode
						 * UOCN0[1:0] = 01,Interrupt request or polling mode
						 */
	UBRDIV0 = 26;

	/* �������ݸ�ʽ */
	ULCON0 = 0x00000003;/* 8n1: 8������λ����У��λ��һ��ֹͣλ 
						 * ULCON0[5:4:3] = 0xx :No parity(��У��λ)
						 * ULCON0[2] = 0 :One stop bit per frame(һ��ֹͣλ)
						 * ULCON0[1:0] = 11 :8-bits(8������λ)
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
















