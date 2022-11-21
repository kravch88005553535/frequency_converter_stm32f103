#include <stm32f10x.h>

#include "global_variables.h"

#ifdef __cplusplus
  extern "C" {
#endif

void EXTI9_5_IRQHandler (void)
{
	TIM3->CR1 |= TIM_CR1_CEN;	
	EXTI->PR |= EXTI_PR_PR6;	
}
    
void TIM3_IRQHandler (void)
{
		char odr_val = static_cast <bool> (GPIOB->ODR & GPIO_ODR_ODR6);
		 switch (odr_val)	
		 {
				 case 0:
				 {
					 TIM1->BDTR |= TIM_BDTR_MOE;
					 NVIC_EnableIRQ (TIM1_UP_IRQn);
					 current_frequency = 9;
				 }
				 break;
				 case 1:
				 {
					 TIM1->BDTR &= ~TIM_BDTR_MOE;
					 NVIC_DisableIRQ (TIM1_UP_IRQn);
					 current_frequency=0;
				 }
				 break;
		 } 
	do TIM3->SR &=	~TIM_SR_UIF;
	while ((TIM3->SR & TIM_SR_UIF) == TIM_SR_UIF);
}

#ifdef __cplusplus
  }
#endif