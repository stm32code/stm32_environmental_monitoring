#ifndef _FAN_H
#define _FAN_H


#include "includes.h"


#define Fan_ON  		PBout(15)=1
#define Fan_OFF 	PBout(15)=0
#define Fan       PBout(15)


void Fan_Init(void);

//void Fan_Open(u16 speed);



#endif

