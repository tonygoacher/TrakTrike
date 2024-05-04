#include <Arduino.h>


#include "Mut_Throttle.h"
#include "Configuration.h"

void mutThrottle(struct Motors* motors, struct MotorOutput* motorSpeeds)
{
	unsigned int value = analogRead(THROTTLE_PIN);
	if (value > Configuration::instance()->getConfiguration()->maxThrottle)
	{
		value = Configuration::instance()->getConfiguration()->maxThrottle;
	}

	if (value < Configuration::instance()->getConfiguration()->minThrottle)
	{
		value = Configuration::instance()->getConfiguration()->minThrottle;
	}

	motorSpeeds->m1Speed = value;
	motorSpeeds->m2Speed = value;

}