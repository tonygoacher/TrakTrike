#pragma once

#include <Arduino.h>


class IDigitalPot
{
public:
	virtual void Init() = 0;
	virtual void SetWiper(int wiperValue) = 0;
};