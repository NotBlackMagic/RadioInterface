#ifndef HAL_STOPWATCH_H_
#define HAL_STOPWATCH_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h"

void StopwatchInit();
void StopwatchStart();
uint32_t StopwatchReset();
uint32_t StopwatchStop();

#ifdef __cplusplus
}
#endif

#endif /* HAL_STOPWATCH_H_ */
