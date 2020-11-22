#include "gpio.h"

#include "pinMaping.h"

/**
  * @brief	This function initializes the GPIO that don't use a peripheral (ADC/UART/SPI etc)
  * @param	None
  * @return	None
  */
void GPIOInit() {
	//Enable Port Clocks
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);

	//Enable EXTI/AFIO Clocks and Power
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	//Enable PC14 and PC15 as general IO
	LL_GPIO_AF_Remap_SWJ_NOJTAG();

	//Set Generic Input GPIO's
	GPIOSetPinMode(GPIO_IN_BTN_0, GPIO_Mode_Input);
	GPIOSetPinMode(GPIO_IN_BTN_1, GPIO_Mode_Input);
	GPIOSetPinMode(GPIO_IN_BTN_2, GPIO_Mode_Input);
	GPIOSetPinMode(GPIO_IN_BTN_3, GPIO_Mode_Input);
	GPIOSetPinMode(GPIO_IN_BTN_4, GPIO_Mode_Input);
	GPIOSetPinMode(GPIO_IN_BTN_5, GPIO_Mode_Input);
	GPIOSetPinMode(GPIO_IN_BTN_6, GPIO_Mode_Input);
	GPIOSetPinMode(GPIO_IN_BTN_7, GPIO_Mode_Input);
	GPIOSetPinMode(GPIO_IN_BTN_8, GPIO_Mode_Input);

	GPIOSetPinMode(GPIO_IN_SD_DET, GPIO_Mode_Input);

	//Set Input Pins Interrupts
	LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTA, LL_GPIO_AF_EXTI_LINE0);
	LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTA, LL_GPIO_AF_EXTI_LINE1);
	LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTA, LL_GPIO_AF_EXTI_LINE2);
	LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTA, LL_GPIO_AF_EXTI_LINE3);
	LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTA, LL_GPIO_AF_EXTI_LINE4);
	LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTA, LL_GPIO_AF_EXTI_LINE5);
	LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTA, LL_GPIO_AF_EXTI_LINE6);
	LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTA, LL_GPIO_AF_EXTI_LINE7);
	LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTA, LL_GPIO_AF_EXTI_LINE11);
	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_0);
	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_1);
	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_2);
	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_3);
	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_4);
	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_5);
	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_6);
	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_7);
	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_11);
	LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_0);
	LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_1);
	LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_2);
	LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_3);
	LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_4);
	LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_5);
	LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_6);
	LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_7);
	LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_11);

	//Set Generic Output GPIO's
	GPIOSetPinMode(GPIO_OUT_BL, GPIO_Mode_Output);

	//Set Output GPIOs
	GPIOWrite(GPIO_OUT_BL, 0x01);

	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);
	NVIC_EnableIRQ(EXTI4_IRQn);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	NVIC_SetPriority(EXTI0_IRQn, 0);
	NVIC_SetPriority(EXTI1_IRQn, 0);
	NVIC_SetPriority(EXTI2_IRQn, 0);
	NVIC_SetPriority(EXTI3_IRQn, 0);
	NVIC_SetPriority(EXTI4_IRQn, 0);
	NVIC_SetPriority(EXTI9_5_IRQn, 0);
	NVIC_SetPriority(EXTI15_10_IRQn, 0);
}

/**
  * @brief	This function sets the output mode type of a pin
  * @param	gpio: Pin to define output mode
  * @param	mode: Output mode of this pin
  * @return	None
  */
void GPIOSetPinMode(uint8_t gpio, GPIOOutputMode mode) {
	uint8_t port = (gpio >> 4);
	uint8_t pin = gpio & 0x0F;
	LL_GPIO_SetPinMode(gpioPorts[port], gpioPins[pin], gpioOutputMode[mode]);
}

/**
  * @brief	This function sets the output of a pin
  * @param	gpio: Pin to set output
  * @param	on: 1 output is set high, 0 output is set low
  * @return	None
  */
void GPIOWrite(uint8_t gpio, uint8_t on) {
	uint8_t port = (gpio >> 4);
	uint8_t pin = gpio & 0x0F;
	if(on == 1) {
		LL_GPIO_SetOutputPin(gpioPorts[port], gpioPins[pin]);
	}
	else {
		LL_GPIO_ResetOutputPin(gpioPorts[port], gpioPins[pin]);
	}
}

/**
  * @brief	This function gets the input state of a pin
  * @param	gpio: Pin to set output
  * @return	1 input is set high, 0 input is set low
  */
uint8_t GPIORead(uint8_t gpio) {
	uint8_t port = (gpio >> 4);
	uint8_t pin = gpio & 0x0F;
	return LL_GPIO_IsInputPinSet(gpioPorts[port], gpioPins[pin]);
}
