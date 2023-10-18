#include "stm32f4xx.h"

int soltou=0, soltou1=0;

int minutos=0;
int horas=0;
int minutosdez=0;
int horasdez=0;
int conta=0;

int numeros[10]={
		0b1000000,
		0b1111001,
		0b0100100,
		0b0110000,
		0b0011001,
		0b0010010,
		0b0000010,
		0b1111000,
		0b0000000,
		0b0010000};


void contador ()
{
if (minutos>9)
{
minutos=0;
minutosdez++;
}

if(minutosdez>5){
horas++;
minutosdez=0;}

if(horas>9){
horas=0;
horasdez++;}

if (horasdez==2 && horas>=4) {
		horasdez=0;
		horas=0;
		minutos=0;
		minutosdez=0;
	}
}



void TIM1_UP_TIM10_IRQHandler(void)
{

	TIM10->SR &=~ TIM_SR_UIF;
	GPIOB->ODR&=~0x000F;
	conta++;
	if(conta>3){
		conta=0;
	}

	switch(conta)
	{

	case 0:

		GPIOC->ODR=numeros[minutos];
		GPIOB->ODR=0b0001;
		break;

	case 1:

		GPIOC->ODR=numeros[minutosdez];
		GPIOB->ODR=0b010;
		break;

	case 2:

		GPIOC->ODR=numeros[horas];
		GPIOB->ODR=0b00100;
		break;

	case 3:

		GPIOC->ODR=numeros[horasdez];
		GPIOB->ODR=0b1000;

		break;
	}


	contador();





};

void TIM1_TRG_COM_TIM11_IRQHandler(void)
{

	TIM11->SR &=~ TIM_SR_UIF;

	minutos++;

};



int main(void){

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN|RCC_AHB1ENR_GPIOBEN|RCC_AHB1ENR_GPIOCEN;

	RCC->APB2ENR |= RCC_APB2ENR_TIM9EN | RCC_APB2ENR_TIM10EN | RCC_APB2ENR_TIM11EN;




	GPIOA->PUPDR &=~ (GPIO_PUPDR_PUPDR0|GPIO_PUPDR_PUPDR3);
	GPIOA->PUPDR |= (GPIO_PUPDR_PUPDR0_1|GPIO_PUPDR_PUPDR3_1);

	TIM9->PSC = 999;
	TIM9->ARR = 49;
	TIM9->CR1 = TIM_CR1_CEN;




	GPIOB->MODER|=GPIO_MODER_MODER0_0|GPIO_MODER_MODER1_0|GPIO_MODER_MODER2_0|GPIO_MODER_MODER3_0;
	GPIOC->MODER|=GPIO_MODER_MODER0_0|GPIO_MODER_MODER1_0|GPIO_MODER_MODER2_0|GPIO_MODER_MODER3_0|GPIO_MODER_MODER4_0|GPIO_MODER_MODER5_0|GPIO_MODER_MODER6_0|GPIO_MODER_MODER7_0|GPIO_MODER_MODER8_0|GPIO_MODER_MODER9_0;

	TIM10->PSC=999;
	TIM10->ARR=49;
	TIM10->CR1 = TIM_CR1_CEN;
	TIM10->DIER|=TIM_DIER_UIE;

	NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 2);
	NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);




	TIM11->PSC=999;
	TIM11->ARR=959999;
	TIM11->CR1|=TIM_CR1_CEN;
	TIM11->DIER|=TIM_DIER_UIE;



	NVIC_SetPriority(TIM1_TRG_COM_TIM11_IRQn, 1);
	NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);


	while(1)
	{

		if(((GPIOA->IDR & 0b01)==0b01) && soltou==0){
			minutos++;
			contador();
			soltou=1;
			TIM9->CNT=0;
			TIM9->SR &= ~(0x01);
			while((TIM9->SR & 0x01)==0){};

		};
		if((GPIOA->IDR & 0b01)==0){
			soltou=0;
		};

		if(((GPIOA->IDR & 0b01000)==0b01000) && soltou1==0){
			horas++;
			contador();
			soltou1=1;
			TIM9->CNT=0;
			TIM9->SR &= ~(0x01);
			while((TIM9->SR & 0x01)==0){};

		};
		if((GPIOA->IDR & 0b01000)==0){
			soltou1=0;
		};




	}

}


