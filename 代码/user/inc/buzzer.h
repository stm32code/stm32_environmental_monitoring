#ifndef _BUZZER_H
#define _BUZZER_H


#include "includes.h"


#define Buz_ON   PBout(1)=1
#define Buz_OFF  PBout(1)=0
#define Buz      PBout(1)

//extern u8 Temp;
//extern u8 Hum;
//extern u8 Light;
//extern u8 CO2;
//extern u8 Soil;
void Buz_Init(void);
void Voice_Loud(void);//±¨¾¯


#endif

