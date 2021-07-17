#include "tft_interface.h"

void TFTInit8BitParalel() {
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);

	GPIOSetPinMode(GPIO_OUT_LCD_nRD, GPIO_Mode_Output);
	GPIOSetPinMode(GPIO_OUT_LCD_nWR, GPIO_Mode_Output);
	GPIOSetPinMode(GPIO_OUT_LCD_RS, GPIO_Mode_Output);
	GPIOSetPinMode(GPIO_OUT_LCD_nCS, GPIO_Mode_Output);
	GPIOSetPinMode(GPIO_OUT_LCD_nRST, GPIO_Mode_Output);

	GPIOSetPinMode(GPIO_OUT_LCD_D0, GPIO_Mode_Output);
	GPIOSetPinMode(GPIO_OUT_LCD_D1, GPIO_Mode_Output);
	GPIOSetPinMode(GPIO_OUT_LCD_D2, GPIO_Mode_Output);
	GPIOSetPinMode(GPIO_OUT_LCD_D3, GPIO_Mode_Output);
	GPIOSetPinMode(GPIO_OUT_LCD_D4, GPIO_Mode_Output);
	GPIOSetPinMode(GPIO_OUT_LCD_D5, GPIO_Mode_Output);
	GPIOSetPinMode(GPIO_OUT_LCD_D6, GPIO_Mode_Output);
	GPIOSetPinMode(GPIO_OUT_LCD_D7, GPIO_Mode_Output);

	//Set all to default position, high
	GPIOWrite(GPIO_OUT_LCD_nRD, 0x01);
	GPIOWrite(GPIO_OUT_LCD_nWR, 0x01);
	GPIOWrite(GPIO_OUT_LCD_RS, 0x01);

	GPIOWrite(GPIO_OUT_LCD_nCS, 0x01);

	GPIOWrite(GPIO_OUT_LCD_nRST, 0x01);
	Delay(5);
	GPIOWrite(GPIO_OUT_LCD_nRST, 0x00);
	Delay(15);
	GPIOWrite(GPIO_OUT_LCD_nRST, 0x01);
	Delay(15);

	GPIOWrite(GPIO_OUT_LCD_nCS, 0x00);
}

void TFTWrite8BitParalel(uint8_t data) {
	GPIOWrite(GPIO_OUT_LCD_nWR, 0x00);		//WR low

	WRITE_REG(GPIOB->BSRR, data);
	uint32_t aux = ((~data) & 0xFF) << 16;
	WRITE_REG(GPIOB->BSRR, aux);

	GPIOWrite(GPIO_OUT_LCD_nWR, 0x01);		//WR high
}

uint8_t TFTRead8BitParalel(void) {
	uint8_t data = 0;

	GPIOWrite(GPIO_OUT_LCD_nRD, 0x00);		//RD low

	data = READ_REG(GPIOB->IDR) & 0x00FF;

	GPIOWrite(GPIO_OUT_LCD_nRD, 0x01);		//RD high

	return data;
}

void TFTCommand8BitParalel(uint8_t data) {
	GPIOWrite(GPIO_OUT_LCD_RS, 0x00);		//D/CX low

	GPIOWrite(GPIO_OUT_LCD_nWR, 0x00);		//WR low

	WRITE_REG(GPIOB->BSRR, data);
	uint32_t aux = ((~data) & 0xFF) << 16;
	WRITE_REG(GPIOB->BSRR, aux);

	GPIOWrite(GPIO_OUT_LCD_nWR, 0x01);		//WR high

	GPIOWrite(GPIO_OUT_LCD_RS, 0x01);		//D/CX high
}

void TFTInitSPI() {
	//Enable bus clocks
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);

	//Set up SPI
	SPI1Init();

	//Set up GPIOs
	GPIOSetPinMode(GPIO_OUT_LCD_RS, GPIO_Mode_Output);
	GPIOSetPinMode(GPIO_OUT_LCD_nCS, GPIO_Mode_Output);
	GPIOSetPinMode(GPIO_OUT_LCD_nRST, GPIO_Mode_Output);

	//Set all to default position, high
	GPIOWrite(GPIO_OUT_LCD_RS, 0x01);

	GPIOWrite(GPIO_OUT_LCD_nCS, 0x01);

	GPIOWrite(GPIO_OUT_LCD_nRST, 0x01);
	Delay(5);
	GPIOWrite(GPIO_OUT_LCD_nRST, 0x00);
	Delay(15);
	GPIOWrite(GPIO_OUT_LCD_nRST, 0x01);
	Delay(15);

	GPIOWrite(GPIO_OUT_LCD_nCS, 0x00);
}

void TFTWriteSPI(uint8_t data) {
//	GPIOWrite(GPIO_OUT_LCD_nCS, 0x00);		//CS Low

//	SPI1Write(data);
	LL_SPI_TransmitData8(SPI1, data);

//	GPIOWrite(GPIO_OUT_LCD_nCS, 0x01);		//CS High
}

uint8_t TFTReadSPI(void) {
//	GPIOWrite(GPIO_OUT_LCD_nCS, 0x00);		//CS Low

	LL_SPI_TransmitData8(SPI1, 0xFF);
	while(!LL_SPI_IsActiveFlag_RXNE(SPI1));
	return LL_SPI_ReceiveData8(SPI1);

//	GPIOWrite(GPIO_OUT_LCD_nCS, 0x01);		//CS High
}

void TFTCommandSPI(uint8_t data) {
	//High pulse to cancel/exit previous possible read/write mode
	GPIOWrite(GPIO_OUT_LCD_nCS, 0x01);		//CS High
	GPIOWrite(GPIO_OUT_LCD_nCS, 0x00);		//CS Low

	GPIOWrite(GPIO_OUT_LCD_RS, 0x00);		//D/CX Low

	SPI1Write(data);
	uint8_t dummy = SPI1Read();

	GPIOWrite(GPIO_OUT_LCD_RS, 0x01);		//D/CX High

//	GPIOWrite(GPIO_OUT_LCD_nCS, 0x01);		//CS High
}
