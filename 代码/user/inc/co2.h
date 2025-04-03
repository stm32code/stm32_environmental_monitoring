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
#define USART2_MAX_RECV_LEN		600					//�����ջ����ֽ���
#define USART2_MAX_SEND_LEN		600					//����ͻ����ֽ���
#define USART2_RX_EN 			1					//0,������;1,����.

extern u8  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 		//���ջ���,���USART3_MAX_RECV_LEN�ֽ�
extern u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 		//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
extern vu16 USART2_RX_STA;   						//��������״̬
extern float HCHO_PPM;
void usart2_init(u32 bound);				//����2��ʼ�� 
void u2_printf(char* fmt,...);
void CO2_Get(void);

#endif

