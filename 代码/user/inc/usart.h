#ifndef _USART_H_
#define _USART_H_

#include "includes.h"

typedef struct 
{
	u8 data[512];
	u16 leng;
	u8 flag;

}re_data;




void Usart1_Init(u32 bp);
void Send_Byte(u16 data);
u16 Rece_Byte(void);
void Data_Echo(void);




#endif

