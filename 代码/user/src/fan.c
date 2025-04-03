#include "water.h"


/***********************
��������Fan_Init
�������ܣ����ȳ�ʼ��
�βΣ�void
����ֵ��void
����˵����
ˮ�� --- PB15 --- ͨ���������

�����ƣ�

************************/

void Fan_Init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//��GPIOBʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);//��TIM1ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	
	GPIO_InitTypeDef GPIO_InitStruct={0};//����ṹ�������
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//�����������ģʽ
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;//���õ�15�Źܽ�
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�Ϊ50Mhz
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
////	//����TIM1ʱ����Ԫ
////	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct={0};
////	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
////	TIM_TimeBaseInitStruct.TIM_Period = 1000 - 1;//��װ��ֵ
////	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;//Ԥ��Ƶ��
////	//TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;    

////	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
////	//��������Ƚ�
////	TIM_OCInitTypeDef TIM_OCInitStruct={0};
////	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//����PWM1ģʽ
////	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//�ߵ�ƽ��Ч
////	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//����Ƚ�ʹ��
////	TIM_OCInitStruct.TIM_Pulse = 0;//�Ƚ�ֵ��ʼֵ
////	TIM_OCInitStruct.TIM_OutputNState 	= TIM_OutputNState_Enable;//�������ʹ��
////	TIM_OCInitStruct.TIM_OCNPolarity 	= TIM_OCNPolarity_High;//����ߵ�ƽ����
////	TIM_OCInitStruct.TIM_OCNIdleState 	= TIM_OCIdleState_Reset;//ָ���µ�����״̬
////	TIM_OCInitStruct.TIM_OCIdleState 	= TIM_OCIdleState_Reset;  //ָ���µ�����״̬   

////	
////	TIM_OC3Init(TIM1,&TIM_OCInitStruct);

////	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);//ʹ��ͨ��3Ӱ�ӼĴ���
////	
////	TIM_Cmd(TIM1,ENABLE);//ʹ��TIM1
////	TIM_CtrlPWMOutputs(TIM1, ENABLE);//ʹ��PWM�������ʹ��
////	TIM_CCPreloadControl(TIM1,ENABLE);
////	TIM_SetCompare3(TIM1,1000);

	//TIM_Cmd(TIM1,ENABLE);//ʹ��TIM1

	//����Ĭ��Ϩ�� --- �͵�ƽ
	Fan_OFF;

}
//void Fan_Open(u16 speed)
//{
//	
//		TIM_SetCompare3(TIM1,speed);

//}
