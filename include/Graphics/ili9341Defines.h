#ifndef ILI9341DEFINES_H_
#define ILI9341DEFINES_H_

//Level 1 Commands
#define NOP						0x00	//NOP
#define SWRESET					0x01	//Soft Reset
#define RDDIDIF					0x04	//Read display identification information
#define RDDST					0x09	//Read Display Status
#define RDDPM 					0x0A	//Read Display Power Mode
#define RDDMADCTL 				0x0B	//Read Display MADCTL
#define RDDCOLMOD 				0x0C	//Read Pixel Format
#define RDDIM					0x0D	//Read Display Image Mode
#define RDDSM 					0x0E	//Read Display Signal Mode
#define RDDSDR 					0x0F	//Read Display Self-Diagnostic Result
#define SLPIN					0x10	//Sleep IN
#define SLPOUT					0x11	//Sleep OUT
#define PTLON 					0x12	//Partial Mode ON
#define NORON					0x13	//Normal Display Mode ON
#define DINVOFF 				0x20	//Display Inversion OFF
#define DINVON 					0x21	//Display Inversion ON
#define GAMSET 					0x26	//Gamma Set
#define DISPOFF					0x28	//Display OFF
#define DISPON					0x29	//Display ON
#define CASET					0x2A	//Column Address Set
#define PASET					0x2B	//Page Address Set
#define RAMWR					0x2C	//Memory Write
#define RGBSET 					0x2D	//Color Set
#define RAMRD					0x2E	//Memory Read
#define PLTAR 					0x30	//Partial Area
#define VSCRDEF					0x33	//Vertical Scrolling Definition
#define TEOFF 					0x34	//Tearing Effect Line OFF
#define TEON 					0x35	//Tearing Effect Line ON
#define MADCTL					0x36	//Memory Access Control
#define VSCRSADD				0x37	//Vertical Scrolling Start Address
#define IDMOFF 					0x38	//Idle Mode OFF
#define IDMON 					0x39	//Idle Mode ON
#define PIXSET					0x3A	//Interface Pixel Format
#define aaaaa					0x3C	//Memory Write Continue
#define aaaaa					0x3E	//Memory Read Continue
#define aaaaa					0x44	//Write Tear Scan line
#define aaaaa					0x45	//Read Tear Scan Line
#define WRDISBV					0x51	//Write Display Brightness value
#define RDDISBV					0x52	//Read Display Brightness Value
#define WRCTRLD					0x53	//Write CTRL Display value
#define RDCTRLD					0x54	//Read CTRL Display value
#define WRCABC					0x55	//Write Content Adaptive Brightness Control value
#define RDCABC					0x56	//Read Content Adaptive Brightness Control value
#define aaaaa					0x5E	//Write CABC Minimum Brightness
#define aaaaa					0x5F	//Read CABC Minimum Brightness
#define RDID1					0xDA	//Read ID1
#define RDID2					0xDB	//Read ID2
#define RDID3					0xDC	//Read ID3

//Level 2 Commands
#define IFMODE 					0xB0	//RGB Interface Signal Control

#endif /* ILI9341DEFINES_H_ */
