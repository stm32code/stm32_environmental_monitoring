#ifndef _DHT11_H
#define _DHT11_H

#include "includes.h"
extern float temp,humi;
extern u8 DHT11;
extern u8 buf1[20];
extern u8 buf2[20];
#define DHT11_IO    GPIOB
#define DHT11_PIN   GPIO_Pin_14
//IO��������
#define DHT11_IO_IN()  {DHT11_IO->CRH&=0XF0FFFFFF;DHT11_IO->CRH|=8<<24;}
#define DHT11_IO_OUT() {DHT11_IO->CRH&=0XF0FFFFFF;DHT11_IO->CRH|=3<<24;}
////IO��������											   
#define	DHT11_DQ_OUT PBout(14) //���ݶ˿�	PA0 
#define	DHT11_DQ_IN  PBin(14)  //���ݶ˿�	PA0 


u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(float *temp,float *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11 
void Dht11_GetValue(void);
//void Dht11_GetValue2(void);


#endif


