#include "gpio.h"
#include "rcc.h"
#include "uart.h"

#include "tft_commands.h"
#include "tft_interface.h"
#include "tft_gui.h"

#include "3DRenderer.h"
#include "gui.h"

#include "pinMaping.h"

#include "stdio.h"

void RadioConfigInit();

int main(void) {
	//Configure the system clock
	SystemClockInit();
	SystemTickInit();

	//Initialize all configured peripherals
	GPIOInit();
	UART1Init(115200);

	//Init TFT Screen
	TFT_Init();
	SoftwareReset();
	TurnDisplayON();
	ExitSleepMode();
	SetMemoryAccess();
	SetPixelFormat();

	Delay(100);

	SetBackgroundColor(Colors666.black);

	//Init/get initial radio configurations
	RadioConfigInit();

	//Init Main Screen
	MainScreenDraw();

	//Upper Upper Status/Button Bar (Analog): RX/TX; Modulation; AGC; RX bandwidth
	AnalogBarInit();

	//Upper Lower Status/Button Bar (Digital): CW, Bitrate, Encoding, Framing, CRC
	DigitalBarInit();

	//Draw Command Status Bar
	CommandBarInit();

	//Draw Bottom Menu Row
	BottomButtonLabelsInit();

	uint8_t analogBarSelected = 0;
	uint8_t digitalBarSelected = 0;

	uint32_t timestamp = GetSysTick();
	uint8_t requestDataIndex = 0;

	uint8_t rxData[512];
	uint16_t rxLength;
	uint8_t cmdError;
	uint8_t txData[512];
	uint16_t txLength;
	while(1) {
		//UART Communication Check
		if(UART1Read(rxData, &rxLength) == 0x01) {
			cmdError = CATInterfaceHandler(rxData, rxLength, txData, &txLength);
//			UART1Write(txData, txLength);
			CommandBarUpdateCmdReturn(cmdError);
		}

		if(ReadButtonState(BUTTON_DOWN) == 0x01) {
			analogBarSelected = 0x00;
			digitalBarSelected = 0x01;

			AnalogBarUpdate(0x00);
			DigitalBarUpdate(0x01);
		}
		else if(ReadButtonState(BUTTON_UP) == 0x01) {
			analogBarSelected = 0x01;
			digitalBarSelected = 0x00;

			AnalogBarUpdate(0x01);
			DigitalBarUpdate(0x00);
		}

		if(ReadButtonState(BUTTON_FREQ) == 0x01) {
			analogBarSelected = 0x00;
			digitalBarSelected = 0x00;

			AnalogBarUpdate(0x00);
			DigitalBarUpdate(0x00);

			CenterFrequencyUpDown();
		}

		if(analogBarSelected != 0x00) {
			analogBarSelected = AnalogBarAction(analogBarSelected);
		}
		else if(digitalBarSelected != 0x00) {
			digitalBarSelected = DigitalBarAction(digitalBarSelected);
		}

		if((timestamp + 500) < GetSysTick()) {
			//Update GUI
			if(requestDataIndex == 0x00) {
				RSSIIndicatorUpdate();

				txLength = sprintf(txData, "RM10;");		//Request RSSI Tracking Data
				UART1Write(txData, txLength);

				CommandBarUpdateCmd(txData);

				requestDataIndex = 0x01;
			}
			else if(requestDataIndex == 0x01) {
				FrequencyTrackingUpdate();

				txLength = sprintf(txData, "RM11;");		//Request RF Frequency Tracking Data
				UART1Write(txData, txLength);

				CommandBarUpdateCmd(txData);

				requestDataIndex = 0x00;
			}

			timestamp = GetSysTick();
		}
	}
}

void RadioConfigInit() {
	uint8_t rxData[512];
	uint16_t rxLength = 0;
	uint8_t cmdResponse = 0x01;
	uint8_t txData[512];
	uint16_t txLength = 0;

	//Init configurations for Radio A (UHF)

	//Init configurations for Radio B (VHF)
	uint8_t config = 0;
	while(config < 0x12) {
		//UART Communication Check
		if(UART1Read(rxData, &rxLength) == 0x01) {
			uint8_t cmdError = CATInterfaceHandler(rxData, rxLength, txData, &txLength);

			cmdResponse = 1;
		}

		if(cmdResponse == 0x01) {
			//Got answer, request next
			switch(config) {
				case 0x00:
					//Get configuration: operationModeB
					txLength = sprintf(txData, "FT1;");
					break;
				case 0x01:
					//Get configuration: operationModeB
					txLength = sprintf(txData, "FR1;");
					break;
				case 0x02:
					//Get configuration: centerFrequencyB
					txLength = sprintf(txData, "FB;");
					break;
				case 0x03:
					//Get configuration: modulationB
					txLength = sprintf(txData, "MD1;");
					break;
				case 0x04:
					//Get configuration: ifFrequncyB
					txLength = sprintf(txData, "IS1;");
					break;
				case 0x05:
					//Get configuration: bandwidthB
					txLength = sprintf(txData, "SH1;");
					break;
				case 0x06:
					//Get configuration: rxDatarateB
					txLength = sprintf(txData, "DR1;");
					break;
				case 0x07:
					//Get configuration: txDatarateB
					txLength = sprintf(txData, "DT1;");
					break;
				case 0x08:
					//Get configuration: afcRangeB
					txLength = sprintf(txData, "AF1;");
					break;
				case 0x09:
					//Get configuration: outputPowerB
					txLength = sprintf(txData, "PC1;");
					break;
				case 0x0A:
					//Get configuration: agcSpeedB
					txLength = sprintf(txData, "GT1;");
					break;
				case 0x0B:
					//Get configuration: frequencyDeviationB
//					txLength = sprintf(txData, "SH1;");
					frequencyDeviationB = 4800;
					txLength = 0;
					break;
				case 0x0C:
					//Get configuration: afskSpaceB
//					txLength = sprintf(txData, "SH1;");
					afskSpaceB = 2200;
					txLength = 0;
					break;
				case 0x0D:
					//Get configuration: afskMarkB
//					txLength = sprintf(txData, "SH1;");
					afskMarkB = 1200;
					txLength = 0;
					break;
				case 0x0E:
					//Get configuration: afskDetectorBWB
//					txLength = sprintf(txData, "SH1;");
					afskDetectorBWB = 4800;
					txLength = 0;
					break;
				case 0x0F:
					//Get configuration: morseSpeedB
//					txLength = sprintf(txData, "SH1;");
					morseSpeedB = 0;
					txLength = 0;
					break;
				case 0x10:
					//Get configuration: encoderB
					txLength = sprintf(txData, "EM1;");
					break;
				case 0x11:
					//Get configuration: framingB
					txLength = sprintf(txData, "FM1;");
					break;
				case 0x12:
					//Get configuration: crcB
					txLength = sprintf(txData, "CT1;");
					break;
				default:
					txLength = 0;
					break;
			}

			config += 1;

			if(txLength > 0) {
				UART1Write(txData, txLength);

				cmdResponse = 0x00;
			}
		}
	}
}
