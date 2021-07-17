#include "stopwatch.h"

/**
  * @brief	This function initializes the TIM2, used to count time, as a Stopwatch
  * @param	None
  * @return	None
  */
void StopwatchInit() {
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

/**
  * @brief	This function starts the TIM2, starts the time counting of the Stopwatch
  * @param	None
  * @return	None
  */
void StopwatchStart() {
	//Reset Counter value
	LL_TIM_SetCounter(TIM2, 0);

	//Start Timer
	LL_TIM_EnableCounter(TIM2);
}

/**
  * @brief	This function resets the TIM2 counter, resets the time of the Stopwatch
  * @param	None
  * @return	Passed time in us
  */
uint32_t StopwatchReset() {
	//Get Counter value
	uint32_t counter = LL_TIM_GetCounter(TIM2);

	//Reset Counter value
	LL_TIM_SetCounter(TIM2, 0);

	//Return Counter value
	return counter;
}

/**
  * @brief	This function stops the TIM2, stops the time counting of the Stopwatch and resets the counter
  * @param	None
  * @return	Passed time in us
  */
uint32_t StopwatchStop() {
	//Stop Timer
	LL_TIM_DisableCounter(TIM2);
	//Return Counter value
	return LL_TIM_GetCounter(TIM2);
}
