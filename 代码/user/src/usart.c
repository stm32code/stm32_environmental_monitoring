#include "usart.h"

//usart1-Tx--PA9       usart1-Rx-----PA10

void Usart1_Init(u32 bp)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	//��GPIO���ں�usart����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	
//����usart����tx����
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;//��������
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

//����usart����rx����
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;//����
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
//���ô��ڵĹ�������
	USART_InitStruct.USART_BaudRate=bp;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_Parity=USART_Parity_No;//����λ
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//Ӳ��������
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
  USART_Init(USART1,&USART_InitStruct);
	
	//����������������
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;//����usart�ж�Դ
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;//�ж�ʹ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=3;//�������ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;	//�����ȼ�
	NVIC_Init(&NVIC_InitStruct);//��ʼ������NVIC���ж��������ƼĴ�����
	//�ж����ú�����ʹ�ܴ����ж�
	USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);//ʹ�ܽ����ж�
	USART_ITConfig(USART1,USART_IT_IDLE, ENABLE);//ʹ�ܿ����ж�

	//ʹ�ܴ���
	USART_Cmd(USART1,ENABLE);
	USART_ClearFlag(USART1,USART_FLAG_TC);//���USARTx�Ĵ������־λ

}

re_data Rece_data;
//�����ж�
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE))//�����жϱ�־λ
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);//����жϱ�־λ
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
//����1����һ�ֽ�
void Send_Byte(uint16_t data)
{
	USART_SendData(USART1,data);
	while(!USART_GetFlagStatus(USART1,USART_FLAG_TXE));//�ȴ������������
	
}

//����1����һ����

u16 Rece_Byte(void)
{
	while(!USART_GetFlagStatus(USART1,USART_FLAG_RXNE))//�ȴ������������
	{
	}
	return USART_ReceiveData(USART1);
}

//���Ժ���
void Data_Echo(void)
{
	uint16_t date=0;
	date=Rece_Byte();
	Send_Byte(date);
}

//�������ܣ�printf�ض���
int fputc(int c, FILE * stream)
{
	Send_Byte(c);
	return c;
}

