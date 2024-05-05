
#include <Arduino.h>

#include "System.h"

#include "Motors.h"
#include "Mut_Trimmer.h"
#include "Configuration.h"
#include "Mut_Throttle.h"


extern SystemConfig systemConfig;

// Displays the trim value as -100.0 to +100.0. Zero trim is 1000
static int showValue(const char *text)
{
	int throttleValue = analogRead(THROTTLE_PIN);
	systemConfig.lcd->setCursor(0, 0);
	char value[18];
	systemConfig.lcd->print(text);

	systemConfig.lcd->setCursor(0, 1);
	sprintf(value, "Value: %04d     ",throttleValue);
	systemConfig.lcd->print(value);
	return throttleValue;
}

void setThrottleRange(const char *header, int* valueContainer)
{
	int oldValue = *valueContainer;
	int value = showValue(header);
	do
	{
	  value = showValue(header);
	} while (!systemConfig.encoderSwitch->Pressed());

	if (oldValue != value)
	{
		*valueContainer = value;
		Configuration::instance()->writeConfiguration();
	}
}

void setMinValue(void* param)
{
	setThrottleRange("     Set Min    ", &Configuration::instance()->getConfiguration()->minThrottle);
}

void setMaxValue(void* param)
{
	setThrottleRange("     Set Max    ", &Configuration::instance()->getConfiguration()->maxThrottle);
}