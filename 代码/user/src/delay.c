#include "delay.h"

/***********************
函数名：delay_us
函数功能：微秒延时
形参：u32 nus
返回值：void
函数说明：
1us -- 72个__NOP();
************************/

void delay_us(u32 nus)
{
	while(nus--)
	{
		
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	}
}



/***********************
函数名：delay_ms
函数功能：毫秒延时
形参：u32 nms
返回值：void
************************/
void delay_ms(u32 nms)
{
	while(nms--)
	{
		delay_us(1000);
	}
}







