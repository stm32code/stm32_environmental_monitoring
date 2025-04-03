#ifndef _DHT11_H
#define _DHT11_H

#include "includes.h"
extern float temp,humi;
extern u8 DHT11;
extern u8 buf1[20];
extern u8 buf2[20];
#define DHT11_IO    GPIOB
#define DHT11_PIN   GPIO_Pin_14
//IO方向设置
#define DHT11_IO_IN()  {DHT11_IO->CRH&=0XF0FFFFFF;DHT11_IO->CRH|=8<<24;}
#define DHT11_IO_OUT() {DHT11_IO->CRH&=0XF0FFFFFF;DHT11_IO->CRH|=3<<24;}
////IO操作函数											   
#define	DHT11_DQ_OUT PBout(14) //数据端口	PA0 
#define	DHT11_DQ_IN  PBin(14)  //数据端口	PA0 


u8 DHT11_Init(void);//初始化DHT11
u8 DHT11_Read_Data(float *temp,float *humi);//读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11 
void Dht11_GetValue(void);
//void Dht11_GetValue2(void);


#endif


