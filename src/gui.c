#include "gui.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "gpio.h"
#include "pinMaping.h"

//Buttons check variables
volatile uint32_t buttonDebounceTimer = 0;
uint8_t button0State;			//UP
uint8_t button1State;			//ENTER/MENU_3
uint8_t button2State;			//BACK/MENU_4
uint8_t button3State;			//V<=>/MENU_1
uint8_t button4State;			//SELECT/MENU_2
uint8_t button5State;			//RIGHT
uint8_t button6State;			//DOWN
uint8_t button7State;			//CENTER
uint8_t button8State;			//LEFT

//Global GUI structures
ButtonStruct analogBarButtons[5];
ButtonStruct digitalBarButtons[5];

uint32_t GetNumberAtIndex(uint32_t value, uint8_t index) {
	return (uint32_t)(value / pow(10, index)) % 10;
}

uint32_t SetNumberAtIndex(uint32_t value, uint8_t index, uint8_t newValue) {
	uint32_t num = 0;

	volatile uint32_t lowNum = value % (uint32_t)pow(10, index);		//Lower part of the number
	volatile uint32_t highNum =  (uint32_t)(value / pow(10, index)) / 10;

	num = ((highNum * 10) + newValue) * pow(10, index) + lowNum;

	return num;
}

uint8_t ReadButtonState(uint8_t button) {
	uint8_t value = 0x00;

	switch(button) {
		case 0x00:
			value = button0State;
			button0State = 0x00;
			break;
		case 0x01:
			value = button1State;
			button1State = 0x00;
			break;
		case 0x02:
			value = button2State;
			button2State = 0x00;
			break;
		case 0x03:
			value = button3State;
			button3State = 0x00;
			break;
		case 0x04:
			value = button4State;
			button4State = 0x00;
			break;
		case 0x05:
			value = button5State;
			button5State = 0x00;
			break;
		case 0x06:
			value = button6State;
			button6State = 0x00;
			break;
		case 0x07:
			value = button7State;
			button7State = 0x00;
			break;
		case 0x08:
			value = button8State;
			button8State = 0x00;
			break;
		default:
			value = 0x00;
			break;
	}

	return value;
}

void DrawButton(ButtonStruct button) {
	if(button.highlight == 0x01) {
		DrawTextBox(button.position, button.size, 2, button.text, strlen(button.text), 1, button.textColor, button.backgroundColor, Colors666.red);
	}
	else {
		DrawTextBox(button.position, button.size, 2, button.text, strlen(button.text), 1, button.textColor, button.backgroundColor, button.frameColor);
	}
}

uint8_t DrawDropDown(Vector2D position, uint8_t width, char *dropdownList[], uint8_t length, uint8_t selected) {
	//Drop Down Button List
	ButtonStruct dropdownButtons[length];

	//Init Drop Down Button List
	uint8_t i;
	for(i = 0; i < length; i++) {
		dropdownButtons[i].position.x = position.x;
		dropdownButtons[i].position.y = position.y;
		dropdownButtons[i].size.x = width;
		dropdownButtons[i].size.y = 18;

		dropdownButtons[i].textColor = Colors666.white;
		dropdownButtons[i].backgroundColor = Colors666.silver;
		dropdownButtons[i].frameColor = Colors666.white;

		dropdownButtons[i].id = 0;
		dropdownButtons[i].highlight = 0;
		dropdownButtons[i].pressed = 0;

		strcpy(dropdownButtons[i].text, dropdownList[i]);

		position.y += 16;
	}

	//Select, start, at current selection
	int8_t newSelected = selected;
	dropdownButtons[selected].highlight = 1;

	//Draw all drop down Menu Options/Buttons
	i = 0;
	for(i = 0; i < length; i++) {
		if(i != selected) {
			DrawButton(dropdownButtons[i]);
		}
	}
	//Draw selected last so to have correct frame color, draw on top
	DrawButton(dropdownButtons[selected]);

	while(1) {
		//Buttons register on "Button Press Up"
		if(ReadButtonState(BUTTON_DOWN) == 0x01) {
			//DOWN Button pressed: Select Next
			//De-Select last button
			dropdownButtons[newSelected].highlight = 0;
			DrawButton(dropdownButtons[newSelected]);

			//Select new button
			newSelected = (newSelected + 1);
			if(newSelected >= length) {
				newSelected = length - 1;
			}
			dropdownButtons[newSelected].highlight = 1;
			DrawButton(dropdownButtons[newSelected]);
		}
		else if(ReadButtonState(BUTTON_UP) == 0x01) {
			//UP Button pressed: Select Next
			//De-Select last button
			dropdownButtons[newSelected].highlight = 0;
			DrawButton(dropdownButtons[newSelected]);

			//Select new button
			newSelected = (newSelected - 1);
			if(newSelected < 0) {
				newSelected = 0;
			}
			dropdownButtons[newSelected].highlight = 1;
			DrawButton(dropdownButtons[newSelected]);
		}
		else if(ReadButtonState(BUTTON_CENTER) == 0x01) {
			//ENTER Button pressed: Exit with new selected
			return newSelected;
		}
		else if(ReadButtonState(BUTTON_BACK) == 0x01) {
			//EXIT Button pressed: Exit with no new selected
			return selected;
		}
	}
}

uint32_t DrawUpDown(Vector2D position, uint32_t minValue, uint32_t maxValue, uint32_t value) {
	Vector2D tPosition = position;
	Vector2D size;
	char text[10];

	//Draw Background Rect
	uint8_t numLen = (uint8_t)log10f(maxValue) + 1;
	size.x = numLen*8 + 4 + 4;				//Max number size x8 + boarder size + after boarder space
	size.y = 19;
	DrawRect(position, size, Colors666.silver, 2, Colors666.white);

	//Draw Initial Number
	switch(numLen) {
		case 1:
			sprintf(text, "%01lu", value);
			break;
		case 2:
			sprintf(text, "%02lu", value);
			break;
		case 3:
			sprintf(text, "%03lu", value);
			break;
		case 4:
			sprintf(text, "%04lu", value);
			break;
		case 5:
			sprintf(text, "%05lu", value);
			break;
		case 6:
			sprintf(text, "%06lu", value);
			break;
		case 7:
			sprintf(text, "%07lu", value);
			break;
		default:
			sprintf(text, "%01lu", value);
			break;
	}
	tPosition.x += 4;
	tPosition.y += 4;
	DrawASCIIText(tPosition, text, strlen(text), 1, Colors666.white, Colors666.silver);

	int8_t selectedNum = 0;
	//Draw Initial Selection
	int32_t tmp = GetNumberAtIndex(value, selectedNum);
	sprintf(text, "%lu", tmp);
	tPosition.x = position.x + 4 + 8*(numLen - (selectedNum + 1));
	DrawASCIIText(tPosition, text, strlen(text), 1, Colors666.red, Colors666.silver);

	while(1) {
		if(ReadButtonState(BUTTON_LEFT) == 0x01) {
			//First Clear previous selected number
			tmp = GetNumberAtIndex(value, selectedNum);
			sprintf(text, "%lu", tmp);
			tPosition.x = position.x + 4 + 8*(numLen - (selectedNum + 1));
			DrawASCIIText(tPosition, text, strlen(text), 1, Colors666.white, Colors666.silver);

			//Get new selected number to the left
			selectedNum += 1;
			if(selectedNum >= numLen) {
				selectedNum = numLen - 1;
			}

			//Draw new selected number
			tmp = GetNumberAtIndex(value, selectedNum);
			sprintf(text, "%lu", tmp);
			tPosition.x = position.x + 4 + 8*(numLen - (selectedNum + 1));
			DrawASCIIText(tPosition, text, strlen(text), 1, Colors666.red, Colors666.silver);
		}
		else if(ReadButtonState(BUTTON_RIGHT) == 0x01) {
			//First Clear previous selected number
			tmp = GetNumberAtIndex(value, selectedNum);
			sprintf(text, "%lu", tmp);
			tPosition.x = position.x + 4 + 8*(numLen - (selectedNum + 1));
			DrawASCIIText(tPosition, text, strlen(text), 1, Colors666.white, Colors666.silver);

			//Get new selected number to the right
			selectedNum -= 1;
			if(selectedNum < 0) {
				selectedNum = 0;
			}

			//Draw new selected number
			tmp = GetNumberAtIndex(value, selectedNum);
			sprintf(text, "%lu", tmp);
			tPosition.x = position.x + 4 + 8*(numLen - (selectedNum + 1));
			DrawASCIIText(tPosition, text, strlen(text), 1, Colors666.red, Colors666.silver);
		}
		else if(ReadButtonState(BUTTON_UP) == 0x01) {
			//Get new value for selected number
			tmp = GetNumberAtIndex(value, selectedNum) + 1;
			if((selectedNum + 1) == numLen) {
				if(tmp > GetNumberAtIndex(maxValue, selectedNum)) {
					tmp = GetNumberAtIndex(maxValue, selectedNum);
				}
			}
			else {
				if(tmp > 9) {
					tmp = 9;
				}
			}

			value = SetNumberAtIndex(value, selectedNum, tmp);
			if(value > maxValue) {
				value = maxValue;
			}
			else if(value < minValue) {
				value = minValue;
			}

			//Draw new selected number
			tmp = GetNumberAtIndex(value, selectedNum);
			sprintf(text, "%lu", tmp);
			tPosition.x = position.x + 4 + 8*(numLen - (selectedNum + 1));
			DrawASCIIText(tPosition, text, strlen(text), 1, Colors666.red, Colors666.silver);
		}
		else if(ReadButtonState(BUTTON_DOWN) == 0x01) {
			//Get new value for selected number
			tmp = GetNumberAtIndex(value, selectedNum) - 1;
			if(tmp < 0) {
				tmp = 0;
			}

			value = SetNumberAtIndex(value, selectedNum, tmp);
			if(value > maxValue) {
				value = maxValue;
			}
			else if(value < minValue) {
				value = minValue;
			}

			//Draw new selected number
			tmp = GetNumberAtIndex(value, selectedNum);
			sprintf(text, "%lu", tmp);
			tPosition.x = position.x + 4 + 8*(numLen - (selectedNum + 1));
			DrawASCIIText(tPosition, text, strlen(text), 1, Colors666.red, Colors666.silver);
		}
		else if(ReadButtonState(BUTTON_BACK) == 0x01 || ReadButtonState(BUTTON_CENTER) == 0x01) {
			//EXIT or CENTER Button pressed
			//Clear previous selected number
			tmp = GetNumberAtIndex(value, selectedNum);
			sprintf(text, "%lu", tmp);
			tPosition.x = position.x + 4 + 8*(numLen - (selectedNum + 1));
			DrawASCIIText(tPosition, text, strlen(text), 1, Colors666.white, Colors666.silver);

			return value;
		}
	}
}

void AnalogBarInit() {
	//Upper Status Bar
	//RX/TX Select Button
	analogBarButtons[0].position.x = 0;
	analogBarButtons[0].position.y = 16;
	analogBarButtons[0].size.x = 28;
	analogBarButtons[0].size.y = 18;

	analogBarButtons[0].textColor = Colors666.white;
	analogBarButtons[0].backgroundColor = Colors666.black;
	analogBarButtons[0].frameColor = Colors666.white;

	analogBarButtons[0].id = 0;
	analogBarButtons[0].highlight = 0;
	analogBarButtons[0].pressed = 0;

	char *radioModeList[3];
	radioModeList[0] = "OFF";
	radioModeList[1] = "RX";
	radioModeList[2] = "TX";
	strcpy(analogBarButtons[0].text, radioModeList[operationModeB]);

	//Modulation Select Button
	analogBarButtons[1].position.x = 26;
	analogBarButtons[1].position.y = 16;
	analogBarButtons[1].size.x = 44;
	analogBarButtons[1].size.y = 18;

	analogBarButtons[1].textColor = Colors666.white;
	analogBarButtons[1].backgroundColor = Colors666.black;
	analogBarButtons[1].frameColor = Colors666.white;

	analogBarButtons[1].id = 1;
	analogBarButtons[1].highlight = 0;
	analogBarButtons[1].pressed = 0;

	char *modulationModeList[9];
	modulationModeList[0] = "AM";
	modulationModeList[1] = "FM";
	modulationModeList[2] = "AFSK";
	modulationModeList[3] = "ASK";
	modulationModeList[4] = "FSK";
	modulationModeList[5] = "GMSK";
	modulationModeList[6] = "4FSK";
	modulationModeList[7] = "BPSK";
	modulationModeList[8] = "QPSK";
	strcpy(analogBarButtons[1].text, modulationModeList[modulationB - 1]);

	//AFC Select Button
	analogBarButtons[2].position.x = 68;
	analogBarButtons[2].position.y = 16;
	analogBarButtons[2].size.x = 36;
	analogBarButtons[2].size.y = 18;

	analogBarButtons[2].textColor = Colors666.white;
	analogBarButtons[2].backgroundColor = Colors666.black;
	analogBarButtons[2].frameColor = Colors666.white;

	analogBarButtons[2].id = 2;
	analogBarButtons[2].highlight = 0;
	analogBarButtons[2].pressed = 0;

	sprintf(analogBarButtons[2].text, "AFC");

	//AGC Select Button
	analogBarButtons[3].position.x = 102;
	analogBarButtons[3].position.y = 16;
	analogBarButtons[3].size.x = 74;
	analogBarButtons[3].size.y = 18;

	analogBarButtons[3].textColor = Colors666.white;
	analogBarButtons[3].backgroundColor = Colors666.black;
	analogBarButtons[3].frameColor = Colors666.white;

	analogBarButtons[3].id = 3;
	analogBarButtons[3].highlight = 0;
	analogBarButtons[3].pressed = 0;

	uint8_t agcSpeedToList[16] = {0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 4, 4, 4, 4, 5};
	char *agcSpeedList[6];
	agcSpeedList[0] = "AGC FAST";		//AGC Speed: 0 -> 79577Hz
	agcSpeedList[1] = "AGC M-FS";		//AGC Speed: 3 -> 18651Hz
	agcSpeedList[2] = "AGC MED";		//AGC Speed: 5 -> 4896Hz
	agcSpeedList[3] = "AGC M-SL";		//AGC Speed: 7 -> 1239Hz
	agcSpeedList[4] = "AGC SLOW";		//AGC Speed: 9 -> 311Hz
	agcSpeedList[5] = "AGC OFF";		//AGC Off: 15 -> Off
	strcpy(analogBarButtons[3].text, agcSpeedList[agcSpeedToList[agcSpeedB]]);

	//RX bandwidth Select Button
	analogBarButtons[4].position.x = 174;
	analogBarButtons[4].position.y = 16;
	analogBarButtons[4].size.x = 66;
	analogBarButtons[4].size.y = 18;

	analogBarButtons[4].textColor = Colors666.white;
	analogBarButtons[4].backgroundColor = Colors666.black;
	analogBarButtons[4].frameColor = Colors666.white;

	analogBarButtons[4].id = 4;
	analogBarButtons[4].highlight = 0;
	analogBarButtons[4].pressed = 0;

	uint16_t kilo = bandwidthB / 1000;
	uint16_t hundred = bandwidthB % 1000;
	if(kilo < 10) {
		sprintf(analogBarButtons[4].text, "BW % 4lu", bandwidthB);
	}
	else if(kilo < 100) {
		sprintf(analogBarButtons[4].text, "BW % 2uk%u", kilo, (hundred / 100));
	}
	else {
		sprintf(analogBarButtons[4].text, "BW % 3uk", kilo);
	}

	//Select Button
	uint8_t i;
	for(i = 0; i < 5; i++) {
		DrawButton(analogBarButtons[i]);
	}
}

void AnalogBarUpdate(uint8_t selected) {
	uint8_t i;
	for(i = 0; i < 5; i++) {
		if(selected == 0x00 || i != (selected - 1)) {
			//Skip Selected
			analogBarButtons[i].highlight = 0;
			DrawButton(analogBarButtons[i]);
		}
	}

	if(selected != 0x00) {
		//Draw Selected last so that it is drawn on top, the boarder
		analogBarButtons[selected - 1].highlight = 1;
		DrawButton(analogBarButtons[selected - 1]);
	}
}

uint8_t AnalogBarAction(uint8_t selected) {
	if(selected == 0x00) {
		return selected;
	}

	if(ReadButtonState(BUTTON_RIGHT) == 0x01) {
		//RIGHT Button pressed: Select Next to the Right
		//Select new button
		selected += 1;
		if(selected > 5) {
			selected = 5;
		}

		AnalogBarUpdate(selected);
	}
	else if(ReadButtonState(BUTTON_LEFT) == 0x01) {
		//LEFT Button pressed: Select Next to the LEFT
		//Select new button
		selected -= 1;
		if(selected < 1) {
			selected = 1;
		}

		AnalogBarUpdate(selected);
	}
	else if(ReadButtonState(BUTTON_CENTER) == 0x01) {
		//ENTER Button pressed: Open Sub-Menu
		Vector2D position;
		switch(selected - 1) {
			case 0x00:
				position.x = 0;
				position.y = 32;

				char *radioModeList[3];
				radioModeList[0] = "OFF";
				radioModeList[1] = "RX";
				radioModeList[2] = "TX";
				operationModeB = DrawDropDown(position, 36, radioModeList, 3, operationModeB);

				strcpy(analogBarButtons[0].text, radioModeList[operationModeB]);
				break;
			case 0x01:
				position.x = 26;
				position.y = 32;

				char *modulationModeList[9];
				modulationModeList[0] = "AM";
				modulationModeList[1] = "FM";
				modulationModeList[2] = "AFSK";
				modulationModeList[3] = "ASK";
				modulationModeList[4] = "FSK";
				modulationModeList[5] = "GMSK";
				modulationModeList[6] = "4FSK";
				modulationModeList[7] = "BPSK";
				modulationModeList[8] = "QPSK";
				modulationB = DrawDropDown(position, 44, modulationModeList, 9, (modulationB - 1)) + 1;

				strcpy(analogBarButtons[1].text, modulationModeList[modulationB - 1]);
				break;
			case 0x02:
//				AFCRangeUpDown();
				position.x = 68;
				position.y = 32;
				afcRangeB = DrawUpDown(position, 0, 100000, afcRangeB);

				BandwidthBarUpdate();
				AFCBarUpdate();
				break;
			case 0x03:
				position.x = 102;
				position.y = 32;

				uint8_t agcListToSpeed[6] = {0, 3, 5, 7, 9, 15};
				uint8_t agcSpeedToList[16] = {0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 4, 4, 4, 4, 5};
				char *agcSpeedList[6];
				agcSpeedList[0] = "AGC FAST";		//AGC Speed: 0 -> 79577Hz
				agcSpeedList[1] = "AGC M-FS";		//AGC Speed: 3 -> 18651Hz
				agcSpeedList[2] = "AGC MED";		//AGC Speed: 5 -> 4896Hz
				agcSpeedList[3] = "AGC M-SL";		//AGC Speed: 7 -> 1239Hz
				agcSpeedList[4] = "AGC SLOW";		//AGC Speed: 9 -> 311Hz
				agcSpeedList[5] = "AGC OFF";		//AGC Off: 15 -> Off
				uint8_t tmp = DrawDropDown(position, 74, agcSpeedList, 6, agcSpeedToList[agcSpeedB]);
				agcSpeedB = agcListToSpeed[tmp];

				strcpy(analogBarButtons[3].text, agcSpeedList[tmp]);
				break;
			case 0x04: {
//				BandwidthUpDown();
				position.x = 174;
				position.y = 32;
				bandwidthB = DrawUpDown(position, 0, 500000, bandwidthB);

				uint16_t kilo = bandwidthB / 1000;
				uint16_t hundred = bandwidthB % 1000;
				if(kilo < 10) {
					sprintf(analogBarButtons[4].text, "BW % 4lu", bandwidthB);
				}
				else if(kilo < 100) {
					sprintf(analogBarButtons[4].text, "BW % 2uk%u", kilo, (hundred / 100));
				}
				else {
					sprintf(analogBarButtons[4].text, "BW % 3uk", kilo);
				}

				BandwidthBarUpdate();
				AFCBarUpdate();
				break;
			}
		}

		//"Clear" Screen
		MainScreenDraw();
		AnalogBarUpdate(selected);
		DigitalBarUpdate(0x00);
	}
	else if(ReadButtonState(BUTTON_BACK) == 0x01) {
		//EXIT Button pressed: Exit with no new selected
		selected = 0x00;

		//"Clear" Screen
		MainScreenDraw();
		AnalogBarUpdate(selected);
		DigitalBarUpdate(0x00);
	}

	return selected;
}

void DigitalBarInit() {
	//Upper Status Bar
	//CW/Morse Select Button
	digitalBarButtons[0].position.x = 0;
	digitalBarButtons[0].position.y = 120;
	digitalBarButtons[0].size.x = 28;
	digitalBarButtons[0].size.y = 18;

	digitalBarButtons[0].textColor = Colors666.white;
	digitalBarButtons[0].backgroundColor = Colors666.black;
	digitalBarButtons[0].frameColor = Colors666.white;

	digitalBarButtons[0].id = 0;
	digitalBarButtons[0].highlight = 0;
	digitalBarButtons[0].pressed = 0;

	char *radioCWList[1];
	radioCWList[0] = "CW";
	strcpy(digitalBarButtons[0].text, radioCWList[morseSpeedB]);

	//Bitrate Select Button
	digitalBarButtons[1].position.x = 26;
	digitalBarButtons[1].position.y = 120;
	digitalBarButtons[1].size.x = 70;
	digitalBarButtons[1].size.y = 18;

	digitalBarButtons[1].textColor = Colors666.white;
	digitalBarButtons[1].backgroundColor = Colors666.black;
	digitalBarButtons[1].frameColor = Colors666.white;

	digitalBarButtons[1].id = 1;
	digitalBarButtons[1].highlight = 0;
	digitalBarButtons[1].pressed = 0;

	uint16_t kilo = txDatarateB / 1000;
	uint16_t hundred = txDatarateB % 1000;
	if(kilo < 10) {
		sprintf(digitalBarButtons[1].text, "RB % 4lu", txDatarateB);
	}
	else if(kilo < 100) {
		sprintf(digitalBarButtons[1].text, "RB % 2uk%u", kilo, (hundred / 100));
	}
	else {
		sprintf(digitalBarButtons[1].text, "RB % 3uk", kilo);
	}

	//Encoding Select Button
	digitalBarButtons[2].position.x = 94;
	digitalBarButtons[2].position.y = 120;
	digitalBarButtons[2].size.x = 48;
	digitalBarButtons[2].size.y = 18;

	digitalBarButtons[2].textColor = Colors666.white;
	digitalBarButtons[2].backgroundColor = Colors666.black;
	digitalBarButtons[2].frameColor = Colors666.white;

	digitalBarButtons[2].id = 2;
	digitalBarButtons[2].highlight = 0;
	digitalBarButtons[2].pressed = 0;

	char *radioEncodeList[7];
	radioEncodeList[0] = "NRZ";
	radioEncodeList[1] = "NRZ-S";
	radioEncodeList[2] = "NRZI";
	radioEncodeList[3] = "NRZI-S";
	radioEncodeList[4] = "FM1";
	radioEncodeList[5] = "FM0";
	radioEncodeList[6] = "MAN";
	strcpy(digitalBarButtons[2].text, radioEncodeList[encoderB]);

	//Framing Select Button
	digitalBarButtons[3].position.x = 140;
	digitalBarButtons[3].position.y = 120;
	digitalBarButtons[3].size.x = 48;
	digitalBarButtons[3].size.y = 18;

	digitalBarButtons[3].textColor = Colors666.white;
	digitalBarButtons[3].backgroundColor = Colors666.black;
	digitalBarButtons[3].frameColor = Colors666.white;

	digitalBarButtons[3].id = 3;
	digitalBarButtons[3].highlight = 0;
	digitalBarButtons[3].pressed = 0;

	char *radioFramingList[3];
	radioFramingList[0] = "RAW";
	radioFramingList[1] = "HDLC";
	radioFramingList[2] = "WMB";
	strcpy(digitalBarButtons[3].text, radioFramingList[framingB]);

	//CCITT/CRC bandwidth Select Button
	digitalBarButtons[4].position.x = 186;
	digitalBarButtons[4].position.y = 120;
	digitalBarButtons[4].size.x = 54;
	digitalBarButtons[4].size.y = 18;

	digitalBarButtons[4].textColor = Colors666.white;
	digitalBarButtons[4].backgroundColor = Colors666.black;
	digitalBarButtons[4].frameColor = Colors666.white;

	digitalBarButtons[4].id = 4;
	digitalBarButtons[4].highlight = 0;
	digitalBarButtons[4].pressed = 0;

	char *radioCRCList[3];
	radioCRCList[0] = "OFF";
	radioCRCList[1] = "CCITT";
	radioCRCList[2] = "CRC16";
	radioCRCList[3] = "DNP";
	radioCRCList[4] = "CRC32";
	strcpy(digitalBarButtons[4].text, radioCRCList[crcB]);

	//Select Button
	uint8_t i;
	for(i = 0; i < 5; i++) {
		DrawButton(digitalBarButtons[i]);
	}
}

void DigitalBarUpdate(uint8_t selected) {
	uint8_t i;
	for(i = 0; i < 5; i++) {
		if(selected == 0x00 || i != (selected - 1)) {
			//Skip Selected
			digitalBarButtons[i].highlight = 0;
			DrawButton(digitalBarButtons[i]);
		}
	}

	if(selected != 0x00) {
		//Draw Selected last so that it is drawn on top, the boarder
		digitalBarButtons[selected - 1].highlight = 1;
		DrawButton(digitalBarButtons[selected - 1]);
	}
}

uint8_t DigitalBarAction(uint8_t selected) {
	if(selected == 0x00) {
		return selected;
	}
	if(ReadButtonState(BUTTON_RIGHT) == 0x01) {
		//RIGHT Button pressed: Select Next to the right
		//Select new button
		selected += 1;
		if(selected > 5) {
			selected = 5;
		}

		DigitalBarUpdate(selected);
	}
	else if(ReadButtonState(BUTTON_LEFT) == 0x01) {
		//LEFT Button pressed: Select Next to the left
		//Select new button
		selected -= 1;
		if(selected < 1) {
			selected = 1;
		}

		DigitalBarUpdate(selected);
	}
	else if(ReadButtonState(BUTTON_CENTER) == 0x01) {
		//ENTER Button pressed: Open Sub-Menu
		Vector2D position;
		switch(selected - 1) {
			case 0x00:
				position.x = 0;
				position.y = 136;

				char *radioCWList[1];
				radioCWList[0] = "CW";
				morseSpeedA = DrawDropDown(position, 28, radioCWList, 1, morseSpeedA);

				strcpy(digitalBarButtons[0].text, radioCWList[morseSpeedA]);
				break;
			case 0x01:
				position.x = 26;
				position.y = 136;
				txDatarateB = DrawUpDown(position, 0, 500000, txDatarateB);

				uint16_t kilo = txDatarateB / 1000;
				uint16_t hundred = txDatarateB % 1000;
				if(kilo < 10) {
					sprintf(digitalBarButtons[1].text, "RB % 4lu", txDatarateB);
				}
				else if(kilo < 100) {
					sprintf(digitalBarButtons[1].text, "RB % 2uk%u", kilo, (hundred / 100));
				}
				else {
					sprintf(digitalBarButtons[1].text, "RB % 3uk", kilo);
				}
				break;
			case 0x02:
				position.x = 94;
				position.y = 136;

				char *radioEncodeList[7];
				radioEncodeList[0] = "NRZ";
				radioEncodeList[1] = "NRZ-S";
				radioEncodeList[2] = "NRZI";
				radioEncodeList[3] = "NRZI-S";
				radioEncodeList[4] = "FM1";
				radioEncodeList[5] = "FM0";
				radioEncodeList[6] = "MAN";
				encoderB = DrawDropDown(position, 48, radioEncodeList, 7, encoderB);

				strcpy(digitalBarButtons[2].text, radioEncodeList[encoderB]);
				break;
			case 0x03:
				position.x = 140;
				position.y = 136;

				char *radioFramingList[3];
				radioFramingList[0] = "RAW";
				radioFramingList[1] = "HDLC";
				radioFramingList[2] = "WMB";
				framingB = DrawDropDown(position, 48, radioFramingList, 3, framingB);

				strcpy(digitalBarButtons[3].text, radioFramingList[framingB]);
				break;
			case 0x04:
				position.x = 186;
				position.y = 136;

				char *radioCRCList[3];
				radioCRCList[0] = "OFF";
				radioCRCList[1] = "CCITT";
				radioCRCList[2] = "CRC16";
				radioCRCList[3] = "DNP";
				radioCRCList[4] = "CRC32";
				crcB = DrawDropDown(position, 54, radioCRCList, 5, crcB);

				strcpy(digitalBarButtons[4].text, radioCRCList[crcB]);
				break;
		}

		//"Clear" Screen
		MainScreenDraw();
		AnalogBarUpdate(0x00);
		DigitalBarUpdate(selected);
	}
	else if(ReadButtonState(BUTTON_BACK) == 0x01) {
		//EXIT Button pressed: Exit with no new selected
		selected = 0x00;

		//"Clear" Screen
		MainScreenDraw();
		AnalogBarUpdate(0x00);
		DigitalBarUpdate(selected);
	}

	return selected;
}

void MainScreenDraw() {
	Vector2D position;
	Vector2D size;

	char text[20];

	//Draw Screen Top Bar
	position.x = 48;
	position.y = 0;
	size.x = 50;
	size.y = 18;
	sprintf(text, "UHF");
	DrawTextBox(position, size, 2, text, strlen(text), 1, Colors666.white, Colors666.blue, Colors666.silver);
	position.x = 0;
	sprintf(text, "VHF");
	DrawTextBox(position, size, 2, text, strlen(text), 1, Colors666.white, Colors666.purple, Colors666.white);

	//Draw Screen Box
	position.x = 0;
	position.y = size.y - 2;
	size.x = 240;
	size.y = 272;
	DrawRect(position, size, Colors666.black, 2, Colors666.white);

	position.x = 0;
	position.y = 32;
	size.x = 240;
	size.y = 34;
	DrawRect(position, size, Colors666.black, 2, Colors666.white);

	//Center Frequency Indicator
	position.x = 8;
	position.y = 38;
	sprintf(text, "CF");
	DrawASCIIText(position, text, strlen(text), 2, Colors666.red, Colors666.black);
	CenterFrequencyUpdate();

	//Center Frequency Shift tracking bar
	BandwidthBarUpdate();
	AFCBarUpdate();

	//Draw AFC Bottom Bar
	position.x = 7;
	position.y = 88;
	size.x = 227;
	size.y = 3;
	DrawRect(position, size, Colors666.white, 0, Colors666.white);

	//RSSI Tracking Bar
	position.x = 0 + 4;
	position.y = 107;
	sprintf(text, "120");
	DrawASCIIText(position, text, strlen(text), 1, Colors666.white, Colors666.black);
	position.x = 60 - 3;
	sprintf(text, "90");
	DrawASCIIText(position, text, strlen(text), 1, Colors666.white, Colors666.black);
	position.x = 120 - 7;
	sprintf(text, "60");
	DrawASCIIText(position, text, strlen(text), 1, Colors666.white, Colors666.black);
	position.x = 180 - 1*8 - 3;
	sprintf(text, "30");
	DrawASCIIText(position, text, strlen(text), 1, Colors666.white, Colors666.black);
	position.x = 240 - 3 - 1*8;
	sprintf(text, "0");
	DrawASCIIText(position, text, strlen(text), 1, Colors666.white, Colors666.black);

	//RSSI Top white line/bar
	position.x = 7;
	position.y = 95;
	size.x = 227;
	size.y = 3;
	DrawRect(position, size, Colors666.white, 0, Colors666.white);

	//RSSI separator bars/lines
	position.x = 8;
	position.y = 98;
	uint8_t i;
	for(i = 0; i < 13; i++) {
		if((i % 3) == 0x00) {
			size.x = 3;
			size.y = 8;

			position.x -= 1;
		}
		else {
			size.x = 1;
			size.y = 6;
		}

		DrawRect(position, size, Colors666.white, 0, Colors666.white);

		position.x += 19;
	}

	//Bottom Main Menu/Screen delimiter bar
	position.x = 0;
	position.y = 122;
	size.x = 240;
	size.y = 2;
	DrawRect(position, size, Colors666.white, 0, Colors666.white);
}

void CenterFrequencyUpdate() {
	char text[20];
	Vector2D position;
	Vector2D size;

	//Clear/erase Center Frequency Label
	position.x = 74;
	position.y = 38;
	size.x = 164;
	size.y = 24;
	DrawRect(position, size, Colors666.black, 0, Colors666.white);

	//Re-Draw Center Frequency Label
	sprintf(text, "%09lu", centerFrequencyB);
	position.x = 240 - strlen(text)*8*2 - 6;	//Right align text
	position.y = 38;
	DrawASCIIText(position, text, strlen(text), 2, Colors666.white, Colors666.black);
}

uint16_t rssiBarLastSizeX = 0;
void RSSIIndicatorUpdate() {
	Vector2D position;
	Vector2D size;

	//Clear/erase old RSSI Bar
	position.x = 10;
	position.y = 98;
	size.x = rssiBarLastSizeX;
	size.y = 4;
	DrawRect(position, size, Colors666.black, 0, Colors666.white);

	//Updated new RSSI Bar
	float rssiBarPos = (120.0f + rssiTrackingB) / 120;
	if(rssiBarPos > 1.0f) {
		rssiBarPos = 1.0f;
	}
	else if(rssiBarPos < 0.0f) {
		rssiBarPos = 0.0f;
	}
	size.x = (uint16_t)(220 * rssiBarPos);
	size.y = 4;
	DrawRect(position, size, Colors666.orange, 0, Colors666.white);
	rssiBarLastSizeX = size.x;

	//Re-Draw RSSI separator bars/lines
	position.x = 8;
	position.y = 98;
	uint8_t i;
	for(i = 0; i < 13; i++) {
		if((i % 3) == 0x00) {
			size.x = 3;
			size.y = 8;

			position.x -= 1;
		}
		else {
			size.x = 1;
			size.y = 6;
		}

		DrawRect(position, size, Colors666.white, 0, Colors666.white);

		position.x += 19;
	}
}

void BandwidthBarUpdate() {
	char text[20];
	Vector2D position;
	Vector2D size;

	//Clear RF Track Bar Labels
	position.x = 4;
	position.y = 79 - 12;
	size.x = 232;
	size.y = 10;
	DrawRect(position, size, Colors666.black, 0, Colors666.white);

	uint8_t bandwidthLabel = bandwidthB/1000;
	//Re-Draw RF Track Bar Labels tracking bar
	position.x = 0 + 4;
	position.y = 79 - 12;
	sprintf(text, "%u", (bandwidthLabel >> 1));
	DrawASCIIText(position, text, strlen(text), 1, Colors666.white, Colors666.black);

	sprintf(text, "%u", (bandwidthLabel >> 2));
	uint8_t labelSize = strlen(text) * 8;
	position.x = 64 - (labelSize >> 1);
	DrawASCIIText(position, text, strlen(text), 1, Colors666.white, Colors666.black);

	sprintf(text, "0");
	labelSize = strlen(text) * 8;
	position.x = 120 - (labelSize >> 1);
	DrawASCIIText(position, text, strlen(text), 1, Colors666.white, Colors666.black);

	sprintf(text, "%u", (bandwidthLabel >> 2));
	labelSize = strlen(text) * 8;
	position.x = 176 - (labelSize >> 1);
	DrawASCIIText(position, text, strlen(text), 1, Colors666.white, Colors666.black);

	sprintf(text, "%u", (bandwidthLabel >> 1));
	labelSize = strlen(text) * 8;
	position.x = 240 - 3 - labelSize;
	DrawASCIIText(position, text, strlen(text), 1, Colors666.white, Colors666.black);
}

void AFCBarUpdate() {
	Vector2D position;
	Vector2D size;

	//Clear/erase old AFC Range Bar
	position.x = 10;
	position.y = 79;
	size.x = 220;
	size.y = 9;
	DrawRect(position, size, Colors666.black, 0, Colors666.white);

	//Re-Draw AFC Range Bar
	float afcBarSize = ((2.0f * afcRangeB) / bandwidthB);
	if(afcBarSize > 1.0f) {
		afcBarSize = 1.0f;
	}
	else if(afcBarSize < 0.0f) {
		afcBarSize = 0.0f;
	}
	size.x = (uint16_t)(220 * afcBarSize);
	position.x = 120 - (size.x >> 1);
	position.y = 84;
	size.y = 4;
	DrawRect(position, size, (Color){0x3F, 0x00, 0x00}, 0, Colors666.white); 		//AFC Range indicator

	//Re-Draw Frequency tracking bar separator bars/lines
	position.x = 6;
	position.y = 80;
	uint8_t i;
	for(i = 0; i < 21; i++) {
		if((i % 5) == 0x00) {
			size.x = 3;
			size.y = 8;

			position.y = 80;
			position.x += 1;
		}
		else {
			size.x = 1;
			size.y = 6;

			position.y = 82;
		}

		DrawRect(position, size, Colors666.white, 0, Colors666.white);

		position.x += 11;
	}
}

uint16_t freqTrackLastPosX = 78;
void FrequencyTrackingUpdate() {
	Vector2D position;
	Vector2D size;

	//Clear/erase old Frequency tracking bar
	position.x = freqTrackLastPosX;
	position.y = 79;
	size.x = 3;
	size.y = 9;
	DrawRect(position, size, Colors666.black, 0, Colors666.white); 	//Frequency shift indicator bar

	//Re-Draw AFC Range Bar
	float afcBarSize = ((2.0f * afcRangeB) / bandwidthB);
	if(afcBarSize > 1.0f) {
		afcBarSize = 1.0f;
	}
	else if(afcBarSize < 0.0f) {
		afcBarSize = 0.0f;
	}
	size.x = (uint16_t)(220 * afcBarSize);
	position.x = 120 - (size.x >> 1);
	position.y = 84;
	size.y = 4;
	DrawRect(position, size, (Color){0x3F, 0x00, 0x00}, 0, Colors666.white); 		//AFC Range indicator

	//Re-Draw Frequency tracking bar separator bars/lines
	position.x = 6;
	position.y = 80;
	uint8_t i;
	for(i = 0; i < 21; i++) {
		if((i % 5) == 0x00) {
			size.x = 3;
			size.y = 8;

			position.y = 80;
			position.x += 1;
		}
		else {
			size.x = 1;
			size.y = 6;

			position.y = 82;
		}

		DrawRect(position, size, Colors666.white, 0, Colors666.white);

		position.x += 11;
	}

	//Update new Frequency tracking bar
	float dFreqBarPos = 0.5f + ((float)rfFrequencyTrackingB / bandwidthB);
	if(dFreqBarPos > 1.0f) {
		dFreqBarPos = 1.0f;
	}
	else if(dFreqBarPos < 0.0f) {
		dFreqBarPos = 0.0f;
	}

	position.x = 10 + (uint16_t)(224 * dFreqBarPos) - 2;
	position.y = 79;
	size.x = 3;
	size.y = 9;
	DrawRect(position, size, Colors666.lime, 0, Colors666.white); 	//Frequency shift indicator bar
	freqTrackLastPosX = position.x;
}

void CommandBarInit() {
	Vector2D position;
	Vector2D size;
	char text[10];

	//Draw Bottom Command Bar
	position.x = 0;
	position.y = 286;
	size.x = 180;
	size.y = 18;
	DrawRect(position, size, Colors666.black, 2, Colors666.white);
	position.x = 178;
	size.x = 62;
	DrawRect(position, size, Colors666.black, 2, Colors666.white);

	position.y = 289;
	position.x = 4;
	sprintf(text, "CMD:");
	DrawASCIIText(position, text, strlen(text), 1, Colors666.white, Colors666.black);
	position.x = 36;
	sprintf(text, "NA");
	DrawASCIIText(position, text, strlen(text), 1, Colors666.white, Colors666.black);
	position.x = 182;
	sprintf(text, "ANS:");
	DrawASCIIText(position, text, strlen(text), 1, Colors666.white, Colors666.black);
	position.x = 214;
	sprintf(text, "NA");
	DrawASCIIText(position, text, strlen(text), 1, Colors666.white, Colors666.black);
}

void CommandBarUpdateCmd(char* cmd) {
	Vector2D position;
	position.x = 36;
	position.y = 289;
	DrawASCIIText(position, cmd, strlen(cmd), 1, Colors666.white, Colors666.black);
}

void CommandBarUpdateCmdReturn(uint8_t cmdReturnError) {
	Vector2D position;
	char text[10];

	position.x = 214;
	position.y = 289;
	if(cmdReturnError == 0x00) {
		//Command return OK
		sprintf(text, "OK ");
		DrawASCIIText(position, text, strlen(text), 1, Colors666.green, Colors666.black);
	}
	else {
		//Command return ERROR
		sprintf(text, "ERR");
		DrawASCIIText(position, text, strlen(text), 1, Colors666.red, Colors666.black);
	}
}

void BottomButtonLabelsInit() {
	Vector2D position;
	Vector2D size;
	char text[10];

	//Draw Bottom Menu Row
	size.x = 62;
	size.y = 18;
	position.y = 302;
	position.x = 0;
	DrawRect(position, size, Colors666.silver, 2, Colors666.white);
	position.x = 58;
	DrawRect(position, size, Colors666.silver, 2, Colors666.white);
	position.x = 118;
	DrawRect(position, size, Colors666.silver, 2, Colors666.white);
	position.x = 178;
	DrawRect(position, size, Colors666.silver, 2, Colors666.white);
	position.y = 305;
	position.x = 11;
	sprintf(text, "V<=>U");
	DrawASCIIText(position, text, strlen(text), 1, Colors666.white, Colors666.silver);
	position.x = 74;
	sprintf(text, "FREQ");
	DrawASCIIText(position, text, strlen(text), 1, Colors666.white, Colors666.silver);
	position.x = 129;
	sprintf(text, "ENTER");
	DrawASCIIText(position, text, strlen(text), 1, Colors666.white, Colors666.silver);
	position.x = 194;
	sprintf(text, "BACK");
	DrawASCIIText(position, text, strlen(text), 1, Colors666.white, Colors666.silver);
}

void CenterFrequencyUpDown() {
	char text[20];
	Vector2D position;

	int32_t value;
	int8_t selectedNum = 0;

	//Draw Initial Selection
	value = GetNumberAtIndex(centerFrequencyB, selectedNum);
	sprintf(text, "%lu", value);
	position.x = 240 - 6 - 8*2*(selectedNum + 1);
	position.y = 38;
	DrawASCIIText(position, text, strlen(text), 2, Colors666.red, Colors666.black);

	while(1) {
		if(ReadButtonState(BUTTON_LEFT) == 0x01) {
			//First Clear previous selected number
			value = GetNumberAtIndex(centerFrequencyB, selectedNum);
			sprintf(text, "%lu", value);
			position.x = 240 - 6 - 8*2*(selectedNum + 1);
			position.y = 38;
			DrawASCIIText(position, text, strlen(text), 2, Colors666.white, Colors666.black);

			//Get new selected number to the left
			selectedNum += 1;
			if(selectedNum > 8) {
				selectedNum = 8;
			}

			//Draw new selected number
			value = GetNumberAtIndex(centerFrequencyB, selectedNum);
			sprintf(text, "%lu", value);
			position.x = 240 - 6 - 8*2*(selectedNum + 1);
			position.y = 38;
			DrawASCIIText(position, text, strlen(text), 2, Colors666.red, Colors666.black);
		}
		else if(ReadButtonState(BUTTON_RIGHT) == 0x01) {
			//First Clear previous selected number
			value = GetNumberAtIndex(centerFrequencyB, selectedNum);
			sprintf(text, "%lu", value);
			position.x = 240 - 6 - 8*2*(selectedNum + 1);
			position.y = 38;
			DrawASCIIText(position, text, strlen(text), 2, Colors666.white, Colors666.black);

			//Get new selected number to the right
			selectedNum -= 1;
			if(selectedNum < 0) {
				selectedNum = 0;
			}

			//Draw new selected number
			value = GetNumberAtIndex(centerFrequencyB, selectedNum);
			sprintf(text, "%lu", value);
			position.x = 240 - 6 - 8*2*(selectedNum + 1);
			position.y = 38;
			DrawASCIIText(position, text, strlen(text), 2, Colors666.red, Colors666.black);
		}
		else if(ReadButtonState(BUTTON_UP) == 0x01) {
			//Get new value for selected number
			value += 1;
			if(value > 9) {
				value = 9;
			}

			centerFrequencyB = SetNumberAtIndex(centerFrequencyB, selectedNum, value);

			//Draw new selected number
			sprintf(text, "%lu", value);
			position.x = 240 - 6 - 8*2*(selectedNum + 1);
			position.y = 38;
			DrawASCIIText(position, text, strlen(text), 2, Colors666.red, Colors666.black);
		}
		else if(ReadButtonState(BUTTON_DOWN) == 0x01) {
			//Get new value for selected number
			value -= 1;
			if(value < 0) {
				value = 0;
			}

			centerFrequencyB = SetNumberAtIndex(centerFrequencyB, selectedNum, value);

			//Draw new selected number
			sprintf(text, "%lu", value);
			position.x = 240 - 6 - 8*2*(selectedNum + 1);
			position.y = 38;
			DrawASCIIText(position, text, strlen(text), 2, Colors666.red, Colors666.black);
		}
		else if(ReadButtonState(BUTTON_BACK) == 0x01 || ReadButtonState(BUTTON_CENTER) == 0x01) {
			//EXIT or CENTER Button pressed
			//Clear previous selected number
			value = GetNumberAtIndex(centerFrequencyB, selectedNum);
			sprintf(text, "%lu", value);
			position.x = 240 - 6 - 8*2*(selectedNum + 1);
			position.y = 38;
			DrawASCIIText(position, text, strlen(text), 2, Colors666.white, Colors666.black);

			return;
		}
	}
}

/**
  * @brief	This function is the Handler for GPIO0
  * @param	None
  * @return	None
  */
void EXTI0_IRQHandler(void) {
	if(LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_0) == 0x01 && LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_0) == 0x01) {
		//LL_GPIO_PIN_0 Interrupt triggered
		if((buttonDebounceTimer + BUTTON_DEBOUNCE_TIMEOUT) < GetSysTick()) {
			button0State = 0x01;

			buttonDebounceTimer = GetSysTick();
		}

		//Clear Interrupt Flag
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);
	}
}

/**
  * @brief	This function is the Handler for GPIO1
  * @param	None
  * @return	None
  */
void EXTI1_IRQHandler(void) {
	if(LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_1) == 0x01 && LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_1) == 0x01) {
		//LL_GPIO_PIN_1 Interrupt triggered
		if((buttonDebounceTimer + BUTTON_DEBOUNCE_TIMEOUT) < GetSysTick()) {
			button1State = 0x01;

			buttonDebounceTimer = GetSysTick();
		}

		//Clear Interrupt Flag
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_1);
	}
}

/**
  * @brief	This function is the Handler for GPIO2
  * @param	None
  * @return	None
  */
void EXTI2_IRQHandler(void) {
	if(LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_2) == 0x01 && LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_2) == 0x01) {
		//LL_GPIO_PIN_2 Interrupt triggered
		if((buttonDebounceTimer + BUTTON_DEBOUNCE_TIMEOUT) < GetSysTick()) {
			button2State = 0x01;

			buttonDebounceTimer = GetSysTick();
		}

		//Clear Interrupt Flag
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_2);
	}
}

/**
  * @brief	This function is the Handler for GPIO3
  * @param	None
  * @return	None
  */
void EXTI3_IRQHandler(void) {
	if(LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_3) == 0x01 && LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_3) == 0x01) {
		//LL_GPIO_PIN_3 Interrupt triggered
		if((buttonDebounceTimer + BUTTON_DEBOUNCE_TIMEOUT) < GetSysTick()) {
			button3State = 0x01;

			buttonDebounceTimer = GetSysTick();
		}

		//Clear Interrupt Flag
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_3);
	}
}

/**
  * @brief	This function is the Handler for GPIO4
  * @param	None
  * @return	None
  */
void EXTI4_IRQHandler(void) {
	if(LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_4) == 0x01 && LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_4) == 0x01) {
		//LL_GPIO_PIN_4 Interrupt triggered
		if((buttonDebounceTimer + BUTTON_DEBOUNCE_TIMEOUT) < GetSysTick()) {
			button4State = 0x01;

			buttonDebounceTimer = GetSysTick();
		}

		//Clear Interrupt Flag
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_4);
	}
}

/**
  * @brief	This function is the Handler for GPIO5 to GPIO9
  * @param	None
  * @return	None
  */
void EXTI9_5_IRQHandler(void) {
	if(LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_5) == 0x01 && LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_5) == 0x01) {
		//LL_GPIO_PIN_5 Interrupt triggered
		if((buttonDebounceTimer + BUTTON_DEBOUNCE_TIMEOUT) < GetSysTick()) {
			button5State = 0x01;

			buttonDebounceTimer = GetSysTick();
		}

		//Clear Interrupt Flag
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_5);
	}

	if(LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_6) == 0x01 && LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_6) == 0x01) {
		//LL_GPIO_PIN_6 Interrupt triggered
		if((buttonDebounceTimer + BUTTON_DEBOUNCE_TIMEOUT) < GetSysTick()) {
			button6State = 0x01;

			buttonDebounceTimer = GetSysTick();
		}

		//Clear Interrupt Flag
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_6);
	}

	if(LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_7) == 0x01 && LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_7) == 0x01) {
		//LL_GPIO_PIN_7 Interrupt triggered
		if((buttonDebounceTimer + BUTTON_DEBOUNCE_TIMEOUT) < GetSysTick()) {
			button7State = 0x01;

			buttonDebounceTimer = GetSysTick();
		}

		//Clear Interrupt Flag
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_7);
	}
}

/**
  * @brief	This function is the Handler for GPIO10 to GPIO15
  * @param	None
  * @return	None
  */
void EXTI15_10_IRQHandler(void) {
	if(LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_11) == 0x01 && LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_11) == 0x01) {
		//LL_GPIO_PIN_11 Interrupt triggered
		if((buttonDebounceTimer + BUTTON_DEBOUNCE_TIMEOUT) < GetSysTick()) {
			button8State = 0x01;

			buttonDebounceTimer = GetSysTick();
		}

		//Clear Interrupt Flag
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_11);
	}
}
