#ifndef _ADC_H
#define _ADC_H


#include "includes.h"

extern u8 light_value,soil_value;

extern u8 light_flag ,soil_flag;

void ADC1_Init(void);
u16 get_Adc_Value(u8 ch);//ͨ��һ����ֵ
void Get_light_Value(void);//��ȡ����ǿ��
void Get_soil_Value(void);//��ȡ����ʪ��




#endif

