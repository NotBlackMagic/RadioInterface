#ifndef PINMAPING_H_
#define PINMAPING_H_

#ifdef __cplusplus
extern "C" {
#endif

//Input Pin Mapping
//#define GPIO_IN_BTN_1						31		//Input Button 1 (OK)
//#define GPIO_IN_BTN_2						30		//Input Button 2 (+)
//#define GPIO_IN_BTN_3						29		//Input Button 3 (-)
//#define GPIO_IN_BTN_4						28		//Input Button 4 (SEL)

#define GPIO_IN_BTN_0						0		//Input Button 0 (UP)
#define GPIO_IN_BTN_1						1		//Input Button 1 (ENTER/MENU_3)
#define GPIO_IN_BTN_2						2		//Input Button 2 (BACK/MENU_4)
#define GPIO_IN_BTN_3						3		//Input Button 3 (V<=>U/MENU_1)
#define GPIO_IN_BTN_4						4		//Input Button 4 (SELECT/MENU_2)
#define GPIO_IN_BTN_5						5		//Input Button 5 (RIGHT)
#define GPIO_IN_BTN_6						6		//Input Button 6 (DOWN)
#define GPIO_IN_BTN_7						7		//Input Button 7 (CENTER)
#define GPIO_IN_BTN_8						11		//Input Button 8 (LEFT)

#define GPIO_IN_SD_DET						12		//Input SD Card detection

//Output Pin Mapping
#define GPIO_OUT_BL							8		//Output Backlight Enable

#ifdef __cplusplus
}
#endif

#endif /* PINMAPING_H_ */
