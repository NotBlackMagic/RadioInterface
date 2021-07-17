#ifndef GUI_H_
#define GUI_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "tft_gui.h"

#include "ax25.h"

#include "radioConfigs.h"

#define BUTTON_DEBOUNCE_TIMEOUT				250

#define BUTTON_SWITCH						3
#define BUTTON_FREQ							4
#define BUTTON_MENU							1
#define BUTTON_BACK							2
#define BUTTON_UP							0
#define BUTTON_DOWN							6
#define BUTTON_LEFT							8
#define BUTTON_RIGHT						5
#define BUTTON_CENTER						7

typedef struct {
	//Button Status
	uint8_t id;
	uint8_t highlight;
	uint8_t pressed;

	//Basic Characteristics
	Vector2D position;
	Vector2D size;
	char text[10];

	//Colors
	Color textColor;
	Color backgroundColor;
	Color frameColor;
} ButtonStruct;

typedef enum {
	MainWindow_None,
	MainWindow_Msg,
	MainWindow_Spectrum,
	MainWindow_Waterfall
} MainWindowScreens;

extern volatile uint8_t selectedRadio;
extern MainWindowScreens mainWindowSelected;

uint8_t ReadButtonState(uint8_t button);
void DrawButton(ButtonStruct button);
uint8_t DrawDropDown(Vector2D position, uint8_t width, char *dropdownList[10], uint8_t length, uint8_t selected);
uint32_t DrawUpDown(Vector2D position, uint32_t minValue, uint32_t maxValue, uint32_t value);

void MainScreenDraw();
void CenterFrequencyUpdate();
void BandwidthBarUpdate();
void AFCBarUpdate();
void FrequencyTrackingUpdate();
void RSSIIndicatorUpdate();

void BottomButtonLabelsInit();

void AnalogBarInit();
void AnalogBarUpdate(uint8_t selected);
uint8_t AnalogBarAction(uint8_t selected);

void DigitalBarInit();
void DigitalBarUpdate(uint8_t selected);
uint8_t DigitalBarAction(uint8_t selected);

void MessageWindowInit();
void MessageWindowUpdate(AX25Struct message);

void SpectrumWindowInit();
void SpectrumWindowUpdate(uint8_t spectrum[], uint16_t length);

void WaterfallWindowInit();
void WaterfallWindowUpdate(uint8_t spectrum[], uint16_t length);

void CommandBarInit();
void CommandBarUpdateCmd(char* cmd);
void CommandBarUpdateCmdReturn(uint8_t cmdReturnError);

void CenterFrequencyUpDown();
void AFCRangeUpDown();
void BandwidthUpDown();

#ifdef __cplusplus
}
#endif

#endif /* GUI_H_ */
