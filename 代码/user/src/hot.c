#include "hot.h"


/***********************
��������Water_Init
�������ܣ����ȳ�ʼ��
�βΣ�void
����ֵ��void
����˵����
���� --- PA7 --- ͨ���������

�����ƣ�

************************/

void Hot_Init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//��GPIOBʱ��
	
	GPIO_InitTypeDef GPIO_InitStruct={0};//����ṹ�������
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//����Ϊͨ���������ģʽ
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;//���õ�11�Źܽ�
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�Ϊ50Mhz
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	//������Ĭ��Ϩ�� --- �͵�ƽ
	Hot_OFF;

	
}

