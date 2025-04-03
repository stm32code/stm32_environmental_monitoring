#include "gizwits_product.h"
#include "gizwits_protocol.h"
#include "main.h"
extern dataPoint_t currentDataPoint;
 void Gizwits_Init(void)
{
	Tim1_Init();//TIM1初始化
	Usart3_Init(9600);//USART3+初始化
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
	gizwitsInit();
}
int main(void)
{

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断组的选择
	Usart1_Init(115200);//串口1初始化
	Led_Init();//LED补光初始化
  Key_Init();//按键初始化
	OLED_Init();//OLED初始化
	DHT11_Init();//DHT11初始化
	ADC1_Init();//模数转换初始化。土壤、光照强度转换
	Buz_Init();//蜂鸣器初始化
	Water_Init();//水泵初始化
	Fan_Init();//风扇初始化
	Hot_Init();//加热器初始化
	Act24_Init();//数据存储器初始化
	usart2_init(9600);
	Gizwits_Init();//机智云初始化

	printf("初始化成功\r\n");
//	Pass_lock();
//	u8 rec0[5];
//	static	u8 temp=0;//放置存储器中的密码
//	Act24_ContinueRead(&temp,21,sizeof(temp),6);//读密码区间数据
//	sprintf((char *)rec0,"%d℃",temp);
//	Oled_ShowAll(0,80,rec0);//显示中英字符串
//	Oled_ShowAll(2,80,"123");//显示中英字符串
//	Hot_ON;
while(1)
{

	
	
//	key = key_scan();
//		if(key == 1)//设置配网模式
//		{
//			printf("sss\r\n");
//			gizwitsSetMode(WIFI_AIRLINK_MODE);//手机广播配网
//			printf("WIFI_AIRLINK_MODE OK\r\n");
//		}
//		if(key == 2)//恢复出厂设置
//		{
//			printf("aaa\r\n");
//			gizwitsSetMode(WIFI_RESET_MODE);//恢复出厂设置
//			printf("WIFI_RESET_MODE OK\r\n");
//		}
//		
//	gizwitsHandle(&currentDataPoint);//上报函数
//	userHandle();//数据上传

Smart_Greenhouse();


}







}

