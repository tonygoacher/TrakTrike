#include <arduino.h>
#include "Mut_Trimmer.h"
#include "Motors.h"
#include "Configuration.h"



static  int trimValue = 0;

int getTrimValue()
{
	return trimValue;
}

void initTrimValue()
{
	trimValue = Configuration::instance()->getConfiguration()->trimValue;
}

void mutTrimmer(struct Motors* motors, struct MotorOutput* motorOutput)
{

	long newMotor;
	long trim = 1000 - abs(trimValue);
	
	if (trimValue < 0)
	{
		newMotor = motorOutput->m1Speed;
	}
	else
	{
		newMotor = motorOutput->m2Speed;
	}

	newMotor *= trim;
	newMotor /= 1000;

	if (trimValue < 0)
	{
		motorOutput->m1Speed = newMotor;
	}
	else
	{
		motorOutput->m2Speed = newMotor;
	}

}

void setTrimValue(int newTrimValue)
{
	trimValue = newTrimValue;
}