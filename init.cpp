#include <stm32f10x.h>
#include <math.h>


#include "init.h"

void clock_init()
{
  RCC->CFGR |= RCC_CFGR_ADCPRE_1;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
}


void adc_init()
{
	ADC1->CR2 |= ADC_CR2_ADON; 
	ADC1->CR2 |= ADC_CR2_CAL;
	while ((ADC1->CR2 & ADC_CR2_CAL) > 0) asm ("nop");
	ADC1-> JSQR &= ~ADC_JSQR_JL;
	ADC1->CR1 |= ADC_CR1_JEOCIE;
	ADC1-> CR2 |= ADC_CR2_JEXTTRIG;	
	ADC1-> CR2 |= ADC_CR2_JEXTSEL; 
	ADC1-> SMPR2 |= ADC_SMPR2_SMP0;
	ADC1-> JSQR |= 0;
	ADC1->CR2 |= ADC_CR2_ADON;
}


void interrupt_init()
{
//	AFIO->EXTICR[1] |= AFIO_EXTICR2_EXTI6_PB;
  
  NVIC_EnableIRQ (TIM1_UP_IRQn);
//	NVIC_EnableIRQ (TIM3_IRQn);
//	NVIC_EnableIRQ (TIM4_IRQn);
//	NVIC_EnableIRQ (ADC1_2_IRQn);
//	NVIC_EnableIRQ (EXTI9_5_IRQn);
//	EXTI->IMR |= EXTI_IMR_MR6;
//	EXTI->FTSR |= EXTI_FTSR_TR6;	
//	EXTI->RTSR |= EXTI_RTSR_TR6;	
}


void gpio_init()
{
	GPIOA->CRL &= ~GPIO_CRL_CNF0_0; 
	GPIOA->CRH |= GPIO_CRH_MODE8;
	GPIOA->CRH |= GPIO_CRH_CNF8_1;
	GPIOA->CRH ^= GPIO_CRH_CNF8_0;	
	GPIOA->CRH |= GPIO_CRH_MODE9;
	GPIOA->CRH |= GPIO_CRH_CNF9_1;
	GPIOA->CRH ^= GPIO_CRH_CNF9_0;
	GPIOA->CRH |= GPIO_CRH_MODE10;
	GPIOA->CRH |= GPIO_CRH_CNF10_1;
	GPIOA->CRH ^= GPIO_CRH_CNF10_0;
	
	GPIOB->CRL &= ~GPIO_CRL_CNF6;
	GPIOB->CRL |= GPIO_CRL_CNF6_1;
	GPIOB->CRL &= ~GPIO_CRL_MODE6;
	GPIOB->BSRR |= GPIO_BSRR_BS6;

	GPIOB->CRH |= GPIO_CRH_MODE13;
	GPIOB->CRH |= GPIO_CRH_CNF13_1;
	GPIOB->CRH ^= GPIO_CRH_CNF13_0;
	GPIOB->CRH |= GPIO_CRH_MODE14;
	GPIOB->CRH |= GPIO_CRH_CNF14_1;
	GPIOB->CRH ^= GPIO_CRH_CNF14_0;
	GPIOB->CRH |= GPIO_CRH_MODE15;
	GPIOB->CRH |= GPIO_CRH_CNF15_1;
	GPIOB->CRH ^= GPIO_CRH_CNF15_0;	
}


void timers_init()
{
  const uint32_t systick_1sec_tick_value{9000000};
  
	SysTick->LOAD = systick_1sec_tick_value;
	t_div_1000 = SysTick->LOAD / 1000;
	SysTick->CTRL |= SysTick_CTRL_ENABLE;
	
	TIM1->ARR = 12000;  //6kHz
	TIM1->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
	TIM1->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
	TIM1->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;
	TIM1->CCMR1 |= TIM_CCMR1_OC1PE;
	TIM1->CCMR1 |= TIM_CCMR1_OC2PE;
	TIM1->CCMR2 |= TIM_CCMR2_OC3PE;
	TIM1->CR1|= TIM_CR1_ARPE;
	TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E;
	TIM1->CCER |= TIM_CCER_CC1NE | TIM_CCER_CC2NE | TIM_CCER_CC3NE;
	TIM1->BDTR = (TIM_BDTR_DTG&0b01001000);
	TIM1->DIER |= TIM_DIER_UIE;
	TIM1->EGR |= TIM_EGR_UG;
	TIM1->CR1 |= TIM_CR1_CEN;

	TIM3->CR1 |= TIM_CR1_OPM;
	TIM3->ARR = 65000;		
	TIM3->PSC = 2106;	
	TIM3->EGR |= TIM_EGR_UG;
	TIM3->SR &= ~TIM_SR_UIF;
	TIM3->DIER |= TIM_DIER_UIE;
	
	TIM4->ARR = 1600;		
	TIM4->PSC = 1024;		 
	TIM4->EGR |= TIM_EGR_UG;
	TIM4->SR &= ~TIM_SR_UIF;
	TIM4->DIER |= TIM_DIER_UIE; 
	TIM4->DIER |=TIM_DIER_TIE;
	TIM4->CR1 |= TIM_CR1_CEN;
}



void init()
{
  const double deg2rad{0.0174532925199};
	
  current_frequency = 9;
  des_frequency = 9;
	for (int i=0; i<360; i++) {
    sinus [i] = static_cast<int32_t>(sin(i*deg2rad)*100000);
  }
  
	clock_init();
  adc_init();
  interrupt_init();
  gpio_init();
  timers_init();
}
  