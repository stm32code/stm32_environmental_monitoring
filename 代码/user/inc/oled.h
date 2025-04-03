#ifndef __OLED_H
#define __OLED_H


#include "includes.h"


/*--------------------引脚定义--------------------------*/
#define 		OLED_SCLK_Set()			GPIO_SetBits(GPIOB,GPIO_Pin_12)	          //  PA6（SCL）输出高
#define			OLED_SCLK_Clr()			GPIO_ResetBits(GPIOB,GPIO_Pin_12)	        //  PA6（SCL）输出低

#define			OLED_SDIN_Set()			GPIO_SetBits(GPIOB,GPIO_Pin_13)	          //  PA5（SDA）输出高
#define			OLED_SDIN_Clr()			GPIO_ResetBits(GPIOB,GPIO_Pin_13)	        //  PA5（SDA）输出高
#define 		OLED_READ_SDIN()		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13)	//  读取PA5（SDA）电平
		

/*definition--------------------------------------------*/


			  				   
#define	IIC_ACK		0		//应答
#define	IIC_NO_ACK	1		//不应答




/*-----------------声明函数-----------------------------*/
void OLED_Init(void); 	// OLED初始化函数
void OLED_Clear(u8 data);          // 清屏函数
void Oled_ShowPic(u8 page,u8 col,u8 height,u8 width,u8 *pic);//显示图片
void Oled_clear(u8 page,u8 col,u8 height,u8 width);//清空某字符
void Oled_ShowChar(u8 page,u8 col,u8 eng);//显示字符
void Oled_Showstring(u8 page,u8 col,u8*str);//显示字符串
void Oled_ShowChi(u8 page,u8 col,u8*chi);//显示汉字
void Oled_ShowAll(u8 page ,u8 col ,u8*str);//显示汉英字符串
void OLED_Scroll(void);//滚屏函数


#endif

