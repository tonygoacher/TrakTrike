#pragma once



#include <Arduino.h>
#include "Motors.h"
#include "Configuration.h"



void mutScalar(struct Motors* motors, struct MotorOutput* motorOutput)
{
	long scalar = Configuration::instance()->getConfiguration()->scalarValue;
	motorOutput->m1Speed = (unsigned int)(((long)motorOutput->m1Speed * scalar) / 1000L);
	motorOutput->m2Speed = (unsigned int)(((long)motorOutput->m2Speed * scalar) / 1000L);

}

