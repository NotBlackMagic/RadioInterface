#ifndef ILI9481DEFINES_H_
#define ILI9481DEFINES_H_

#define NOP						0x00
#define SOFT_RESET				0x01
#define GET_RED_CHANNEL			0x06
#define GET_GREEN_CHANNEL		0x07
#define GET_BLUE_CHANNEL		0x08
#define GET_POWER_MODE			0x0A
#define GET_ADDRESS_MODE		0x0B
#define GET_PIXEL_FORMAT		0x0C
#define GET_DISPLAY_MODE		0x0D
#define GET_SIGNAL_MODE			0x0E
#define GET_DIAGNOSTIC_RESULT	0x0F
#define ENTER_SLEEP_MODE		0x10
#define EXIT_SLEEP_MODE			0x11
#define ENTER_PARTIAL_MODE		0x12
#define ENTER_NORMAL_MODE		0x13
#define EXIT_INVERT_MODE		0x20
#define ENTER_INVERT_MODE		0x21
#define SET_GAMMA_CURVE			0x26
#define SET_DISPLAY_OFF			0x28
#define SET_DISPLAY_ON			0x29
#define SET_COLUMN_ADDRESS		0x2A
#define SET_PAGE_ADDRESS		0x2B
#define WRITE_MEMORY_START		0x2C
#define WRITE_LUT				0x2D
#define READ_MEMORY_START		0x2E
#define SET_PARTIAL_AREA		0x30
#define SET_SCROLL_AREA			0x33
#define SET_TEAR_OFF			0x34
#define SET_TEAR_ON				0x35
#define SET_ADDRESS_MODE		0x36
#define SET_SCROLL_START		0x37
#define EXIT_IDLE_MODE			0x38
#define ENTER_IDLE_MODE			0x39
#define SET_PIXEL_FORMAT		0x3A
#define WRITE_MEMORY_CONTINUE	0x3C
#define READ_MEMORY_CONTINUE	0x3E
#define SET_TEAR_SCANLINE		0x44
#define GET_SCANLINE			0x45
#define READ_DDB_START			0xA1
#define READ_DDB_CONTINUE		0xA8

#define CMD_ACCESS_PROTECT		0xB0 	//Command Access Protect
#define LPM_CONTROL				0xB1	//Low Power Mode Control
#define FRAME_ACCESS_SETTING	0xB3	//Frame Memory Access and Interface setting
#define DISP_MODE_FR_MEM_SET	0xB4	//Display Mode and Frame Memory Write Mode setting
#define DEVICE_CODE_READ		0xBF	//Device code Read
#define PANEL_DRIVE_SET			0xC0 	//Panel Driving Setting
#define DISP_TIM_SET_NORMAL		0xC1	//Display Timing Setting for Normal Mode
#define DISP_TIM_SET_PARTIAL	0xC2 	//Display Timing Setting for Partial Mode
#define DISP_TIM_SET_IDLE 		0xC3 	//Display Timing Setting for Idle Mode
#define FR_INV_CTRL				0xC5 	//Frame rate and Inversion Control
#define INTERFACE_CTRL			0xC6 	//Interface Control
#define GAMMA_SETTING			0xC8 	//Gamma Setting
#define PWR_SETTING				0xD0 	//Power Setting
#define VCOM_CTRL				0xD1 	//VCOM Control
#define PWR_SET_NRM_MODE		0xD2 	//Power Setting for Normal Mode
#define PWR_SET_PAR_MODE		0xD3 	//Power Setting for Partial Mode
#define PWR_SET_IDLE_MODE		0xD4 	//Power Setting for Idle Mode
#define NV_MEMORY_WRITE			0xE0 	//NV Memory Write
#define NV_MEMORY_CONTROL		0xE1 	//NV Memory Control
#define NV_MEMORY_STATUS		0xE2 	//NV Memory Status
#define NV_MEMORY_PROTECTION	0xE3 	//NV Memory Protection
#define EEPROM_WR_ENABLE		0xE8	//EEPROM Write Enable
#define EEPROM_WR_DISABLE		0xE9 	//EEPROM Write Disable
#define EEPROM_WORD_WR			0xEA	//EEPROM Word Write
#define EEPROM_WORD_RD			0xEB	//EEPROM Word Read
#define EEPROM_ADDRESS_SET		0xEC	//EEPROM Address Set
#define EEPROM_ERASE			0xED	//EEPROM Erase
#define EEPROM_ERASE_ALL		0xEE	//EEPROM Erase All

#endif /* ILI9481DEFINES_H_ */
