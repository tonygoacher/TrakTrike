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
bool showingValues = false;

void initMotors()
{
	memset(m.motorSpeedMutators, 0, sizeof(m.motorSpeedMutators));
	m.motorSpeedMutators[0] = &mutThrottle;
	//m.motorSpeedMutators[1] = &mutScalar;
 	m.motorSpeedMutators[1] = &mutTrimmer;

}

int m1Last = 0xffff;
int m2Last = 0xffff;

void displayCurrentMotorValues()
{


		if (motorSpeeds.m1Speed != m1Last || motorSpeeds.m2Speed != m2Last)
		{
			m1Last = motorSpeeds.m1Speed;
			m2Last = motorSpeeds.m2Speed;
			systemConfig.lcd->setCursor(0, 1);
			char text[17];
			sprintf(text, "%03d   %d     %03d", motorSpeeds.m1Speed, digitalRead(systemConfig.reverseSwitchPort), motorSpeeds.m2Speed);
			//sprintf(text, "%d", Configuration::instance()->getConfiguration()->trimValue);
			systemConfig.lcd->print(text);
		}
}

void runMotors(bool displayValues)
{
	if (!showingValues && displayValues)
	{
		m1Last = 0xffff;
		m2Last = 0xffff;
		showingValues = true;
	}

	if (showingValues && !displayValues)
	{
		showingValues = false;
	}

	int mutatorIndex = 0;
	while (m.motorSpeedMutators[mutatorIndex] != NULL)
	{
		m.motorSpeedMutators[mutatorIndex](&m, &motorSpeeds);
		mutatorIndex++;
	}

	if (displayValues)
	{
		displayCurrentMotorValues();
	}

	systemConfig.left->SetWiper(motorSpeeds.m1Speed, motorSpeeds.m2Speed);
	return;
}