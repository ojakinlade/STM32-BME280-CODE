#include "stm32f4xx.h"                  // Device header
#include "clocks.h"

void Clocks_Init(void)
{
	/*
	@brief:
	Initializes all required device peripherals clocks.
	
	@param:
	None
	
	@return:
	None
	
	*/
	
	while( (RCC->CR & RCC_CR_HSIRDY) != RCC_CR_HSIRDY); /* Wait till HSI clock becomes ready */
	//System clock = 8MHz
	RCC->CFGR |= RCC_CFGR_HPRE_DIV2;
	//Enable clock for USART2 and 3, I2C1...3
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN | RCC_APB1ENR_USART3EN |RCC_APB1ENR_I2C1EN
									| RCC_APB1ENR_I2C2EN | RCC_APB1ENR_I2C3EN;
	//Enable clock for USART 1 and 6
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_USART6EN;
	//Enable clock for DMA1 and 2
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN | RCC_AHB1ENR_DMA2EN;
  //Enable for clock for GPIOA, GPIOB, GPIOC, GPIOD
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN;
		
}
