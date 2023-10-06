
/* Esse projeto tem como objetivo piscar o led*/


#include "main.h"
#include "stm32f4xx.h"


int main(void){

	RCC->AHB1ENR=0x00000087;
	GPIOC->MODER=GPIO_MODER_MODER0_0;
	RCC->APB2ENR|=1<<18;

	TIM11->PSC=1999;
	TIM11->ARR=1599;
	TIM11->CR1=0X01;
	while(1){

	if(TIM11->SR & TIM_SR_UIF){


			GPIOC->ODR^=0b01;
			TIM11->SR&=~(TIM_SR_UIF);


		}
	}
}
