#include "hot.h"


/***********************
函数名：Water_Init
函数功能：加热初始化
形参：void
返回值：void
函数说明：
加热 --- PA7 --- 通用推挽输出

软件设计：

************************/

void Hot_Init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//打开GPIOB时钟
	
	GPIO_InitTypeDef GPIO_InitStruct={0};//定义结构体变量名
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//配置为通用推挽输出模式
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;//配置第11号管脚
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//速度为50Mhz
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	//加热器默认熄灭 --- 低电平
	Hot_OFF;

	
}

