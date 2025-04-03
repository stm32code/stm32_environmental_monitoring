#ifndef _CO2_H
#define _CO2_H


#include "includes.h"

//typedef struct 
//{
//	u8 data[512];
//	u16 leng;
//	u8 flag;

//}Re_data;

void usart2_init(u32 bound);

extern float TVOC_PPM;
extern float HCHO_PPM;
extern u16   CO2_PPM;
extern u8  buf5[200];
#define USART2_MAX_RECV_LEN		600					//最大接收缓存字节数
#define USART2_MAX_SEND_LEN		600					//最大发送缓存字节数
#define USART2_RX_EN 			1					//0,不接收;1,接收.

extern u8  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 		//接收缓冲,最大USART3_MAX_RECV_LEN字节
extern u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 		//发送缓冲,最大USART3_MAX_SEND_LEN字节
extern vu16 USART2_RX_STA;   						//接收数据状态
extern float HCHO_PPM;
void usart2_init(u32 bound);				//串口2初始化 
void u2_printf(char* fmt,...);
void CO2_Get(void);

#endif

