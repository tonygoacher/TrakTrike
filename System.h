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
	MCP41XX* left;
	MCP41XX* right;
};


