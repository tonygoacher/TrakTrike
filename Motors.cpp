#pragma once

#include "Arduino.h"
#include "Motors.h"
#include "Mut_Throttle.h"
#include "Mut_Trimmer.h"
#include "Mut_Scalar.h"
#include "System.h"
#include "Mut_Reverse.h"

extern SystemConfig systemConfig;

struct Motors m;
struct MotorOutput motorSpeeds;

void initMotors()
{
	memset(m.motorSpeedMutators, 0, sizeof(m.motorSpeedMutators));
	m.motorSpeedMutators[0] = &mutThrottle;
	m.motorSpeedMutators[1] = &mutScalar;
//	m.motorSpeedMutators[1] = &mutTrimmer;
	m.motorSpeedMutators[2] = &mutReverse;
}


void runMotors()
{

	int mutatorIndex = 0;
	while (m.motorSpeedMutators[mutatorIndex] != NULL)
	{
		m.motorSpeedMutators[mutatorIndex](&m, &motorSpeeds);
		mutatorIndex++;
	}

	systemConfig.left->SetWiper(motorSpeeds.m1Speed, motorSpeeds.m2Speed);
	return;
}