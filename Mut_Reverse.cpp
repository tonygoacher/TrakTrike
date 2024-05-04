#include <Arduino.h>


#include "Mut_Reverse.h"
#include "System.h"
#include "Configuration.h"

extern SystemConfig systemConfig;

void mutReverse(struct Motors* motors, struct MotorOutput* motorSpeeds)
{
	if (!digitalRead(systemConfig.reverseSwitchPort))
	{
		int maxValue = (Configuration::instance()->getConfiguration()->minThrottle * 120) / 100;
		if (motorSpeeds->m1Speed > maxValue || motorSpeeds->m2Speed > maxValue)
		{
			motorSpeeds->m1Speed = maxValue;
			motorSpeeds->m2Speed = maxValue;
		}
	}

}