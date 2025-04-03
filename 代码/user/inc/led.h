#ifndef _LED_H
#define _LED_H


#include "includes.h"

#define LED_ON   PBout(0)=0
#define LED_OFF  PBout(0)=1
#define LED  PBout(0)



void Led_Init(void);
void TIM3_Init(void);


#endif

