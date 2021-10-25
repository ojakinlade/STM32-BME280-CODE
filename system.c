#include "stm32f4xx.h"                  // Device header
#include <stdbool.h>
#include "clocks.h"
#include "gpio.h"
#include "system.h"
#include "systick.h"


void System_Init(void)
{
	/*
	Description:
	
	Parameters:
	
	Return:
	
	*/
	
	Clocks_Init();
	SysTick_Init();

}

void System_Timer_DelayMs(uint32_t delayTime)
{
	/*
	Description:
	
	Parameters:
	
	Return:
	
	*/
	
	SysTick_DelayMs(delayTime);
}

void System_TimerInit(sysTimer_t* pSysTimer, uint32_t timerRepTime)
{
	pSysTimer->start = 0;
	pSysTimer->isCounting = false;
	pSysTimer->ticksToWait = timerRepTime;
}

bool System_TimerDoneCounting(sysTimer_t* pSysTimer)
{
	bool countingComplete = false;
	
	if (!pSysTimer->isCounting)
	{
		pSysTimer->start = SysTick_GetTick();
		pSysTimer->isCounting = true;
	}
	
	else
	{
		if ((SysTick_GetTick() - pSysTimer->start) >= pSysTimer->ticksToWait)
		{
			countingComplete = true;
			pSysTimer->start = 0;
			pSysTimer->isCounting = false;
		}
	}
	return countingComplete;
}