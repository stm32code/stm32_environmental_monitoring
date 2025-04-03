#ifndef _ACT24_H 
#define _ACT24_H


#include "includes.h"
void Act24_Init(void);
u8 At24cxx_WriteByte(u8 addr ,u8 date,u8 us);
u8 Act24_Ran_Read (u8 addr,u8 *date,u8 us);
u8 Act24_PageWrite(u8*data,u8 addr,u16 len,u8 us);
u8 Act24_ContinueRead(u8*data,u8 addr,u16 len,u8 us);
void Act24_AutoWrite(u8*data,u8 addr,u16 len,u8 us);
void Pass_lock(void);//¼ÇÒäÄ£¿é

#endif
