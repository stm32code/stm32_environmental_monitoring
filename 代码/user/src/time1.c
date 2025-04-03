#include "gizwits_product.h"
#include "time1.h"
/***********************
��������
�������ܣ���ʱ��1��ʼ��
�βΣ�
����ֵ��
����˵����


************************/


void Tim1_Init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);//��TIMʱ��
	
	//����TIM1ʱ����Ԫ
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct={0};
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInitStruct.TIM_Period = 1000;//��װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;//Ԥ��Ƶ��
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);

	TIM_ITConfig(TIM1,TIM_IT_Update, ENABLE);//ʹ�ܸ����ж�
	
	//TIM1������������
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=TIM1_UP_IRQn;//����TIM1�ж�Դ
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;//�ж�ʹ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;//�������ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;	//�����ȼ�
	NVIC_Init(&NVIC_InitStruct);//��ʼ������NVIC���ж��������ƼĴ�����
	
	TIM_Cmd(TIM1, ENABLE);//ʧ�ܶ�ʱ��


}
void TIM1_UP_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
		gizTimerMs();//Э�����Ҫ����ʱ��

	}
}
//void TIM3_Int_Init(u16 arr,u16 psc)
//{
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
//	
//	//��ʱ��TIM3��ʼ��
//	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
//	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
// 
//	//TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

//	//�ж����ȼ�NVIC����
//	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�3��
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
//	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


//	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
//}

////��ʱ��3�жϷ������
//void TIM3_IRQHandler(void)   //TIM3�ж�
//{
//	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
//	{
//		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
//		gizTimerMs();
//	}


//}


