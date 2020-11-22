#ifndef HAL_TFT_COMMANDS_H_
#define HAL_TFT_COMMANDS_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "tft_interface.h"

typedef struct Color {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} Color;

typedef struct Vector2D {
	uint16_t x;
	uint16_t y;
} Vector2D;

void SetHorizontalArea(uint16_t start, uint16_t end);
void SetVerticalArea(uint16_t start, uint16_t end);
void SetColumn(uint16_t column);
void SetLine(uint16_t line);
void SetPoint(Vector2D position);
void SetPixel(Vector2D position, Color color);
void EnterVerticalScroll(uint16_t startScrollArea, uint16_t scrollAreaLength);
void VerticalScrollStep(uint16_t stepLines);
void ExitVerticalScroll();

void SetMemoryAccess();
void SetPixelFormat();
void TurnDisplayON();
void TurnDisplayOFF();
void SoftwareReset();
void ReadDisplayStatus();
void ExitSleepMode();
void EnterSleepMode();

#ifdef __cplusplus
}
#endif

#endif /* HAL_TFT_COMMANDS_H_ */
