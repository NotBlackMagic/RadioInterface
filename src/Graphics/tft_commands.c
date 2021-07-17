#include "tft_commands.h"

void SetVerticalArea(uint16_t start, uint16_t end) {
	TFT_Command(PASET);
	TFT_Data((uint8_t)(start>>8));
	TFT_Data((uint8_t)start);
	TFT_Data((uint8_t)(end>>8));
	TFT_Data((uint8_t)end);
}

void SetHorizontalArea(uint16_t start, uint16_t end) {
	TFT_Command(CASET);
	TFT_Data((uint8_t)(start>>8));
	TFT_Data((uint8_t)start);
	TFT_Data((uint8_t)(end>>8));
	TFT_Data((uint8_t)end);
}

void SetColumn(uint16_t column) {
	SetVerticalArea(column, 0xFFFF);
}

void SetLine(uint16_t line) {
	SetHorizontalArea(line, 0xFFFF);
}

void SetMemoryAccess() {
	TFT_Command(MADCTL);

	//Horizontal Normal
	//TFT_Data(0xC4);

	//Vertical Normal
	TFT_Data(0x60);
}

void SetPixelFormat() {
	TFT_Command(PIXSET);
	TFT_Data(0x66);
}

void TurnDisplayON() {
	TFT_Command(DISPON);
}

void TurnDisplayOFF() {
	TFT_Command(DISPOFF);
}

void SoftwareReset() {
	TFT_Command(SWRESET);

	Delay(5);
}

void ReadDisplayStatus() {
	uint8_t data;

	TFT_Command(RDDST);

	TFT_Data(NOP);

	data = TFT_Read();
	data = TFT_Read();
	data = TFT_Read();
	data = TFT_Read();
}

void ExitSleepMode() {
	TFT_Command(SLPOUT);

	Delay(5);
}

void EnterSleepMode() {
	TFT_Command(SLPIN);

	Delay(5);
}

void SetPoint(Vector2D position) {
	SetColumn(position.x);
	SetLine(position.y);
}

void SetPixel(Vector2D position, Color color) {
	SetPoint(position);

	TFT_Command(RAMWR);
	TFT_Data(color.blue << 2);
	TFT_Data(color.green << 2);
	TFT_Data(color.red << 2);
}

void EnterVerticalScroll(uint16_t startScrollArea, uint16_t scrollAreaLength) {
	uint16_t endScrollArea = 320 - (startScrollArea + scrollAreaLength);

	TFT_Command(VSCRDEF);
	TFT_Data((uint8_t)(startScrollArea>>8));
	TFT_Data((uint8_t)startScrollArea);
	TFT_Data((uint8_t)(scrollAreaLength>>8));
	TFT_Data((uint8_t)scrollAreaLength);
	TFT_Data((uint8_t)(endScrollArea>>8));
	TFT_Data((uint8_t)endScrollArea);
}

void VerticalScrollStep(uint16_t stepLines) {
	TFT_Command(VSCRSADD);
	TFT_Data((stepLines>>8));
	TFT_Data(stepLines);
}

void ExitVerticalScroll() {
	TFT_Command(NORON);
}
