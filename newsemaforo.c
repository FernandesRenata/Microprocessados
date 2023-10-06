#include "main.h"
#include "stm32f4xx.h"
int conta=0;
int main(void)
{
																																									RCC->AHB1ENR=0x00000087;
	RCC->APB2ENR|= RCC_APB2ENR_TIM10EN;
	GPIOC->MODER|=GPIO_MODER_MODER0_0|GPIO_MODER_MODER1_0|GPIO_MODER_MODER2_0|GPIO_MODER_MODER3_0|GPIO_MODER_MODER4_0|GPIO_MODER_MODER5_0;
	TIM10->PSC=999;
	TIM10->ARR=1599;
	TIM10->CR1=TIM_CR1_CEN;


	while(1){
		if(TIM10->SR & 0b01){
			TIM10->SR &=~0b01;
			conta++;
			switch(conta){
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
					GPIOC->ODR=0b0100001;
					break;
				case 8:
				case 9:
				case 10:
				case 11:
				case 12:
					GPIOC->ODR=0b0100011;
					break;
				case 13:
				case 14:
					GPIOC->ODR=0b001100;
					break;
				case 15:
				case 16:
				case 17:
				case 18:
				case 19:
					GPIOC->ODR=0b011100;
					conta=0;
					break;
					break;
		}

	}

}
}
