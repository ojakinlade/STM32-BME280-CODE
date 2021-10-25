#ifndef _SYSTEM_H
#define _SYSTEM_H


typedef struct
{
	uint32_t start; 
	uint32_t ticksToWait; 
	bool isCounting;
}sysTimer_t;


extern void System_Init(void);
extern void System_Timer_DelayMs(uint32_t delayTime);
extern void System_TimerInit(sysTimer_t* pSysTimer, uint32_t timerRepTime);
extern bool System_TimerDoneCounting(sysTimer_t* pSysTimer);

#endif //_SYSTEM_H
