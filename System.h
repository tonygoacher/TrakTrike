#pragma once

#include "Quadrature.h"

#include <LiquidCrystal_I2C.h>
#include "Switch.h"
#include "IDigitalPot.h"
#include "Configuration.h"

struct SystemConfig
{
	LiquidCrystal_I2C* lcd;
	Quadrature* quadrature;
	Switch* encoderSwitch;
	IDigitalPot* left;
	IDigitalPot* right;
};


