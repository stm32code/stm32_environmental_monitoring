#include "gizwits_product.h"
#include "time1.h"
/***********************
函数名：
函数功能：定时器1初始化
形参：
返回值：
函数说明：


************************/


void Tim1_Init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);//打开TIM时钟
	
	//配置TIM1时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct={0};
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStruct.TIM_Period = 1000;//重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;//预分频数
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);

	TIM_ITConfig(TIM1,TIM_IT_Update, ENABLE);//使能更新中断
	
	//TIM1中优先限配置
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=TIM1_UP_IRQn;//配置TIM1中断源
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;//中断使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;//抢断优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;	//子优先级
	NVIC_Init(&NVIC_InitStruct);//初始化配置NVIC（中断向量控制寄存器）
	
	TIM_Cmd(TIM1, ENABLE);//失能定时器


}
void TIM1_UP_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
		gizTimerMs();//协议层需要缓冲时间

	}
}
//void TIM3_Int_Init(u16 arr,u16 psc)
//{
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
//	
//	//定时器TIM3初始化
//	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
//	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
// 
//	//TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

//	//中断优先级NVIC设置
//	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //从优先级3级
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
//	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


//	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
//}

////定时器3中断服务程序
//void TIM3_IRQHandler(void)   //TIM3中断
//{
//	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
//	{
//		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
//		gizTimerMs();
//	}


//}


