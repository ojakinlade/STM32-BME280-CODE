#include "stm32f4xx.h"                  // Device header
#include <stdbool.h>
#include "gpio.h"


void GPIO_Input_Init(GPIO_TypeDef* gpioPort, uint8_t gpioPin, bool pullUpEn)
{
	/*
	@brief:
	@param:
	@return:
	*/
	
	gpioPort->MODER |= (GPIO_INPUT_MODE << gpioPin);
	
	if(pullUpEn)
	{
		gpioPort->PUPDR |= (1 << gpioPin * 2);
	}
	
}

void GPIO_Output_Init(GPIO_TypeDef* gpioPort, uint32_t gpioMode)
{
	gpioPort->MODER |= gpioMode;
}

void GPIO_Alt_Func_Init(GPIO_TypeDef* gpioPort, uint32_t gpioMode, uint8_t gpioPin, uint8_t gpioAltFunc)
{
	/*
	@brief:
	@param:
	@return:
	*/
	gpioPort->MODER |= gpioMode;
	
	if(gpioPin >= 8)
	{
		gpioPort->AFR[1] |= (gpioAltFunc << ((gpioPin % 8) * 4) );
	}
	else
	{
		gpioPort->AFR[0] |= (gpioAltFunc << (gpioPin * 4));
	}
}

void GPIO_Analog_Init(GPIO_TypeDef* gpioPort, uint32_t gpioMode)
{
	/*
	@brief:
	@param:
	@return:
	*/
	
	gpioPort->MODER |= gpioMode;
}

void GPIO_Output_Write(GPIO_TypeDef* gpioPort, uint8_t gpioPin, bool gpioPinLogic)
{
	/*
	@brief:
	@param:
	@return:
	*/
	
	
	
	if(gpioPinLogic)
	{
		gpioPort->ODR |= (1 << gpioPin);
	}
	else
		gpioPort->ODR &= ~(1 << gpioPin);
	
}

void GPIO_Output_Clear_Reg(GPIO_TypeDef* gpioPort, uint32_t gpioPins)
{
	gpioPort->ODR &= ~gpioPins;
}

void GPIO_Output_Reg_Write(GPIO_TypeDef* gpioPort, uint32_t gpioPins)
{
	gpioPort->ODR |= gpioPins;
}

bool GPIO_Input_Read(GPIO_TypeDef* gpioPort, uint8_t gpioPin)
{
	/*
	Description:
	Reads a GPIO pin and returns its logic level or state
	
	Parameters:
	1.) gpioPort: pointer to GPIO_TypeDef struct which contains
	all registers for the desired GPIO peripheral
	e.g. if gpioPort is passed an argument of GPIOA, the GPIOA peripheral
	is configured and if passed an argument of GPIOB, the GPIOB peripheral
	is configured etc.
	
	2.) gpioPin: Pin number of GPIO input pin e.g. if this parameter is passed with 
	GPIO_PINx, the state of pin x will be read
	
	Return:
	1.) true if GPIO pin is high
	2.) false if GPIO pin is low
	
	*/
	
	if ( (gpioPort->IDR & (1<<gpioPin)) == (1<<gpioPin) )
	{
		return true;
	}
	
	return false;
}

bool GPIO_Output_Read(GPIO_TypeDef* gpioPort, uint8_t gpioPin)
{
	if ( (gpioPort->ODR & (1<<gpioPin)) == (1<<gpioPin) )
	{
		return true;
	}
	
	return false;	
}


