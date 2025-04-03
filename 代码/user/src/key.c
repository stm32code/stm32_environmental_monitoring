#include "key.h"

/***********************
函数名：Key_Init
函数功能：按键初始化
形参：void
返回值：void
函数说明：
KEY1  -PAO  KEY2--PB5  KEY3--PB8  KEY4  --PB6  按下为低电平
KEY1 --- PA0 --- 浮空输入模式
KEY2 --- PB5 --- 浮空输入模式
KEY3 --- PB8 --- 浮空输入模式
KEY4 --- PB9 --- 浮空输入模式
软件设计：
1、	打开时钟
2、	初始化IO
3、	按键扫描
************************/

void Key_Init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//打开GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//打开GPIOB时钟
	
	GPIO_InitTypeDef GPIO_InitStruct={0};//定义结构体变量名
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//配置为浮空输入模式
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;//配置管脚
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//配置为浮空输入模式
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9 ;//配置管脚
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}

/***********************
函数名：key_scan
函数功能：按键扫描
形参：void
返回值：u8  返回键值
函数说明：
************************/

u8 key_scan(void)
{
	static u8 key_flag = 0;
	
	if(((!KEY1) || (!KEY2) || (!KEY3)||( !KEY4)) && key_flag == 0)//判断按键是否按下
	{
		//按键软件消抖
		delay_ms(30);
		if(!KEY1)
		{
			key_flag = 1;
			return 1;
		}
		if(!KEY2)
		{
			key_flag = 1;
			return 2;
		}
		if(!KEY3)
		{
			key_flag = 1;
			return 3;
		}
		if(!KEY4)
		{
			key_flag = 1;
			return 4;
		}
	}
	else if((KEY1 && KEY2 && KEY3 && KEY4) && key_flag == 1)//判断按键是否松手
	{
		key_flag = 0;
	}
	return 0;
}

