#include "main.h"
#include "stm32f4xx.h"

int chaves;

int main()
{



	RCC->AHB1ENR=0x00000087;
	GPIOC->MODER &=~(GPIO_MODER_MODER0|GPIO_MODER_MODER1|GPIO_MODER_MODER2|GPIO_MODER_MODER3);
	GPIOB->MODER |= GPIO_MODER_MODER0_0;


  while (1)
  {

	  chaves = GPIOC->IDR & 0b1111;

	  switch(chaves){
	  case 0b0110:
		  GPIOB->ODR=0b01;
		  	  break;
	  case 0b1001:
		  GPIOB->ODR=0b01;
		  	  break;
	  case 0b1100:
		  GPIOB->ODR=0b01;
		  	  break;
	  case 0b0011:
		  GPIOB->ODR=0b01;
		  	  break;
	  case 0b1010:
		  GPIOB->ODR=0b01;
		  	 break;
	  case 0b0101:
		  GPIOB->ODR=0b01;
		    break;


	  default:
		  GPIOB->ODR=0b00;
		  break;


	  }

  }
}

