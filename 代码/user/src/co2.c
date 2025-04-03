#include "co2.h"
#include "math.h"
#include "stdarg.h"	 	 

/***********************
��������CO2_Init
�������ܣ�co2���ģ���ʼ��
�βΣ�void
����ֵ��void
����˵����
co2--- PA3 

�����ƣ�

************************/
//void usart2_init(u32 bound)
//{  

//	NVIC_InitTypeDef NVIC_InitStructure;
//	GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// GPIOBʱ��
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); //����3ʱ��ʹ��

// 	USART_DeInit(USART2);  //��λ����3
//		 //USART3_TX   PB10
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PB10
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
//    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PB10
//   
//    //USART3_RX	  PB11
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
//    GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PB11
//	
//	USART_InitStructure.USART_BaudRate = bound;//������һ������Ϊ9600;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
//	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
//  
//	USART_Init(USART2, &USART_InitStructure); //��ʼ������	3
//  
//	USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 
//	
//	//ʹ�ܽ����ж�
//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�   
//	
//	//�����ж����ȼ�
//	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
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
//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//���յ�����
//	{	 
//		USART_ClearITPendingBit(USART2,USART_IT_RXNE);//����жϱ�־λ
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
//			Oled_ShowAll(6,0,(u8*)buf5);//��ʾ��Ӣ�ַ���
//			rec.leng = 0;
//		}
////		data[count++] = res;
//	}  				 											 
//}


//���ڽ��ջ����� 	
u8  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 				//���ջ���,���USART3_MAX_RECV_LEN���ֽ�.
u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 			//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�

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
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//���յ�����
	{	 
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);//����жϱ�־λ
		res =USART_ReceiveData(USART2);		
		USART_SendData(USART2, res);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET) {}	
		if(res == 0x2C) {
			count = 0;
			CO2_PPM  = (data[1]*256+data[2]);
				CO2_PPM = ((100 * CO2_PPM)/2000);//������̼ǿ�Ȱٷֱ�

			
		}
		data[count++] = res;
		
	}  				 											 
} 

//��ʼ��IO ����3
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������	  
void usart2_init(u32 bound)
{  

	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); //����3ʱ��ʹ��

 	USART_DeInit(USART2);  //��λ����3
		 //USART3_TX   PB10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PB10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PB10
   
    //USART3_RX	  PB11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PB11
	
	USART_InitStructure.USART_BaudRate = bound;//������һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  
	USART_Init(USART2, &USART_InitStructure); //��ʼ������	3
  
	USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 
	
	//ʹ�ܽ����ж�
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�   
	
	//�����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
}



//����3,printf ����
//ȷ��һ�η������ݲ�����USART3_MAX_SEND_LEN�ֽ�
void u2_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART2_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART2_TX_BUF);		//�˴η������ݵĳ���
	for(j=0;j<i;j++)							//ѭ����������
	{
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
		USART_SendData(USART2,USART2_TX_BUF[j]); 
	} 
}

void CO2_Get(void)
{
			sprintf((char*)buf5,"CO2:%d%%",CO2_PPM);
			Oled_ShowAll(4,0,(u8*)buf5);//��ʾ��Ӣ�ַ���
			//if()
			Oled_clear(4,56,16,8);//���ĳ�ַ�
			memset(buf5,0,sizeof(buf5));
}
