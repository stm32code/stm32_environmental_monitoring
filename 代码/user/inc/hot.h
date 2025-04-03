#ifndef _Hot_H
#define _Hot_H


#include "includes.h"


#define Hot_ON  PAout(7)=1
#define Hot_OFF PAout(7)=0
#define Hot    PAout(7)

void Hot_Init(void);




#endif

