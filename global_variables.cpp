#include <stdint.h>

#include "global_variables.h"


volatile  uint32_t t_div_1000;

int32_t sinus[360]          {};
volatile int32_t current_frequency   {0};
volatile int32_t des_frequency       {0};

//temporary global variables
volatile int32_t tim1_ccr1  {0};
volatile int32_t tim1_ccr2  {0};
volatile int32_t tim1_ccr3  {0};

