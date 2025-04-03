#include "gizwits_product.h"
#include "gizwits_protocol.h"
#include "main.h"
extern dataPoint_t currentDataPoint;
 void Gizwits_Init(void)
{
	Tim1_Init();//TIM1��ʼ��
	Usart3_Init(9600);//USART3+��ʼ��
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
	gizwitsInit();
}
int main(void)
{

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�ж����ѡ��
	Usart1_Init(115200);//����1��ʼ��
	Led_Init();//LED�����ʼ��
  Key_Init();//������ʼ��
	OLED_Init();//OLED��ʼ��
	DHT11_Init();//DHT11��ʼ��
	ADC1_Init();//ģ��ת����ʼ��������������ǿ��ת��
	Buz_Init();//��������ʼ��
	Water_Init();//ˮ�ó�ʼ��
	Fan_Init();//���ȳ�ʼ��
	Hot_Init();//��������ʼ��
	Act24_Init();//���ݴ洢����ʼ��
	usart2_init(9600);
	Gizwits_Init();//�����Ƴ�ʼ��

	printf("��ʼ���ɹ�\r\n");
//	Pass_lock();
//	u8 rec0[5];
//	static	u8 temp=0;//���ô洢���е�����
//	Act24_ContinueRead(&temp,21,sizeof(temp),6);//��������������
//	sprintf((char *)rec0,"%d��",temp);
//	Oled_ShowAll(0,80,rec0);//��ʾ��Ӣ�ַ���
//	Oled_ShowAll(2,80,"123");//��ʾ��Ӣ�ַ���
//	Hot_ON;
while(1)
{

	
	
//	key = key_scan();
//		if(key == 1)//��������ģʽ
//		{
//			printf("sss\r\n");
//			gizwitsSetMode(WIFI_AIRLINK_MODE);//�ֻ��㲥����
//			printf("WIFI_AIRLINK_MODE OK\r\n");
//		}
//		if(key == 2)//�ָ���������
//		{
//			printf("aaa\r\n");
//			gizwitsSetMode(WIFI_RESET_MODE);//�ָ���������
//			printf("WIFI_RESET_MODE OK\r\n");
//		}
//		
//	gizwitsHandle(&currentDataPoint);//�ϱ�����
//	userHandle();//�����ϴ�

Smart_Greenhouse();


}







}

