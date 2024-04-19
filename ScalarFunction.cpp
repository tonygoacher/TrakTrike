
#include <Arduino.h>

#include "System.h"

#include "Motors.h"
#include "Mut_Trimmer.h"
#include "Configuration.h"
#include "Mut_Throttle.h"


extern SystemConfig systemConfig;

// Displays the trim value as -100.0 to +100.0. Zero trim is 1000
static void showScalarValue(uint32_t value)
{
	int throttleValue = analogRead(THROTTLE_PIN);
	systemConfig.lcd->setCursor(0, 0);
	char text[18];
	sprintf(text, "In:%04d         ", throttleValue);
	systemConfig.lcd->print(text);

	systemConfig.lcd->setCursor(0, 1);
	sprintf(text, "Out:%04d Sc:%04d", (int)(((uint32_t)throttleValue * value) / 1000L), (int)value);
	systemConfig.lcd->print(text);
}

void scalarFunction(void* param)
{
	uint32_t oldScalarValue =  Configuration::instance()->getConfiguration()->scalarValue;
	
	systemConfig.lcd->clear();
	uint32_t newScalarValue = oldScalarValue;
	// Quad can only use positive numbers so add 1000

	systemConfig.quadrature->setBoundaries(0, 1000, false);
	systemConfig.quadrature->setEncoderValue(oldScalarValue);
	systemConfig.quadrature->setAcceleration(5);

	showScalarValue(newScalarValue);
	int last = analogRead(THROTTLE_PIN);
	do
	{
		newScalarValue = systemConfig.quadrature->readEncoder();
		int throttleValue = analogRead(THROTTLE_PIN);
		if (systemConfig.quadrature->encoderChanged() || throttleValue != last)
		{	
			last = throttleValue;
			showScalarValue(newScalarValue);
		}
	}
	while (!systemConfig.encoderSwitch->Pressed());

	if (oldScalarValue != newScalarValue)
	{
		Configuration::instance()->getConfiguration()->scalarValue = newScalarValue;
		Configuration::instance()->writeConfiguration();
	}
}