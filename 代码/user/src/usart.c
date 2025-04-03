#include "usart.h"

//usart1-Tx--PA9       usart1-Rx-----PA10

void Usart1_Init(u32 bp)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	//打开GPIO串口和usart串口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	
//配置usart串口tx发送
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

//配置usart串口rx接收
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;//浮空
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
//配置串口的工作参数
	USART_InitStruct.USART_BaudRate=bp;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_Parity=USART_Parity_No;//检验位
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//硬件流控制
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
  USART_Init(USART1,&USART_InitStruct);
	
	//串口中优先限配置
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;//配置usart中断源
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;//中断使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=3;//抢断优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;	//子优先级
	NVIC_Init(&NVIC_InitStruct);//初始化配置NVIC（中断向量控制寄存器）
	//中断配置函数，使能串口中断
	USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);//使能接收中断
	USART_ITConfig(USART1,USART_IT_IDLE, ENABLE);//使能空闲中断

	//使能串口
	USART_Cmd(USART1,ENABLE);
	USART_ClearFlag(USART1,USART_FLAG_TC);//清除USARTx的待处理标志位

}

re_data Rece_data;
//串口中断
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE))//接收中断标志位
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);//清除中断标志位
		Rece_data.data[Rece_data.leng++]=USART_ReceiveData(USART1);
	}
	if(USART_GetITStatus(USART1,USART_IT_IDLE))
	{
		USART1->SR;
		USART1->DR;
		
		Rece_data.data[Rece_data.leng]='\0';
		Rece_data.flag=1;
		Rece_data.leng=0;
		printf("data:%s\r\n",Rece_data.data);
	}

}
//串口1发送一字节
void Send_Byte(uint16_t data)
{
	USART_SendData(USART1,data);
	while(!USART_GetFlagStatus(USART1,USART_FLAG_TXE));//等待发送数据完毕
	
}

//串口1接收一节字

u16 Rece_Byte(void)
{
	while(!USART_GetFlagStatus(USART1,USART_FLAG_RXNE))//等待接收数据完毕
	{
	}
	return USART_ReceiveData(USART1);
}

//回显函数
void Data_Echo(void)
{
	uint16_t date=0;
	date=Rece_Byte();
	Send_Byte(date);
}

//函数功能：printf重定向
int fputc(int c, FILE * stream)
{
	Send_Byte(c);
	return c;
}

