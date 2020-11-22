#ifndef ILI9488DEFINES_H_
#define ILI9488DEFINES_H_

#define NOP						0x00	//NOP
#define SWRESET					0x01	//Soft Reset
#define aaaaa					0x04	//Read display identification information
#define aaaaa					0x05	//Read Number of the Errors on DSI
#define RDDST					0x09	//Read Display Status
#define aaaaa					0x0A	//Read Display Power Mode
#define aaaaa					0x0B	//Read Display MADCTL
#define aaaaa					0x0C	//Read Pixel Format
#define aaaaa					0x0D	//Read Display Image Mode
#define aaaaa					0x0E	//Read Display signal Mode
#define aaaaa					0x0F	//Read Display Self-Diagnostic Result
#define SLPIN					0x10	//Sleep IN
#define SLPOUT					0x11	//Sleep OUT
#define aaaaa					0x12	//Partial Mode ON
#define NORON					0x13	//Normal Display Mode ON
#define aaaaa					0x20	//Display Inversion OFF
#define aaaaa					0x21	//Display Inversion ON
#define aaaaa					0x22	//All Pixel OFF
#define aaaaa					0x23	//All Pixel ON
#define DISPOFF					0x28	//Display OFF
#define DISPON					0x29	//Display ON
#define CASET					0x2A	//Column Address Set
#define PASET					0x2B	//Page Address Set
#define RAMWR					0x2C	//Memory Write
#define aaaaa					0x2E	//Memory Read
#define aaaaa					0x30	//Partial Area
#define VSCRDEF					0x33	//Vertical Scrolling Definition
#define aaaaa					0x34	//Tearing Effect Line OFF
#define aaaaa					0x35	//Tearing Effect Line ON
#define MADCTL					0x36	//Memory Access Control
#define VSCRSADD				0x37	//Vertical Scrolling Start Address
#define aaaaa					0x38	//Idle Mode OFF
#define aaaaa					0x39	//Idle Mode ON
#define PIXSET					0x3A	//Interface Pixel Format
#define aaaaa					0x3C	//Memory Write Continue
#define aaaaa					0x3E	//Memory Read Continue
#define aaaaa					0x44	//Write Tear Scan line
#define aaaaa					0x45	//Read Tear Scan Line
#define aaaaa					0x51	//Write Display Brightness value
#define aaaaa					0x52	//Read Display Brightness Value
#define aaaaa					0x53	//Write CTRL Display value
#define aaaaa					0x54	//Read CTRL Display value
#define aaaaa					0x55	//Write Content Adaptive Brightness Control value
#define aaaaa					0x56	//Read Content Adaptive Brightness Control value
#define aaaaa					0x5E	//Write CABC Minimum Brightness
#define aaaaa					0x5F	//Read CABC Minimum Brightness
#define aaaaa					0x68	//Read automatic brightness control self-diagnostic result
#define aaaaa					0xDA	//Read ID1
#define aaaaa					0xDB	//Read ID2
#define aaaaa					0xDC	//Read ID3


#endif /* ILI9488DEFINES_H_ */
