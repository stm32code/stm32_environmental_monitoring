#include "water.h"


/***********************
函数名：Fan_Init
函数功能：风扇初始化
形参：void
返回值：void
函数说明：
水泵 --- PB15 --- 通用推挽输出

软件设计：

************************/

void Fan_Init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//打开GPIOB时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);//打开TIM1时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	
	GPIO_InitTypeDef GPIO_InitStruct={0};//定义结构体变量名
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//配置推挽输出模式
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;//配置第15号管脚
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//速度为50Mhz
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
////	//配置TIM1时基单元
////	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct={0};
////	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
////	TIM_TimeBaseInitStruct.TIM_Period = 1000 - 1;//重装载值
////	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;//预分频数
////	//TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;    

////	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
////	//配置输出比较
////	TIM_OCInitTypeDef TIM_OCInitStruct={0};
////	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//配置PWM1模式
////	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//高电平有效
////	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//输出比较使能
////	TIM_OCInitStruct.TIM_Pulse = 0;//比较值初始值
////	TIM_OCInitStruct.TIM_OutputNState 	= TIM_OutputNState_Enable;//互补输出使能
////	TIM_OCInitStruct.TIM_OCNPolarity 	= TIM_OCNPolarity_High;//输出高电平互补
////	TIM_OCInitStruct.TIM_OCNIdleState 	= TIM_OCIdleState_Reset;//指定下的引脚状态
////	TIM_OCInitStruct.TIM_OCIdleState 	= TIM_OCIdleState_Reset;  //指定下的引脚状态   

////	
////	TIM_OC3Init(TIM1,&TIM_OCInitStruct);

////	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);//使能通道3影子寄存器
////	
////	TIM_Cmd(TIM1,ENABLE);//使能TIM1
////	TIM_CtrlPWMOutputs(TIM1, ENABLE);//使能PWM互补输出使能
////	TIM_CCPreloadControl(TIM1,ENABLE);
////	TIM_SetCompare3(TIM1,1000);

	//TIM_Cmd(TIM1,ENABLE);//使能TIM1

	//风扇默认熄灭 --- 低电平
	Fan_OFF;

}
//void Fan_Open(u16 speed)
//{
//	
//		TIM_SetCompare3(TIM1,speed);

//}
