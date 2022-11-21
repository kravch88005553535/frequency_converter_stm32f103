#include <stm32f10x.h>

#include "pwm.h"
#include "init.h"
#include "math.h"

#ifdef __cplusplus
  extern "C" {
#endif 
void TIM1_UP_IRQHandler (void)
{
  static int32_t ph_A_pwm{0};
  static int32_t ph_B_pwm{0};
  static int32_t ph_C_pwm{0};

  static int32_t addent{0};
  static int32_t delta{0};
  static int32_t t{0};
  static int32_t time_quanta{0};
  static int32_t switch_param{0};
  static int32_t current_sin_coeff{0}; 
  
  t = SysTick->VAL * 100 / t_div_1000;
	
  current_sin_coeff = (36*current_frequency*t/10000)%360;
		
	if (des_frequency != current_frequency)
	{ 
		delta = des_frequency - current_frequency;
		time_quanta = SysTick->LOAD * 100 / t_div_1000/current_frequency;  

		if (current_frequency < 20) addent = 40;
		else if (current_frequency < 25) addent = 10;
		else if (current_frequency < 35) addent = 2;
		else if (current_frequency < 60) addent = 3;
		else if (current_frequency > 60) addent = 4;
		
		
		if( (t<(SysTick->LOAD * 100 / t_div_1000)-time_quanta) 
			&&(t>(SysTick->LOAD * 100 / t_div_1000)-time_quanta-100) )
			{	
				if (addent >= 10)
				{
				SysTick->VAL = 0;		
				absolute(delta) < addent/10 ? current_frequency+=delta : (current_frequency += delta/absolute(delta)*addent/10) ;
				}
				else
				{
				switch_param++;
					switch_param == addent ? (switch_param = 0, SysTick->VAL = 0, current_frequency += delta/absolute(delta)):1;
				}
			}
	}	
	
	ph_A_pwm = sinus[current_sin_coeff]; 
	ph_B_pwm = sinus[(current_sin_coeff + 120)%360]; 
	ph_C_pwm = sinus[(current_sin_coeff + 240)%360];
	tim_pwm_asign (ph_A_pwm, ph_B_pwm, ph_C_pwm);
		
	do TIM1->SR &=	~TIM_SR_UIF;
	while ((TIM1->SR & TIM_SR_UIF) == TIM_SR_UIF);
}

#ifdef __cplusplus
  }
#endif 

void tim_pwm_asign (int val1, int val2, int val3)
{		
//    TIM1->CCR1 = TIM1->ARR/2 - (TIM1->ARR/2/1000 * val1 * current_frequency /50 /100);
//		TIM1->CCR2 = TIM1->ARR/2 - (TIM1->ARR/2/1000 * val2 * current_frequency /50 /100);
//		TIM1->CCR3 = TIM1->ARR/2 - (TIM1->ARR/2/1000 * val3 * current_frequency /50 /100);
	if (current_frequency <=50)	
	{
		TIM1->CCR1 = TIM1->ARR/2 - (TIM1->ARR/2/1000 * val1 * current_frequency /50 /100);
		TIM1->CCR2 = TIM1->ARR/2 - (TIM1->ARR/2/1000 * val2 * current_frequency /50 /100);
		TIM1->CCR3 = TIM1->ARR/2 - (TIM1->ARR/2/1000 * val3 * current_frequency /50 /100);
	}
	else
	{
		TIM1->CCR1 = TIM1->ARR/2 - (TIM1->ARR/2/1000 * val1 * current_frequency /50 /100);
		TIM1->CCR2 = TIM1->ARR/2 - (TIM1->ARR/2/1000 * val2 * current_frequency /50 /100);
		TIM1->CCR3 = TIM1->ARR/2 - (TIM1->ARR/2/1000 * val3 * current_frequency /50 /100);
	}
}

