#include "key.h"

/***********************
��������Key_Init
�������ܣ�������ʼ��
�βΣ�void
����ֵ��void
����˵����
KEY1  -PAO  KEY2--PB5  KEY3--PB8  KEY4  --PB6  ����Ϊ�͵�ƽ
KEY1 --- PA0 --- ��������ģʽ
KEY2 --- PB5 --- ��������ģʽ
KEY3 --- PB8 --- ��������ģʽ
KEY4 --- PB9 --- ��������ģʽ
�����ƣ�
1��	��ʱ��
2��	��ʼ��IO
3��	����ɨ��
************************/

void Key_Init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//��GPIOBʱ��
	
	GPIO_InitTypeDef GPIO_InitStruct={0};//����ṹ�������
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//����Ϊ��������ģʽ
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;//���ùܽ�
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//����Ϊ��������ģʽ
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9 ;//���ùܽ�
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}

/***********************
��������key_scan
�������ܣ�����ɨ��
�βΣ�void
����ֵ��u8  ���ؼ�ֵ
����˵����
************************/

u8 key_scan(void)
{
	static u8 key_flag = 0;
	
	if(((!KEY1) || (!KEY2) || (!KEY3)||( !KEY4)) && key_flag == 0)//�жϰ����Ƿ���
	{
		//�����������
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
	else if((KEY1 && KEY2 && KEY3 && KEY4) && key_flag == 1)//�жϰ����Ƿ�����
	{
		key_flag = 0;
	}
	return 0;
}

