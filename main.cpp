#include <stm32f10x.h>
#include "init.h"

int main()
{ 
  init();
  
  
  while (1){
  tim1_ccr1 = TIM1->CCR1;
  tim1_ccr2 = TIM1->CCR2;
  tim1_ccr3 = TIM1->CCR3;
  }     
}
