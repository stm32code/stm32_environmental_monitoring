#include "led.h"


/***********************
函数名：Buz_Init
函数功能：蜂鸣器初始化
形参：void
返回值：void
函数说明：
PB1 --- 通用推挽输出


************************/

void Buz_Init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//打开GPIOB时钟
	
	GPIO_InitTypeDef GPIO_InitStruct={0};//定义结构体变量名
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//配置为通用推挽输出模式
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;//配置第11号管脚
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//速度为50Mhz
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	

	
	//关闭蜂鸣器
	Buz_OFF;

}

/***********************
函数名：Voice_Loud
函数功能：报警模块
形参：void
返回值：void
函数说明：
温湿度、土壤湿度、二氧化碳浓度超过阈值，则蜂鸣器报警


************************/
//u8 Temp=45;
//u8 Hum=30;
//u8 Light=50;
//u8 CO2=50;
//u8 Soil=1;
void Voice_Loud(void)
{
//	u8 flag=0;
	static	u8 Temp=0;//放置温度
		static	u8 Hum=0;//放置湿度
	static	u8 Light=0;//放置光照强度
	static	u8 CO2=0;//放置二氧化碳浓度
	static	u8 Soil=0;//放置土壤湿度
	Act24_ContinueRead(&Temp,0,sizeof(Temp),6);//读取查重温度阈值
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
//			OLED_Clear(0x00);//清屏
//		}
//	if(temp>=Temp)
//	{
//		Oled_ShowAll(0,0,"Temperature anomaly");//显示中英字符串
//		Buz_ON;
//	}
//	else
//	{
//		Oled_ShowAll(0,0,"                   ");//显示中英字符串
//		Buz_OFF;
//	}
//	if(light_value<=Light)
//	{
//		Oled_ShowAll(2,0,"Light anomaly");//显示中英字符串
//		Buz_ON;
//	
//	}
//		if(light_value>Light)
//	{
//		Oled_ShowAll(2,0,"                   ");//显示中英字符串
//		Buz_OFF;
//	}
	
		
//	if(CO2_PPM>=CO2)
//	{
//		Oled_ShowAll(4,0,"CO2 anomaly");//显示中英字符串
//		Buz_ON;
//	}
//	else
//	{
//		Oled_ShowAll(4,0,"                   ");//显示中英字符串
//		Buz_OFF;
//	}
//	if(soil_value<=Soil)
//	{
//		Oled_ShowAll(6,0,"Soil anomaly");//显示中英字符串
//		Buz_ON;
//	}
//	else
//	{
//		Oled_ShowAll(6,0,"                   ");//显示中英字符串
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

