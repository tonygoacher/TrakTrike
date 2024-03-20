#pragma once

#include "IDigitalPot.h"

class INoneVolatilePot : public IDigitalPot
{
public: 
	virtual void SetDefaultWiper(int defaultWiper) = 0;
};