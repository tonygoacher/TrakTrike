#pragma once

#include <AiAvrRotaryEncoder.h>

#include <LiquidCrystal_I2C.h>
#include "Switch.h"
#include "MCP41XX.h"
#include "Configuration.h"


struct SystemConfig
{
	LiquidCrystal_I2C* lcd;
	AiAvrRotaryEncoder* quadrature;
	Switch* encoderSwitch;
	int reverseSwitchPort;
	MCP41XX* left;
	bool showMotorValues;
};


