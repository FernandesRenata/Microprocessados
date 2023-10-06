#include "main.h"
#include "stm32f4xx.h"

int led[8]={
		0b00000000,
		0b00000001,
		0b00000010,
		0b00000100,
		0b00001000,
		0b00010000,
		0b00100000,
		0b10000000
};
int leds[9]={
		0b000000001,
		0b000000011,
		0b000000111,
		0b000001111,
		0b000011111,
		0b000111111,
		0b001111111,
		0b011111111,
		0b111111111
};
int random[8]={
		0b00000000,
		0b001001100,
		0b011010110,
		0b011111111,
		0b010101010,
		0b001010101,
		0b011111111,
		0b00000000
};

int i = 0;
int chaves;
int controle=1;
int j = 8;

int main(void){

	RCC->AHB1ENR=0x00000087;
	RCC->APB2ENR |=1<<17;
	GPIOC->MODER |= GPIO_MODER_MODER0_0|GPIO_MODER_MODER1_0|GPIO_MODER_MODER2_0|GPIO_MODER_MODER3_0|GPIO_MODER_MODER4_0|GPIO_MODER_MODER5_0|GPIO_MODER_MODER6_0|GPIO_MODER_MODER7_0;
	GPIOB->MODER &=~(GPIO_MODER_MODER13|GPIO_MODER_MODER14);

	GPIOB->PUPDR &=~ (GPIO_PUPDR_PUPDR13 | GPIO_PUPDR_PUPDR14);

	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR13_1 | GPIO_PUPDR_PUPDR14_1;

	TIM10->CR1|=0b100000001;
	TIM10->PSC=999;


	while(1){
		chaves|=GPIOB->IDR & 0b110000000000000;
		chaves = chaves >> 13;

		if(TIM10->SR & 0b01){
			TIM10->SR &=0b00;

		switch(chaves){

			case 0b010:
				TIM10->ARR=7999;
				GPIOC->ODR= led[i];
				i++;
				if(i>8){
				controle=1;
					i=0;
					}
				break;

			case 0b011:
				TIM10->ARR=599;
				if(controle==1)
				{
								GPIOC->ODR=leds[j];
								j--;
								if(j<0){
									j=8;
									controle=0;
								}


							}

							else{
									GPIOC->ODR=leds[i];
									i++;
									if(i>8){
										controle=1;
										i=0;
									}
					}

						break;

			case  0b01:
				TIM10->ARR=999;
				GPIOC->ODR=random[i];
				i++;
				if(i>8){
				i=0;
					}
				break;

			default:
				TIM10->ARR=7999;
				GPIOC->ODR=0b0111111111;

			}
		}

	}
}


