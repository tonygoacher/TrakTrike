#include <Arduino.h>


#include "Mut_Throttle.h"

void mutThrottle(struct Motors* motors, struct MotorOutput* motorSpeeds)
{
	unsigned int value = analogRead(THROTTLE_PIN);
	motorSpeeds->m1Speed = value;
	motorSpeeds->m2Speed = value;

}