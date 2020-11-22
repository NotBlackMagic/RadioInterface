#ifndef GRAPHICS_FASTMATH_H_
#define GRAPHICS_FASTMATH_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx.h"

static float sinLookupTable[32] = {	0.0000, 0.0523, 0.1045, 0.1564, 0.2079, 0.2588, 0.3090, 0.3584, 0.4067, 0.4540, 0.5000, 0.5446, 0.5878, 0.6293, 0.6691, 0.7071,
									0.7431, 0.7771, 0.8090, 0.8387, 0.8660, 0.8910, 0.9135, 0.9336, 0.9511, 0.9659, 0.9781, 0.9877, 0.9945, 0.9986, 1.0000, 0.9986};
//static float tanLookupTable[30] = {};

float FastSin(float angleDeg);
float FastCos(float angleDeg);
float FastTan(float angleDeg);

#ifdef __cplusplus
}
#endif

#endif /* GRAPHICS_FASTMATH_H_ */
