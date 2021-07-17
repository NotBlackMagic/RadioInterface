#include "tft_gui.h"

ColorsStruct Colors888 = {
		.white =	{0xFF, 0xFF, 0xFF},
		.silver =	{0xC0, 0xC0, 0xC0},
		.gray =		{0x80, 0x80, 0x80},
		.black =	{0x00, 0x00, 0x00},
		.red =		{0xFF, 0x00, 0x00},
		.aqua =		{0x00, 0xFF, 0xFF},
		.blue =		{0x00, 0x00, 0xFF},
		.teal =		{0x00, 0x80, 0x80},
		.navy =		{0x00, 0x00, 0x80},
		.purple =	{0x80, 0x00, 0x80},
		.yellow =	{0xFF, 0xFF, 0x00},
		.lime =		{0x00, 0xFF, 0x00},
		.fuchsia =	{0xFF, 0x00, 0xFF},
		.maroon =	{0x80, 0x00, 0x00},
		.green =	{0x00, 0x80, 0x00},
		.orange =	{0xFF, 0xA5, 0x00},
		.olive =	{0x80, 0x80, 0x00}
};

ColorsStruct Colors666 = {
		.white =	{0x3F, 0x3F, 0x3F},
		.silver =	{0x30, 0x30, 0x30},
		.gray =		{0x20, 0x20, 0x20},
		.black =	{0x00, 0x00, 0x00},
		.red =		{0x3F, 0x00, 0x00},
		.aqua =		{0x00, 0x3F, 0x3F},
		.blue =		{0x00, 0x00, 0x3F},
		.teal =		{0x00, 0x20, 0x20},
		.navy =		{0x00, 0x00, 0x20},
		.purple =	{0x3A, 0x00, 0x3A},
		.yellow =	{0x3F, 0x3F, 0x00},
		.lime =		{0x00, 0x3F, 0x00},
		.fuchsia =	{0x3F, 0x00, 0x3F},
		.maroon =	{0x20, 0x00, 0x00},
		.green =	{0x00, 0x3A, 0x00},
		.orange =	{0x3F, 0x29, 0x00},
		.olive =	{0x20, 0x20, 0x00}
};

/**
  * @brief	This function converts from 24-Bit Color, 888RGB, to 18-Bit Color, 666RGB
  * @param	color: 24-Bit Color to convert
  * @return	Returns the 18-Bit Color
  */
Color ToRGB666Convertion(Color color) {
	Color rgb666Color;

	rgb666Color.red = color.red >> 2;
	rgb666Color.green = color.green >> 2;
	rgb666Color.blue = color.blue >> 2;

	return rgb666Color;
}

/**
  * @brief	This function returns a color from a defined gradient
  * @param	index: Value to get a color from the gradient
  * @return	Returns the 18-Bit Color
  */
Color ValueToColorGradient(uint8_t index) {
	Color gColor;

	//Invert index: So that RED is 255 and BLUE is 0
	index = 255 - index;

	if(index < 64) {
		//Iterate from RED to YELLOW
		gColor.red = 0x3F;
		gColor.green = index;
		gColor.blue = 0x00;
	}
	else if(index < 128) {
		//Iterate from YELLOW to GREEN
		gColor.red = 0x3F - index;
		gColor.green = 0x3F;
		gColor.blue = 0x00;
	}
	else if(index < 192) {
		//Iterate from GREEN to CYAN
		gColor.red = 0x00;
		gColor.green = 0x3F;
		gColor.blue = index;
	}
	else {
		//Iterate from CYAN to BLUE
		gColor.red = 0x00;
		gColor.green = 0x3F - index;
		gColor.blue = 0x3F;
	}

	return gColor;
}

/**
  * @brief	This function sets the background, full screen, to a single color
  * @param	color: Color to set the background to (18-Bit Color)
  * @return	None
  */
void SetBackgroundColor(Color color) {
	uint32_t x = 0;

	Vector2D position;
	position.x = 0;
	position.y = 0;

	SetPoint(position);

	TFT_Command(RAMWR);
	for(x = 0; x < (SCREEN_HEIGHT * SCREEN_WIDTH); x++) {
			TFT_Data(color.blue << 2);
			TFT_Data(color.green << 2);
			TFT_Data(color.red << 2);
	}
}

/**
  * @brief	This function draws a line between two points
  * @param	pointA: Point 1 for the line
  * @param	pointB: Point 2 for the line
  * @param	color: Line color (18-Bit Color)
  * @return	None
  */
void DrawLine(Vector2D pointA, Vector2D pointB, Color color) {
	uint32_t distance = (pointA.x - pointB.x)*(pointA.x - pointB.x) + (pointA.y - pointB.y)*(pointA.y - pointB.y);

	if(distance < 4) {
		return;
	}

	Vector2D midPoint;
	midPoint.x = (pointA.x + pointB.x) >> 1;
	midPoint.y = (pointA.y + pointB.y) >> 1;

	SetPixel(midPoint, color);
	DrawLine(pointA, midPoint, color);
	DrawLine(midPoint, pointB, color);
}

/**
  * @brief	This function draws a filled rectangle with a optional boarder
  * @param	position: Position of the top left corner of the rectangle
  * @param	size: Size of the rectangle in pixels
  * @param	fillColor: Fill color of the rectangle (18-Bit Color)
  * @param	thickness: Boarder/frame thickness in pixels, set to 0 for no boarder/frame
  * @param	frameColor: Boarder/Frame color of the rectangle (18-Bit Color)
  * @return	None
  */
void DrawRect(Vector2D position, Vector2D size, Color fillColor, uint8_t thickness, Color frameColor) {
	uint16_t x,y;

	SetVerticalArea(position.x, position.x + size.x - 1);
	SetHorizontalArea(position.y, position.y + size.y - 1);

	TFT_Command(RAMWR);
	for(x = position.x; x < (position.x + size.x); x++) {
		for(y = position.y; y < (position.y + size.y); y++) {
			if(y < (position.y + thickness) || y >= (position.y + size.y - thickness) || x < (position.x + thickness) || x >= (position.x + size.x - thickness)) {
				TFT_Data(frameColor.blue << 2);
				TFT_Data(frameColor.green << 2);
				TFT_Data(frameColor.red << 2);
			}
			else {
				TFT_Data(fillColor.blue << 2);
				TFT_Data(fillColor.green << 2);
				TFT_Data(fillColor.red << 2);
			}
		}
	}
}

/**
  * @brief	This function draws a filled circle with a optional boarder
  * @param	position: Position of the center of the circle
  * @param	radius: Radius of the circle in pixels
  * @param	fillColor: Fill color of the circle (18-Bit Color)
  * @param	thickness: Boarder/frame thickness in pixels, set to 0 for no boarder/frame
  * @param	frameColor: Boarder/Frame color of the circle (18-Bit Color)
  * @return	None
  */
void DrawCircle(Vector2D position, uint16_t radius, Color fillColor, uint8_t thickness, Color frameColor) {
	Vector2D point;
	uint32_t rOutSqr = radius*radius;
	uint32_t rInSqr = (radius - thickness)*(radius - thickness);

//	SetVerticalArea((position.x - radius), (position.x + radius - 1));
//	SetHorizontalArea((position.y - radius), (position.y + radius - 1));

//	TFT_Command(RAMWR);
	for(point.x = (position.x - radius); point.x < (position.x + radius); point.x++) {
		for(point.y = (position.y - radius); point.y < (position.y + radius); point.y++) {
			uint32_t d = (point.x - position.x)*(point.x - position.x) + (point.y - position.y)*(point.y - position.y);

			if(d < rOutSqr) {
				if(d >= rInSqr) {
					//Between inner and outer circle limit, draw boarder
					SetPixel(point, frameColor);
				}
				else {
					SetPixel(point, fillColor);
				}
			}
		}
	}
}

//Test for Radius of 100: Pixel Set: 1490'370us; Area Set: 367'494us; Area Set w. Point Set: 619'972us
//void DrawFilledCircle(Vector2D position, uint16_t radius, Color fillColor) {
//	Vector2D point;
//	uint32_t rSqr = radius*radius;
//
//	SetVerticalArea((position.x - radius), (position.x + radius - 1));
//	SetHorizontalArea((position.y - radius), (position.y + radius - 1));
//
//	TFT_Command(RAMWR);
//	for(point.x = (position.x - radius); point.x < (position.x + radius); point.x++) {
//		for(point.y = (position.y - radius); point.y < (position.y + radius); point.y++) {
//			uint32_t d = (point.x - position.x)*(point.x - position.x) + (point.y - position.y)*(point.y - position.y);
//
//			if(d < rSqr) {
////				SetPixel(point, fillColor);
//				TFT_Data(fillColor.blue << 2);
//				TFT_Data(fillColor.green << 2);
//				TFT_Data(fillColor.red << 2);
//			}
//			else {
//				SetPoint(point);
//				TFT_Command(RAMWR);
//			}
//		}
//	}
//}
//
//void DrawFilledCircleFramed(Vector2D position, uint16_t radius, uint8_t thickness, Color fillColor, Color frameColor) {
//	Vector2D point;
//	uint32_t rOutSqr = radius*radius;
//	uint32_t rInSqr = (radius - thickness)*(radius - thickness);
//
////	SetVerticalArea((position.x - radius), (position.x + radius - 1));
////	SetHorizontalArea((position.y - radius), (position.y + radius - 1));
//
////	TFT_Command(RAMWR);
//	for(point.x = (position.x - radius); point.x < (position.x + radius); point.x++) {
//		for(point.y = (position.y - radius); point.y < (position.y + radius); point.y++) {
//			uint32_t d = (point.x - position.x)*(point.x - position.x) + (point.y - position.y)*(point.y - position.y);
//
//			if(d < rOutSqr) {
//				if(d >= rInSqr) {
//					//Between inner and outer circle limit, draw boarder
//					SetPixel(point, frameColor);
//				}
//				else {
//					SetPixel(point, fillColor);
//				}
//			}
//		}
//	}
//}

/**
  * @brief	This function draws a ASCII text with a filled background rectangle
  * @param	position: Position of the top left corner of the text rectangle
  * @param	text: ASCII char string of the text to draw/write
  * @param	stringLength: Length of the "text" ASCII char string
  * @param	fontSize: Integer multiplier for the font size: 1-> Default Size, 2-> Double Size, etc...
  * @param	textColor: Text color (18-Bit Color)
  * @param	backgroundColor: Color of the background rectangle (18-Bit Color)
  * @return	None
  */
void DrawASCIIText(Vector2D position, const char* text, uint8_t stringLength, uint8_t fontSize, Color textColor, Color backgroundColor) {
	uint16_t x,y;
	uint16_t length = stringLength*fontSize*8 + position.x;
	uint8_t indexString = 0;
	uint8_t fontIndex = 0;
	uint8_t indexChar = 0;
	uint8_t indexCol = 0;
	uint8_t h,k;
	k = 0;

	SetPoint(position);

	//Check if first char is a valid char
	if(text[indexString] > 127 || text[indexString] < 32) {
		//Not valid, substitute with a valid char placeholder
		fontIndex = '#' - 32;
	}
	else {
		fontIndex = (text[indexString] - 32);
	}

	for(x = position.x; x < length; x++) {
		SetColumn(x);

		TFT_Command(RAMWR);

		for(y = 0; y < 12; y++) {
			for(h = 0; h < fontSize; h++) {
				if((((font[fontIndex][y]) & ( 1 << indexChar )) >> indexChar) == 1) {
					TFT_Data(textColor.blue << 2);
					TFT_Data(textColor.green << 2);
					TFT_Data(textColor.red << 2);
				}
				else {
					TFT_Data(backgroundColor.blue << 2);
					TFT_Data(backgroundColor.green << 2);
					TFT_Data(backgroundColor.red << 2);
				}
			}
		}

		k += 1;

		if(k == fontSize) {
			k = 0;

			indexChar += 1;

			if(indexChar > 7) {
				indexChar = 0;
				indexString += 1;

				//Check if next char is a valid char
				if(text[indexString] > 127 || text[indexString] < 32) {
					//Not valid, substitute with a valid char placeholder
					fontIndex = '#' - 32;
				}
				else {
					fontIndex = (text[indexString] - 32);
				}
			}
		}
	}
}

/**
  * @brief	This function draws a symbol with a filled background rectangle
  * @param	position: Position of the top left corner of the text rectangle
  * @param	symbol: Symbol to draw, from ASCII Text Table defined in "font5x7.h", start at 0x80
  * @param	fontSize: Integer multiplier for the symbol size: 1-> Default Size, 2-> Double Size, etc...
  * @param	textColor: Symbol color (18-Bit Color)
  * @param	backgroundColor: Color of the background rectangle (18-Bit Color)
  * @return	None
  */
void DrawASCIISynmbol(Vector2D position, uint8_t symbol, uint8_t fontSize, Color textColor, Color backgroundColor) {
	uint16_t x,y;
	uint16_t lenght = fontSize*8+position.x;
	uint8_t indexString = 0;
	uint8_t indexChar = 0;
	uint8_t h,k;
	k = 0;
	SetPoint(position);

	for(x = position.x; x < lenght; x++){
		SetColumn(x);

		TFT_Command(RAMWR);

		for(y = 0; y < 12; y++){
			for(h = 0; h < fontSize; h++){
				if((((font[(symbol - 32)][y]) & ( 1 << indexChar )) >> indexChar) == 1) {
					TFT_Data(textColor.blue << 2);
					TFT_Data(textColor.green << 2);
					TFT_Data(textColor.red << 2);
				}
				else {
					TFT_Data(backgroundColor.blue << 2);
					TFT_Data(backgroundColor.green << 2);
					TFT_Data(backgroundColor.red << 2);
				}
			}
		}

		k += 1;

		if(k == fontSize) {
			k = 0;

			indexChar += 1;

			if(indexChar > 7) {
				indexChar = 0;
				indexString += 1;
			}
		}
	}
}

/**
  * @brief	This function draws a ASCII text box with a filled background rectangle of defined size with a optional boarder
  * @param	position: Position of the top left corner of the text rectangle
  * @param	size: Size of the text box rectangle
  * @param	thickness: Boarder/frame thickness in pixels, set to 0 for no boarder/frame
  * @param	text: ASCII char string of the text to draw/write
  * @param	stringLength: Length of the "text" ASCII char string
  * @param	fontSize: Integer multiplier for the font size: 1-> Default Size, 2-> Double Size, etc...
  * @param	textColor: Text color (18-Bit Color)
  * @param	backgroundColor: Color of the background rectangle (18-Bit Color)
  * @param	frameColor: Boarder/Frame color of the circle (18-Bit Color)
  * @return	None
  */
void DrawTextBox(Vector2D position, Vector2D size, uint8_t thickness, const char* text, uint8_t stringLength, uint8_t fontSize, Color textColor, Color backgroundColor, Color frameColor) {
	uint16_t textLength = stringLength*fontSize*8;
	uint16_t textOffsetX = (size.x - textLength) >> 1;
	uint16_t textOffsetY = (size.y - 12*fontSize) >> 1;

	uint8_t indexString = 0;
	uint8_t indexChar = 0;
	uint8_t indexCharY = 0;
	uint8_t k = 0;

	SetVerticalArea(position.x, position.x + size.x - 1);
	SetHorizontalArea(position.y, position.y + size.y - 1);

	TFT_Command(RAMWR);

	uint8_t ty = 0;
	uint8_t tx = 0;
	uint16_t x,y;
	for(x = 0; x < size.x; x++) {
		for(y = 0; y < size.y; y++) {
			//Draw boarder/frame
			if(y < thickness || y > (size.y - thickness - 1)) {
				//Draw top and bottom boarder
				TFT_Data(frameColor.blue << 2);
				TFT_Data(frameColor.green << 2);
				TFT_Data(frameColor.red << 2);
			}
			else if(x < thickness || x > (size.x - thickness - 1)) {
				//Draw left and right boarder
				TFT_Data(frameColor.blue << 2);
				TFT_Data(frameColor.green << 2);
				TFT_Data(frameColor.red << 2);
			}
			else if(y > (textOffsetY - 1) && y < (textOffsetY + 12*fontSize) && x > (textOffsetX - 1) && x < (textOffsetX + textLength)) {
				//Draw text
				if((((font[(text[indexString]-32)][indexCharY]) & ( 1 << indexChar )) >> indexChar) == 1) {
					TFT_Data(textColor.blue << 2);
					TFT_Data(textColor.green << 2);
					TFT_Data(textColor.red << 2);
				}
				else {
					TFT_Data(backgroundColor.blue << 2);
					TFT_Data(backgroundColor.green << 2);
					TFT_Data(backgroundColor.red << 2);
				}

				ty += 1;
				if(ty == fontSize) {
					indexCharY += 1;
					ty = 0;
				}

				if(indexCharY >= 12) {
					indexCharY = 0;
					ty = 0;
					tx += 1;
					if(tx == fontSize) {
						indexChar += 1;
						tx = 0;
					}
					if(indexChar > 7) {
						indexChar = 0;
						indexString += 1;
					}
				}
			}
			else {
				//Draw filling
				TFT_Data(backgroundColor.blue << 2);
				TFT_Data(backgroundColor.green << 2);
				TFT_Data(backgroundColor.red << 2);
			}
		}
	}
}
