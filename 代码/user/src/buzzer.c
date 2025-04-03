#include "led.h"


/***********************
��������Buz_Init
�������ܣ���������ʼ��
�βΣ�void
����ֵ��void
����˵����
PB1 --- ͨ���������


************************/

void Buz_Init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//��GPIOBʱ��
	
	GPIO_InitTypeDef GPIO_InitStruct={0};//����ṹ�������
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//����Ϊͨ���������ģʽ
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;//���õ�11�Źܽ�
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�Ϊ50Mhz
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	

	
	//�رշ�����
	Buz_OFF;

}

/***********************
��������Voice_Loud
�������ܣ�����ģ��
�βΣ�void
����ֵ��void
����˵����
��ʪ�ȡ�����ʪ�ȡ�������̼Ũ�ȳ�����ֵ�������������


************************/
//u8 Temp=45;
//u8 Hum=30;
//u8 Light=50;
//u8 CO2=50;
//u8 Soil=1;
void Voice_Loud(void)
{
//	u8 flag=0;
	static	u8 Temp=0;//�����¶�
		static	u8 Hum=0;//����ʪ��
	static	u8 Light=0;//���ù���ǿ��
	static	u8 CO2=0;//���ö�����̼Ũ��
	static	u8 Soil=0;//��������ʪ��
	Act24_ContinueRead(&Temp,0,sizeof(Temp),6);//��ȡ�����¶���ֵ
	Act24_ContinueRead(&Hum,2,sizeof(Hum),6);
	Act24_ContinueRead(&Light,4,sizeof(Light),6);
	Act24_ContinueRead(&CO2,6,sizeof(CO2),6);
	Act24_ContinueRead(&Soil,8,sizeof(Soil),6);
	if(temp>Temp|| light_value<Light|| CO2_PPM>CO2||soil_value<Soil )
	{
	
		if(temp>Temp|| CO2_PPM>CO2)
		{
			Fan_ON;
			Buz_ON;
			Hot_OFF;
		}
		if(temp<5)
		{
			Hot_ON;
		}
		if(light_value<Light)
		{
//			LED_ON;
				Hot_OFF;
				TIM_SetCompare3(TIM3,0);   
		}
	
		if(soil_value<Soil)
		{
			Water_ON;
			Buz_ON;
		}
	
//		if(flag==0)
//		{
//			flag=1;
//			OLED_Clear(0x00);//����
//		}
//	if(temp>=Temp)
//	{
//		Oled_ShowAll(0,0,"Temperature anomaly");//��ʾ��Ӣ�ַ���
//		Buz_ON;
//	}
//	else
//	{
//		Oled_ShowAll(0,0,"                   ");//��ʾ��Ӣ�ַ���
//		Buz_OFF;
//	}
//	if(light_value<=Light)
//	{
//		Oled_ShowAll(2,0,"Light anomaly");//��ʾ��Ӣ�ַ���
//		Buz_ON;
//	
//	}
//		if(light_value>Light)
//	{
//		Oled_ShowAll(2,0,"                   ");//��ʾ��Ӣ�ַ���
//		Buz_OFF;
//	}
	
		
//	if(CO2_PPM>=CO2)
//	{
//		Oled_ShowAll(4,0,"CO2 anomaly");//��ʾ��Ӣ�ַ���
//		Buz_ON;
//	}
//	else
//	{
//		Oled_ShowAll(4,0,"                   ");//��ʾ��Ӣ�ַ���
//		Buz_OFF;
//	}
//	if(soil_value<=Soil)
//	{
//		Oled_ShowAll(6,0,"Soil anomaly");//��ʾ��Ӣ�ַ���
//		Buz_ON;
//	}
//	else
//	{
//		Oled_ShowAll(6,0,"                   ");//��ʾ��Ӣ�ַ���
//		Buz_OFF;
//	}
//	if(key_scan()==1)
//	{
//		Buz_OFF;
//		
//	}

}
	else
	{
//		LED_OFF;
			TIM_SetCompare3(TIM3,1000);   
		Hot_OFF;
		Water_OFF;
		Fan_OFF;
		Buz_OFF;
	}
}

