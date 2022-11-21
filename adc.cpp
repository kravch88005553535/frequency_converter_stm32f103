#include <stm32f10x.h>
 
#include "global_variables.h"

#ifdef __cplusplus
  extern "C" {
#endif

void TIM4_IRQHandler (void)
{
	ADC1->CR2 |= ADC_CR2_JSWSTART;
	do TIM4->SR &=	~TIM_SR_UIF;
	while ((TIM4->SR & TIM_SR_UIF) == TIM_SR_UIF);
}

void ADC1_2_IRQHandler (void)		
{
	des_frequency = (ADC1->JDR1 * 100) / 0xFFF;  
	des_frequency <9 ? des_frequency = 9 : des_frequency;
	des_frequency >99 ? des_frequency = 99 : des_frequency;
  do ADC1->SR &= ~ADC_SR_JEOC;
  while ((ADC1->SR & ADC_SR_JEOC) == ADC_SR_JEOC);
}

#ifdef __cplusplus
  }
#endif