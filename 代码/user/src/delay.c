#include "delay.h"

/***********************
��������delay_us
�������ܣ�΢����ʱ
�βΣ�u32 nus
����ֵ��void
����˵����
1us -- 72��__NOP();
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
��������delay_ms
�������ܣ�������ʱ
�βΣ�u32 nms
����ֵ��void
************************/
void delay_ms(u32 nms)
{
	while(nms--)
	{
		delay_us(1000);
	}
}







