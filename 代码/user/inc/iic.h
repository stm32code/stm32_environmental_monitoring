#ifndef _IIC_H
#define _IIC_H


#include "includes.h"

#define IIC_SCL_H   PBout(6)=1
#define IIC_SCL_L   PBout(6)=0

#define IIC_SDA_H   PBout(7)=1
#define IIC_SDA_L   PBout(7)=0

#define IIC_SDA_In   PBin(7)

void IIC_Port_Init(void);
void IIC_Start(u8 us);
void IIC_Stop(u8 us);
void IIC_SendAck(u8 ack ,u8 us);
u8 IIC_RecAck(u8 us);
u8 IIC_SendData(u8 date,u8 us);
u8 IIC_RecData(u8 ack,u8 us);



#endif


