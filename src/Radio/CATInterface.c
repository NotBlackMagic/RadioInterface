#include "CATInterface.h"

uint8_t CATASCIIToNumber(uint8_t* ascii, uint8_t asciiLength, int32_t* value);

//CAT Command Handlers
uint8_t CATCommandAFCControl(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandCRC(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandEncoding(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandDatarateRX(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandDatarateTX(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandCenterFequencyA(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandCenterFequencyB(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandFraming(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandFunctionRX(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandFunctionTX(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandAGCSpeed(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandIFFrequency(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandModulation(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandTXPower(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandBandwidth(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandReadMeter(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandRSSI(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);
uint8_t CATCommandDeviation(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength);

/**
  * @brief	This function handles all incoming data/commands
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * CAT Command Example: Set: FA145895000; Read: FA; Return: FA145895000;
  */
uint8_t CATInterfaceHandler(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	if(data[0] == 'A' && data[1] == 'F') {
		//AFC Control
		return CATCommandAFCControl(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'C' && data[1] == 'T') {
		//CRC/CCITT Control
		return CATCommandCRC(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'D' && data[1] == 'A') {
		//Screen Brightness setting
	}
	else if(data[0] == 'E' && data[1] == 'M') {
		//Bit Encoding Mode
		return CATCommandEncoding(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'E' && data[1] == 'X') {
		//Extended Menu
	}
	else if(data[0] == 'D' && data[1] == 'R') {
		//Datarate RX
		return CATCommandDatarateRX(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'D' && data[1] == 'T') {
		//Datarate TX
		return CATCommandDatarateTX(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'F' && data[1] == 'A') {
		//Center Frequency of Radio A
		return CATCommandCenterFequencyA(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'F' && data[1] == 'B') {
		//Center Frequency of Radio B
		return CATCommandCenterFequencyB(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'F' && data[1] == 'M') {
		//Framing Mode
		return CATCommandFraming(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'F' && data[1] == 'R') {
		//Function RX (ON or OFF)
		return CATCommandFunctionRX(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'F' && data[1] == 'T') {
		//Function TX (ON or OFF)
		return CATCommandFunctionTX(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'G' && data[1] == 'T') {
		//AGC Speed setting
		return CATCommandAGCSpeed(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'I' && data[1] == 'S') {
		//IF Frequency setting
		return CATCommandIFFrequency(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'K' && data[1] == 'S') {
		//CW/Morse Key Speed
	}
	else if(data[0] == 'M' && data[1] == 'D') {
		//Operating Mode/Modulation
		return CATCommandModulation(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'P' && data[1] == 'C') {
		//TX Output Power
		return CATCommandTXPower(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'R' && data[1] == 'G') {
		//RF Gain, LNA/AGC Gain
	}
	else if(data[0] == 'R' && data[1] == 'M') {
		//Read Meter/Tracking Value
		return CATCommandReadMeter(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'S' && data[1] == 'H') {
		//RX Bandwidth
		return CATCommandBandwidth(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'S' && data[1] == 'M') {
		//RSSI Reading
		return CATCommandRSSI(data, dataLength, rData, rDataLength);
	}
	else if(data[0] == 'T' && data[1] == 'C') {
		//TNC Mode
	}
	else if(data[0] == '?' && data[1] == ';') {
		//Command return ERROR
		return 1;
	}
	else if(data[0] == 'O' && data[1] == 'K' && data[2] == ';') {
		//Command return OK
		return 0;
	}
	else {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	return 0;
}

/**
  * @brief	This function handles the AFC Range CAT Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: AFC1125000; Read: AFC1; Return: AFC1125000;
  */
uint8_t CATCommandAFCControl(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is Return Value, same syntax as Write command
	if(data[9] == ';') {
		//Return Value from Read Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 6, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_A) {
			radioAConfig.afcRange = value;
		}
		else if(radio == RADIO_B) {
			radioBConfig.afcRange = value;
		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the CRC Mode Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: CT10; Read: CT1; Return: CT10;
  */
uint8_t CATCommandCRC(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is Return Value, same syntax as Write command
	if(data[4] == ';') {
		//Return Value from Read Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 1, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_A) {
			radioAConfig.crc = value;
		}
		else if(radio == RADIO_B) {
			radioBConfig.crc = value;
		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Encoding Mode CAT Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: EM14; Read: EM1; Return: EM14;
  */
uint8_t CATCommandEncoding(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is Return Value, same syntax as Write command
	if(data[4] == ';') {
		//Return Value from Read Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 1, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_A) {
			radioAConfig.encoder = value;
		}
		else if(radio == RADIO_B) {
			radioBConfig.encoder = value;
		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Datarate RX CAT Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: DR1001200; Read: DR1; Return: DR1001200;
  */
uint8_t CATCommandDatarateRX(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is Return Value, same syntax as Write command
	if(data[9] == ';') {
		//Return Value from Read Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 6, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_A) {
			radioAConfig.rxDatarate = value;
		}
		else if(radio == RADIO_B) {
			radioBConfig.rxDatarate = value;
		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Datarate TX CAT Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: DT0250000; Read: DT0; Return: DT0250000;
  */
uint8_t CATCommandDatarateTX(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is Return Value, same syntax as Write command
	if(data[9] == ';') {
		//Return Value from Read Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 6, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_A) {
			radioAConfig.txDatarate = value;
		}
		else if(radio == RADIO_B) {
			radioBConfig.txDatarate = value;
		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Center Frequency A CAT Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: FA145895000; Read: FA; Return: FA145895000;
  */
uint8_t CATCommandCenterFequencyA(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	//Check if is Return Value, same syntax as Write command
	if(data[11] == ';') {
		//Return Value from Read Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[2], 9, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		radioAConfig.centerFrequency = value;
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Center Frequency B CAT Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: FB145895000; Read: FB; Return: FB145895000;
  */
uint8_t CATCommandCenterFequencyB(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	//Check if is Return Value, same syntax as Write command
	if(data[11] == ';') {
		//Return Value from Read Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[2], 9, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		radioBConfig.centerFrequency = value;
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Framing Mode CAT Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: FM02; Read: FM0; Return: FM02;
  */
uint8_t CATCommandFraming(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is Return Value, same syntax as Write command
	if(data[4] == ';') {
		//Return Value from Read Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 1, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_A) {
			radioAConfig.framing = value;
		}
		else if(radio == RADIO_B) {
			radioBConfig.framing = value;
		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Function RX (RX On/Off) CAT Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: FR00; Read: FR0; Return: FR00;
  */
uint8_t CATCommandFunctionRX(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is Return Value, same syntax as Write command
	if(data[4] == ';') {
		//Return Value from Read Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 1, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_A) {
			if(value == 0x01) {
				//Check if is AFSK mode, if yes change AFSK register because have different meaning in RX or TX
				if(radioAConfig.modulation == RadioModulation_AFSK) {

				}
			}
			radioAConfig.operationMode = value;
		}
		else if(radio == RADIO_B) {
			if(value == 0x01) {
				//Check if is AFSK mode, if yes change AFSK register because have different meaning in RX or TX
				if(radioBConfig.modulation == RadioModulation_AFSK) {

				}
			}
			radioBConfig.operationMode = value;
		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Function TX (TX On/Off) CAT Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: FT01; Read: FT0; Return: FT01;
  */
uint8_t CATCommandFunctionTX(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is Return Value, same syntax as Write command
	if(data[4] == ';') {
		//Return Value from Read Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 1, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_A) {
			if(value == 0x00) {
				radioAConfig.operationMode = RadioMode_OFF;
			}
			else if(value == 0x01) {
				radioAConfig.operationMode = RadioMode_TX;

				//Check if is AFSK mode, if yes change AFSK register because have different meaning in RX or TX
				if(radioAConfig.modulation == RadioModulation_AFSK) {

				}
			}
			else {
				return 1;
			}
		}
		else if(radio == RADIO_B) {
			if(value == 0x00) {
				radioBConfig.operationMode = RadioMode_OFF;
			}
			else if(value == 0x01) {
				radioBConfig.operationMode = RadioMode_TX;

				//Check if is AFSK mode, if yes change AFSK register because have different meaning in RX or TX
				if(radioBConfig.modulation == RadioModulation_AFSK) {

				}
			}
			else {
				return 1;
			}
		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the AGC Speed Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: GT001; Read: GT0; Return: GT001;
  */
uint8_t CATCommandAGCSpeed(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is Return Value, same syntax as Write command
	if(data[5] == ';') {
		//Return Value from Read Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 2, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_A) {
			radioAConfig.agcSpeed = (15 - value);	//Inverted Logic: CAT 0-> OFF, Local 0-> Fastest
		}
		else if(radio == RADIO_B) {
			radioBConfig.agcSpeed = (15 - value);	//Inverted Logic: CAT 0-> OFF, Local 0-> Fastest
		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the IF Frequency Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: IS1010000; Read: IS1; Return: IS1010000;
  */
uint8_t CATCommandIFFrequency(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is Return Value, same syntax as Write command
	if(data[9] == ';') {
		//Return Value from Read Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 6, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_A) {
			radioAConfig.ifFrequency = value;
		}
		else if(radio == RADIO_B) {
			radioBConfig.ifFrequency = value;
		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Modulation Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: MD01; Read: MD0; Return: MD01;
  */
uint8_t CATCommandModulation(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is Return Value, same syntax as Write command
	if(data[4] == ';') {
		//Return Value from Read Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 1, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_A) {
			radioAConfig.modulation = value;
		}
		else if(radio == RADIO_B) {
			radioBConfig.modulation = value;
		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the TX Power Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: PC110; Read: PC1; Return: PC110;
  */
uint8_t CATCommandTXPower(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is Return Value, same syntax as Write command
	if(data[5] == ';') {
		//Return Value from Read Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 2, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_A) {
			radioAConfig.outputPower = (value - 10);
		}
		else if(radio == RADIO_B) {
			radioBConfig.outputPower = (value - 10);
		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the RX Bandwidth Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: SH0250000; Read: SH0; Return: SH0250000;
  */
uint8_t CATCommandBandwidth(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is Return Value, same syntax as Write command
	if(data[9] == ';') {
		//Return Value from Read Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 6, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio == RADIO_A) {
			radioAConfig.bandwidth = value;
		}
		else if(radio == RADIO_B) {
			radioBConfig.bandwidth = value;
		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	*rDataLength = sprintf(rData, "OK;");
	return 0;
}

/**
  * @brief	This function handles the Read Meter Value
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: NA; Read: RM10; Return: RM10100;
  */
uint8_t CATCommandReadMeter(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	uint32_t meter = 0;
	if(CATASCIIToNumber(&data[3], 1, &meter) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	switch(meter) {
		case 0x00:
			//Meter RSSI Value
			if(data[7] == ';') {
				//Return Value from Read Command
				int32_t value = 0;
				if(CATASCIIToNumber(&data[4], 3, &value) != 0x00) {
					*rDataLength = sprintf(rData, "?;");
					return 1;
				}

				//RSSI value is always negative but sent as positive
				value = -value;

				if(radio == RADIO_A) {
					radioATracking.rssiTracking = value;
				}
				else if(radio == RADIO_B) {
					radioBTracking.rssiTracking = value;
				}
				else {
					*rDataLength = sprintf(rData, "?;");
					return 1;
				}
			}
			break;
		case 0x01:
			//Read RF Frequency Value
			if(data[11] == ';') {
				//Return Value from Read Command
				int32_t value = 0;
				if(CATASCIIToNumber(&data[5], 6, &value) != 0x00) {
					*rDataLength = sprintf(rData, "?;");
					return 1;
				}

				//Get value sign
				if(data[4] == '+') {
				}
				else if(data[4] == '-') {
					value = -value;
				}
				else {
					*rDataLength = sprintf(rData, "?;");
					return 1;
				}

				if(radio == RADIO_A) {
					radioATracking.rfFrequencyTracking = value;
				}
				else if(radio == RADIO_B) {
					radioBTracking.rfFrequencyTracking = value;
				}
				else {
					*rDataLength = sprintf(rData, "?;");
					return 1;
				}
			}
			break;
		default:
			*rDataLength = sprintf(rData, "?;");
			return 1;
	}

	return 0;
}

/**
  * @brief	This function handles the RSSI CAT Command
  * @param	data: Current Input data string
  * @param	dataLength: Length of the data string
  * @param	rData: Return data string, what to answer over the interface
  * @param	rDataLength: Length of the return data string
  * @return	0-> No Errors, 1->Error in Command
  *
  * Example: Set: NA; Read: SM1; Return: SM1100;
  */
uint8_t CATCommandRSSI(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	if(data[3] == ';') {
		//Read Command
		if(radio == RADIO_A) {
			*rDataLength = sprintf(rData, "SM0%03d;", (-radioATracking.rssiTracking));
			return 0;
		}
		else if(radio == RADIO_B) {
			*rDataLength = sprintf(rData, "SM1%03d;", (-radioBTracking.rssiTracking));
			return 0;
		}
		else {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}
}

uint8_t CATCommandDeviation(uint8_t* data, uint16_t dataLength, uint8_t* rData, uint16_t* rDataLength) {
	uint32_t radio = 0;
	if(CATASCIIToNumber(&data[2], 1, &radio) != 0x00) {
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}

	//Check if is Return Value, same syntax as Write command
	if(data[5] == ';') {
		//Return Value from Read Command
		uint32_t value = 0;
		if(CATASCIIToNumber(&data[3], 2, &value) != 0x00) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}

		if(radio > 1) {
			*rDataLength = sprintf(rData, "?;");
			return 1;
		}
	}
	else {
		//Syntax Error
		*rDataLength = sprintf(rData, "?;");
		return 1;
	}
}

/**
  * @brief	This function calculates the Power of base^exp, both uint8_t
  * @param	base: Base value of the Power
  * @param	exp: Exponent value of the Power
  * @return	The Power of base^exp
  */
uint32_t UIntPow(uint8_t base, uint8_t exp) {
	if(exp == 0) {
		return 1;
	}

	uint32_t value = base;
	uint8_t i;
	for(i = 1; i < exp; i++) {
		value *= base;
	}

	return value;
}

/**
  * @brief	This function converts the CAT value fields to int
  * @param	ascii: The CAT value field in ASCII
  * @param	asciiLength: Length of the ASCII field aka N digits
  * @param	value: Pointer to return value
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t CATASCIIToNumber(uint8_t* ascii, uint8_t asciiLength, int32_t* value) {
	*value = 0;

	uint8_t i;
	for(i = 0; i < asciiLength; i++) {
		if(ascii[i] < '0' || ascii[i] > '9') {
			return 1;
		}
		uint32_t mult = UIntPow(10, (asciiLength - i - 1));
		*value += (ascii[i] - '0') * mult;
	}

	return 0;
}
