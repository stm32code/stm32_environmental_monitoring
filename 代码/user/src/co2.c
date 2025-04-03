#include "co2.h"
#include "math.h"
#include "stdarg.h"	 	 

/***********************
函数名：CO2_Init
函数功能：co2检测模块初始化
形参：void
返回值：void
函数说明：
co2--- PA3 

软件设计：

************************/
//void usart2_init(u32 bound)
//{  

//	NVIC_InitTypeDef NVIC_InitStructure;
//	GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// GPIOB时钟
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); //串口3时钟使能

// 	USART_DeInit(USART2);  //复位串口3
//		 //USART3_TX   PB10
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PB10
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
//    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PB10
//   
//    //USART3_RX	  PB11
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
//    GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PB11
//	
//	USART_InitStructure.USART_BaudRate = bound;//波特率一般设置为9600;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
//	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
//  
//	USART_Init(USART2, &USART_InitStructure); //初始化串口	3
//  
//	USART_Cmd(USART2, ENABLE);                    //使能串口 
//	
//	//使能接收中断
//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断   
//	
//	//设置中断优先级
//	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
//}
//u16 data[9];
//u8  count = 0;
//u8  data_flag = 0;
//u16  buf5[20];
//float TVOC_PPM;
//float HCHO_PPM;
//u16   CO2_PPM;
//Re_data rec;
//void USART2_IRQHandler(void)
//{
//	u8 res;	      
//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//接收到数据
//	{	 
//		USART_ClearITPendingBit(USART2,USART_IT_RXNE);//清除中断标志位
//		rec.data[rec.leng++	] =USART_ReceiveData(USART2);		
////		USART_SendData(USART2, rec.data[rec.leng-1]);
////		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET) {}	
//		if(rec.data[rec.leng-1] == 0x03) {
//			CO2_PPM  = (rec.data[rec.leng-3]*256+rec.data[rec.leng-2]);
//			if(CO2_PPM>=2000)
//			{
//				CO2_PPM=2000;
//			}
//			res=(100 *CO2_PPM)/2000;
//			sprintf((char*)buf5,"CO2:%d%%",res);
//			Oled_ShowAll(6,0,(u8*)buf5);//显示中英字符串
//			rec.leng = 0;
//		}
////		data[count++] = res;
//	}  				 											 
//}


//串口接收缓存区 	
u8  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 				//接收缓冲,最大USART3_MAX_RECV_LEN个字节.
u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 			//发送缓冲,最大USART3_MAX_SEND_LEN字节

u16 data[9];
u8  count = 0;
u8  data_flag = 0;
u8  buf5[200];
float TVOC_PPM;
float HCHO_PPM;
u16   CO2_PPM;

 void USART2_IRQHandler(void)
{
	u8 res;	      
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//接收到数据
	{	 
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);//清除中断标志位
		res =USART_ReceiveData(USART2);		
		USART_SendData(USART2, res);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET) {}	
		if(res == 0x2C) {
			count = 0;
			CO2_PPM  = (data[1]*256+data[2]);
				CO2_PPM = ((100 * CO2_PPM)/2000);//二氧化碳强度百分比

			
		}
		data[count++] = res;
		
	}  				 											 
} 

//初始化IO 串口3
//pclk1:PCLK1时钟频率(Mhz)
//bound:波特率	  
void usart2_init(u32 bound)
{  

	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); //串口3时钟使能

 	USART_DeInit(USART2);  //复位串口3
		 //USART3_TX   PB10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PB10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PB10
   
    //USART3_RX	  PB11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PB11
	
	USART_InitStructure.USART_BaudRate = bound;//波特率一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  
	USART_Init(USART2, &USART_InitStructure); //初始化串口	3
  
	USART_Cmd(USART2, ENABLE);                    //使能串口 
	
	//使能接收中断
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断   
	
	//设置中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
}



//串口3,printf 函数
//确保一次发送数据不超过USART3_MAX_SEND_LEN字节
void u2_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART2_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART2_TX_BUF);		//此次发送数据的长度
	for(j=0;j<i;j++)							//循环发送数据
	{
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
		USART_SendData(USART2,USART2_TX_BUF[j]); 
	} 
}

void CO2_Get(void)
{
			sprintf((char*)buf5,"CO2:%d%%",CO2_PPM);
			Oled_ShowAll(4,0,(u8*)buf5);//显示中英字符串
			//if()
			Oled_clear(4,56,16,8);//清空某字符
			memset(buf5,0,sizeof(buf5));
}
