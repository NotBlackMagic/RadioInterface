#ifndef HAL_TIMER_H_
#define HAL_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h"

void TIM2Init();

void TIM2Start();
uint32_t TIM2Stop();

#ifdef __cplusplus
}
#endif

#endif /* HAL_TIMER_H_ */
