#ifndef SYSTICK_H
#define SYSTICK_H

//Initializes the systick timer on the stm32f407
extern void SysTick_Init(void);

//Gets the current tick i.e. timer count
extern uint32_t SysTick_GetTick(void);

//Creates a blocking delay in milliseconds
extern void SysTick_DelayMs(uint32_t delayTime);



#endif /* SYSTICK_H */
