
#include "s3c2440_soc.h"
#include "uart.h"
#include "init.h"

int main(void) 
{
	int i=1;
	uart0_init();
	//sdram_init();
	i = sdram_test();
	
	if(i==0)
	{
		puts("yes\n\r");
		led_test();
	}
	else
	{
		puts("no\n\r");
	}
	
	return 0;
}


