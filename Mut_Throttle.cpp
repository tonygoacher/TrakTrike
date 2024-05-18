#include <Arduino.h>


#include "Mut_Throttle.h"
#include "Configuration.h"

void mutThrottle(struct Motors* motors, struct MotorOutput* motorSpeeds)
{
	unsigned int value = analogRead(THROTTLE_PIN);
	int minValue = Configuration::instance()->getConfiguration()->minThrottle;
	int maxValue = Configuration::instance()->getConfiguration()->maxThrottle;

	/*Serial.print(value);
	Serial.print(" ");
	Serial.print(minValue);
	Serial.print(" ");
	Serial.print(maxValue);
	Serial.print(" ");*/

	value = constrain(value, minValue, maxValue);

	/*
	Serial.print(" ");
	Serial.print(value);*/

	value = map(value, minValue, maxValue, 0, Configuration::instance()->getConfiguration()->maxOutput);

	motorSpeeds->m1Speed = value;
	motorSpeeds->m2Speed = value;

}