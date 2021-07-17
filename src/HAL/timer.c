#include "timer.h"

/**
  * @brief	This function initializes the TIM2, used to count time
  * @param	None
  * @return	None
  */
void TIM2Init() {
	//Enable bus clocks
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);

	//Configure the Timer: TIM2 is connected to APB1 Timer clocks which has the APB1 clock = 72MHz
	LL_TIM_SetPrescaler(TIM2, 71);					//Set Clock to 1MHz (1us); Fpwm = 72MHz / ((Prescaler + 1) * Compare)
	LL_TIM_SetCounterMode(TIM2, LL_TIM_COUNTERMODE_UP);
	LL_TIM_SetAutoReload(TIM2, UINT16_MAX);
	LL_TIM_EnableARRPreload(TIM2);

	//This is needed to update the prescaler
	LL_TIM_GenerateEvent_UPDATE(TIM2);

	//Enable Timer
//	LL_TIM_EnableCounter(TIM2);
}

void TIM2Start() {
	//Reset Counter value
	LL_TIM_SetCounter(TIM2, 0);

	//Start Timer
	LL_TIM_EnableCounter(TIM2);
}

uint32_t TIM2Stop() {
	//Stop Timer
	LL_TIM_DisableCounter(TIM2);
	//Return Counter value
	return LL_TIM_GetCounter(TIM2);
}
