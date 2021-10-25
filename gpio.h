#ifndef GPIO_H
#define GPIO_H

enum GPIO_Alt_Func
{
	TIM_1_2 = 0x01,
	TIM_3_4_5 = 0x02,
	TIM_8_9_10_11 = 0x03,
	I2C_1_2 = 0x04,
	SPI_1_2 = 0x05,
	SPI_3 = 0x06,
	USART_1_2_3 = 0x07,
	USART_4_5_6 = 0x08,
	TIM_12_13_14 = 0x09,
	OTG_FS_HS = 0x0A
};	

#define GPIO_INPUT_MODE									0x00
#define GPIO_PULLUP_ENABLE							true

#define GPIO_PIN0												0
#define GPIO_PIN0_GEN_PUR_OUTPUT				GPIO_MODER_MODE0_0
#define GPIO_PIN0_ALT_FUNCTION					GPIO_MODER_MODE0_1
#define GPIO_PIN0_ANALOG_MODE						GPIO_MODER_MODE0

#define GPIO_PIN1												1
#define GPIO_PIN1_GEN_PUR_OUTPUT				GPIO_MODER_MODE1_0
#define GPIO_PIN1_ALT_FUNCTION					GPIO_MODER_MODE1_1
#define GPIO_PIN1_ANALOG_MODE						GPIO_MODER_MODE1

#define GPIO_PIN2												2
#define GPIO_PIN2_GEN_PUR_OUTPUT				GPIO_MODER_MODE2_0
#define GPIO_PIN2_ALT_FUNCTION					GPIO_MODER_MODE2_1
#define GPIO_PIN2_ANALOG_MODE						GPIO_MODER_MODE2

#define GPIO_PIN3												3
#define GPIO_PIN3_GEN_PUR_OUTPUT				GPIO_MODER_MODE3_0
#define GPIO_PIN3_ALT_FUNCTION					GPIO_MODER_MODE3_1
#define GPIO_PIN3_ANALOG_MODE						GPIO_MODER_MODE3

#define GPIO_PIN4												4
#define GPIO_PIN4_GEN_PUR_OUTPUT				GPIO_MODER_MODE4_0
#define GPIO_PIN4_ALT_FUNCTION					GPIO_MODER_MODE4_1
#define GPIO_PIN4_ANALOG_MODE						GPIO_MODER_MODE4

#define GPIO_PIN5												5
#define GPIO_PIN5_GEN_PUR_OUTPUT				GPIO_MODER_MODE5_0
#define GPIO_PIN5_ALT_FUNCTION					GPIO_MODER_MODE5_1
#define GPIO_PIN5_ANALOG_MODE						GPIO_MODER_MODE5

#define GPIO_PIN6												6
#define GPIO_PIN6_GEN_PUR_OUTPUT				GPIO_MODER_MODE6_0
#define GPIO_PIN6_ALT_FUNCTION					GPIO_MODER_MODE6_1
#define GPIO_PIN6_ANALOG_MODE						GPIO_MODER_MODE6

#define GPIO_PIN7												7
#define GPIO_PIN7_GEN_PUR_OUTPUT				GPIO_MODER_MODE7_0
#define GPIO_PIN7_ALT_FUNCTION					GPIO_MODER_MODE7_1
#define GPIO_PIN7_ANALOG_MODE						GPIO_MODER_MODE7

#define GPIO_PIN8												8
#define GPIO_PIN8_GEN_PUR_OUTPUT				GPIO_MODER_MODE8_0
#define GPIO_PIN8_ALT_FUNCTION					GPIO_MODER_MODE8_1
#define GPIO_PIN8_ANALOG_MODE						GPIO_MODER_MODE8

#define GPIO_PIN9												9
#define GPIO_PIN9_GEN_PUR_OUTPUT				GPIO_MODER_MODE9_0
#define GPIO_PIN9_ALT_FUNCTION					GPIO_MODER_MODE9_1
#define GPIO_PIN9_ANALOG_MODE						GPIO_MODER_MODE9

#define GPIO_PIN10											10
#define GPIO_PIN10_GEN_PUR_OUTPUT				GPIO_MODER_MODE10_0
#define GPIO_PIN10_ALT_FUNCTION					GPIO_MODER_MODE10_1
#define GPIO_PIN10_ANALOG_MODE					GPIO_MODER_MODE10

#define GPIO_PIN11											11
#define GPIO_PIN11_GEN_PUR_OUTPUT				GPIO_MODER_MODE11_0
#define GPIO_PIN11_ALT_FUNCTION					GPIO_MODER_MODE11_1
#define GPIO_PIN11_ANALOG_MODE					GPIO_MODER_MODE11

#define GPIO_PIN12											12
#define GPIO_PIN12_GEN_PUR_OUTPUT				GPIO_MODER_MODE12_0
#define GPIO_PIN12_ALT_FUNCTION					GPIO_MODER_MODE12_1
#define GPIO_PIN12_ANALOG_MODE					GPIO_MODER_MODE12

#define GPIO_PIN13											13
#define GPIO_PIN13_GEN_PUR_OUTPUT				GPIO_MODER_MODE13_0
#define GPIO_PIN13_ALT_FUNCTION					GPIO_MODER_MODE13_1
#define GPIO_PIN13_ANALOG_MODE					GPIO_MODER_MODE13

#define GPIO_PIN14											14
#define GPIO_PIN14_GEN_PUR_OUTPUT				GPIO_MODER_MODE14_0
#define GPIO_PIN14_ALT_FUNCTION					GPIO_MODER_MODE14_1
#define GPIO_PIN14_ANALOG_MODE					GPIO_MODER_MODE14

#define GPIO_PIN15											15
#define GPIO_PIN15_GEN_PUR_OUTPUT				GPIO_MODER_MODE15_0
#define GPIO_PIN15_ALT_FUNCTION					GPIO_MODER_MODE15_1
#define GPIO_PIN15_ANALOG_MODE					GPIO_MODER_MODE15


extern void GPIO_Input_Init(GPIO_TypeDef* gpioPort, uint8_t gpioPin, bool pullUpEn);
extern void GPIO_Output_Init(GPIO_TypeDef* gpioPort, uint32_t gpioMode);
extern void GPIO_Alt_Func_Init(GPIO_TypeDef* gpioPort, uint32_t gpioMode, uint8_t gpioPin, uint8_t gpioAltFunc);
extern void GPIO_Analog_Init(GPIO_TypeDef* gpioPort, uint32_t gpioMode);
extern void GPIO_Output_Write(GPIO_TypeDef* gpioPort, uint8_t gpioPin, bool gpioPinLogic);
extern void GPIO_Output_Clear_Reg(GPIO_TypeDef* gpioPort, uint32_t gpioPins);
extern void GPIO_Output_Reg_Write(GPIO_TypeDef* gpioPort, uint32_t gpioPins);
extern bool GPIO_Input_Read(GPIO_TypeDef* gpioPort, uint8_t gpioPin);
extern bool GPIO_Output_Read(GPIO_TypeDef* gpioPort, uint8_t gpioPin);



#endif /* GPIO_H */

