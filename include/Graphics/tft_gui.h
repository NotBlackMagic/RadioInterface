#ifndef HAL_TFT_GUI_H_
#define HAL_TFT_GUI_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "tft_commands.h"

#include "font5x7.h"

//Color white =	{0xFF, 0xFF, 0xFF};
//Color silver =	{0xC0, 0xC0, 0xC0};
//Color gray =	{0x80, 0x80, 0x80};
//Color black =	{0x00, 0x00, 0x00};
//Color red =		{0xFF, 0x00, 0x00};
//Color aqua =	{0x00, 0xFF, 0xFF};
//Color blue =	{0x00, 0x00, 0xFF};
//Color teal =	{0x00, 0x80, 0x80};
//Color navy =	{0x00, 0x00, 0x80};
//Color purple =	{0x80, 0x00, 0x80};
//Color yellow =	{0xFF, 0xFF, 0x00};
//Color lime =	{0x00, 0xFF, 0x00};
//Color fuchsia =	{0xFF, 0x00, 0xFF};
//Color maroon =	{0x80, 0x00, 0x00};
//Color green =	{0x00, 0x80, 0x00};
//Color orange =	{0xFF, 0xA5, 0x00};
//Color olive =	{0x80, 0x80, 0x00};

typedef struct {
	Color white;
	Color silver;
	Color gray;
	Color black;
	Color red;
	Color aqua;
	Color blue;
	Color teal;
	Color navy;
	Color purple;
	Color yellow;
	Color lime;
	Color fuchsia;
	Color maroon;
	Color green;
	Color orange;
	Color olive;
} ColorsStruct;

extern ColorsStruct Colors888;
extern ColorsStruct Colors666;

Color ToRGB666Convertion(Color color);

void SetBackgroundColor(Color color);
void DrawLine(Vector2D pointA, Vector2D pointB, Color color);
void DrawRect(Vector2D position, Vector2D size, Color fillColor, uint8_t thickness, Color frameColor);
void DrawCircle(Vector2D position, uint16_t radius, Color fillColor, uint8_t thickness, Color frameColor);
//void DrawFilledRect(Vector2D position, Vector2D size, Color fillColor);
//void DrawFilledRectFramed(Vector2D position, Vector2D size, uint8_t thickness, Color fillColor, Color frameColor);
//void DrawFilledCircle(Vector2D position, uint16_t radius, Color fillColor);
//void DrawFilledCircleFramed(Vector2D position, uint16_t radius, uint8_t thickness, Color fillColor, Color frameColor);
void DrawASCIIText(Vector2D position, const char* text, uint8_t stringLength, uint8_t fontSize, Color textColor, Color backgroundColor);
void DrawASCIISynmbol(Vector2D position, uint8_t symbol, uint8_t fontSize, Color textColor, Color backgroundColor);
void DrawTextBox(Vector2D position, Vector2D size, uint8_t thickness, const char* text, uint8_t stringLength, uint8_t fontSize, Color textColor, Color backgroundColor, Color frameColor);

#ifdef __cplusplus
}
#endif

#endif /* HAL_TFT_GUI_H_ */
