#ifndef __OLED_H
#define __OLED_H


#include "includes.h"


/*--------------------���Ŷ���--------------------------*/
#define 		OLED_SCLK_Set()			GPIO_SetBits(GPIOB,GPIO_Pin_12)	          //  PA6��SCL�������
#define			OLED_SCLK_Clr()			GPIO_ResetBits(GPIOB,GPIO_Pin_12)	        //  PA6��SCL�������

#define			OLED_SDIN_Set()			GPIO_SetBits(GPIOB,GPIO_Pin_13)	          //  PA5��SDA�������
#define			OLED_SDIN_Clr()			GPIO_ResetBits(GPIOB,GPIO_Pin_13)	        //  PA5��SDA�������
#define 		OLED_READ_SDIN()		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13)	//  ��ȡPA5��SDA����ƽ
		

/*definition--------------------------------------------*/


			  				   
#define	IIC_ACK		0		//Ӧ��
#define	IIC_NO_ACK	1		//��Ӧ��




/*-----------------��������-----------------------------*/
void OLED_Init(void); 	// OLED��ʼ������
void OLED_Clear(u8 data);          // ��������
void Oled_ShowPic(u8 page,u8 col,u8 height,u8 width,u8 *pic);//��ʾͼƬ
void Oled_clear(u8 page,u8 col,u8 height,u8 width);//���ĳ�ַ�
void Oled_ShowChar(u8 page,u8 col,u8 eng);//��ʾ�ַ�
void Oled_Showstring(u8 page,u8 col,u8*str);//��ʾ�ַ���
void Oled_ShowChi(u8 page,u8 col,u8*chi);//��ʾ����
void Oled_ShowAll(u8 page ,u8 col ,u8*str);//��ʾ��Ӣ�ַ���
void OLED_Scroll(void);//��������


#endif

