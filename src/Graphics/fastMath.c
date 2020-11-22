#include "fastMath.h"

float FastSin(float angleDeg) {
	if(angleDeg >= 0 && angleDeg <= 90) {
		//First Quadrant
		uint8_t index = (angleDeg / 3.f);
		float weigth = angleDeg - (index * 3);

		return (sinLookupTable[index] * weigth + sinLookupTable[index + 1] * (1 - weigth));
	}
	else if(angleDeg > 90 && angleDeg <= 180) {
		//Second Quadrant
		angleDeg = 180 - angleDeg;

		uint8_t index = (angleDeg / 3.f);
		float weigth = angleDeg - (index * 3);

		return (sinLookupTable[index] * weigth + sinLookupTable[index + 1] * (1 - weigth));
	}
	else if(angleDeg > 180 && angleDeg <= 270) {
		//Third Quadrant
		angleDeg = angleDeg - 180;

		uint8_t index = (angleDeg / 3.f);
		float weigth = angleDeg - (index * 3);

		return -(sinLookupTable[index] * weigth + sinLookupTable[index + 1] * (1 - weigth));
	}
	else if(angleDeg > 270 && angleDeg <= 360) {
		//Forth Quadrant
		angleDeg = 360 - angleDeg;

		uint8_t index = (angleDeg / 3.f);
		float weigth = angleDeg - (index * 3);

		return -(sinLookupTable[index] * weigth + sinLookupTable[index + 1] * (1 - weigth));
	}

	return 0;
}

float FastCos(float angleDeg) {
	float angle = 90 - angleDeg;
	if(angle < 0) {
		angle += 360;
	}
	return FastSin(angle);
}

float FastTan(float angleDeg) {

}
