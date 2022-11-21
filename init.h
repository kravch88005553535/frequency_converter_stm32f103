#ifndef __INIT_H__
#define __INIT_H__

#include "global_variables.h"

extern int32_t sinus[360];
extern int32_t t_div_1000;
extern volatile int32_t current_frequency;
extern volatile int32_t des_frequency;

void init();

#endif  //__INIT_H__