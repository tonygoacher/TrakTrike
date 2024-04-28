#pragma once

#include "Arduino.h"
#include "Motors.h"
#include "Mut_Throttle.h"
#include "Mut_Trimmer.h"
#include "Mut_Scalar.h"
#include "System.h"

extern SystemConfig systemConfig;

struct Motors m;
struct MotorOutput motorSpeeds;

void initMotors()
{
	memset(m.motorSpeedMutators, 0, sizeof(m.motorSpeedMutators));
	m.motorSpeedMutators[0] = &mutThrottle;
	m.motorSpeedMutators[1] = &mutScalar;
	m.motorSpeedMutators[2] = &mutTrimmer;
}

int limitValue(int speed)
{
	if (speed < Configuration::instance()->getConfiguration()->minThrottle)
	{
		speed = Configuration::instance()->getConfiguration()->minThrottle;
	}

	if (speed > Configuration::instance()->getConfiguration()->maxThrottle)
	{
		speed = Configuration::instance()->getConfiguration()->maxThrottle;
	}
	return (int)map(speed, 
			Configuration::instance()->getConfiguration()->minThrottle,
		Configuration::instance()->getConfiguration()->maxThrottle,
		0,
		511);
}

void runMotors()
{

	int mutatorIndex = 0;
	while (m.motorSpeedMutators[mutatorIndex] != NULL)
	{
		m.motorSpeedMutators[mutatorIndex](&m, &motorSpeeds);
		mutatorIndex++;
	}

	Serial.print(motorSpeeds.m1Speed);
	Serial.print("  ");
	Serial.println(motorSpeeds.m2Speed);

	systemConfig.left->SetWiper(motorSpeeds.m1Speed);


	systemConfig.right->SetWiper(motorSpeeds.m2Speed);
	return;
}