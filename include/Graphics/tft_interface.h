#ifndef TFT_INTERFACE_H_
#define TFT_INTERFACE_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "gpio.h"
#include "rcc.h"
#include "spi.h"

#include "ili9341Defines.h"

#define SCREEN_HEIGHT						320
#define SCREEN_WIDTH						240

#define GPIO_OUT_LCD_nRD					26		//LCD RDX - Data read
#define GPIO_OUT_LCD_nWR					47		//LCD WRX - Data write
#define GPIO_OUT_LCD_RS						46		//LCD D/CX - Display data/Command selection pin, 1 -> Display data, 0 -> Command data
#define GPIO_OUT_LCD_nCS					45		//LCD CSX - Chip-select, active low
//#define GPIO_OUT_LCD_nCS					15		//LCD CSX - Chip-select, active low
#define GPIO_OUT_LCD_nRST					27		//LCD RESX - External Reset Signal, active low

#define GPIO_OUT_LCD_D0						16
#define GPIO_OUT_LCD_D1						17
#define GPIO_OUT_LCD_D2						18
#define GPIO_OUT_LCD_D3						19
#define GPIO_OUT_LCD_D4						20
#define GPIO_OUT_LCD_D5						21
#define GPIO_OUT_LCD_D6						22
#define GPIO_OUT_LCD_D7						23

#define TFT_Init()			TFTInitSPI()
#define TFT_Data(data)		TFTWriteSPI((data))
#define TFT_Command(data)	TFTCommandSPI((data))
#define TFT_Read()			TFTReadSPI()

void TFTInit8BitParalel(void);
void TFTWrite8BitParalel(uint8_t data);
uint8_t TFTRead8BitParalel(void);
void TFTCommand8BitParalel(uint8_t data);

void TFTInitSPI();
void TFTWriteSPI(uint8_t data);
uint8_t TFTReadSPI(void);
void TFTCommandSPI(uint8_t data);

#ifdef __cplusplus
}
#endif

#endif /* TFT_INTERFACE_H_ */
