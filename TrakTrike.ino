/*
 Name:		TrakTrike.ino
 Created:	12/13/2023 6:09:22 PM
 Author:	tgoacher
*/

// the setup function runs once when you press reset or power the board
#include <AiAvrRotaryEncoderNumberSelector.h>
#include <AiAvrRotaryEncoder.h>
#include <EEPROM.h>

#include <Arduino.h>
#include <math.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftSPI.h>
#include <SoftWire.h>
#include <Encoder.h>
#include "MCP41XX.h"
#include "IDigitalPot.h"
#include "Switch.h"
#include "System.h"
#include "Quadrature.h"
#include "MainMenu.h"
#include "Motors.h"


Motors motors;

#define _CS	9
#define MOSI    11
#define MISO    A7	// UNUSED!
#define SCK		10

#define SHUTDOWN 12

#define WIPER_LEFT_ADDRESS 0
#define WIPER_RIGHT_ADDRESS 1

#define LCD_ADDRESS 0x27//Define I2C Address where the PCF8574A is
#define LCD_COLOUMNS 16
#define LCD_ROWS	2

#define ENCODER_SWITCH	4
#define ENCODER_PIN1	2
#define ENCODER_PIN2	3



LiquidCrystal_I2C* lcd;

SystemConfig systemConfig;

SoftSPI spi(MOSI, MISO, SCK);
IDigitalPot* pLeft = NULL;
AiAvrRotaryEncoder encoder(ENCODER_PIN1, ENCODER_PIN2, -1 - 1, 1);

void encoderCallback()
{

	encoder.readEncoder_ISR();
}

void setup() 
{
	Serial.begin(115200);

	pinMode(MOSI, OUTPUT);
	digitalWrite(MOSI, HIGH);


	lcd = new LiquidCrystal_I2C(LCD_ADDRESS, LCD_COLOUMNS, LCD_ROWS);
	lcd->init();
	lcd->backlight();
	lcd->clear();
	lcd->print("    TrakTrike   ");
	systemConfig.encoderSwitch = new Switch();
	systemConfig.encoderSwitch->Init(ENCODER_SWITCH);
	systemConfig.quadrature = &encoder;
	systemConfig.lcd = lcd;
	systemConfig.left = new MCP41XX(&spi, _CS, WIPER_LEFT_ADDRESS);
	systemConfig.right = new MCP41XX(&spi, _CS, WIPER_RIGHT_ADDRESS);
	systemConfig.left->Init();
	systemConfig.right->Init();
	Serial.println("AAAAAAAA");

	pinMode(SHUTDOWN, OUTPUT);
	digitalWrite(SHUTDOWN, HIGH);


	initMotors();

	encoder.setup(encoderCallback);
}


int wiper = 0;
int dir = 1;

// the loop function runs over and over again until power down or reset
void loop()
{
	//Serial.print(dir++);
//	Serial.println();

	MainMenu(&mainMenuConfig);
	/*
	wiper+=dir;

	pLeft->SetWiper(wiper);
	if (wiper == 511 & dir == 1)
	{
		dir = -1;
	}
	else
	{
		if (wiper == 0 && dir == -1)
		{
			dir = 1;
		}
	}
	*/
	delay(100);

}
