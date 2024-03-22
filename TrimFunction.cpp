

#include "System.h"
#include "Motors.h"
#include "Mut_Trimmer.h"
#include "Configuration.h"


extern SystemConfig systemConfig;

// Displays the trim value as -100.0 to +100.0. Zero trim is 1000
static void showTrimValue(int value)
{
	systemConfig.lcd->setCursor(0, 1);
	char text[18];
	sprintf(text, "     %c%03d.%1d     ", 
		value < 0 ? '-' : ' ',
		abs(value / 10), abs(value % 10));
	systemConfig.lcd->print(text);
}

void TrimFunction(void* param)
{
	int oldTrimValue = Configuration::instance()->getConfiguration()->trimValue;

	systemConfig.lcd->clear();
	uint32_t displayTrimValue = getTrimValue();	// Trim value range is -1000.0 to +1000.0 but quad can onlu use positive numbers

	systemConfig.quadrature->setBoundaries(-1000, 1000, true);
	systemConfig.quadrature->setEncoderValue(displayTrimValue);
	systemConfig.quadrature->setAcceleration(5);

	systemConfig.lcd->print("      Trim      ");
	showTrimValue(displayTrimValue);
	int initialTrimValue = displayTrimValue;
	do
	{
		if (systemConfig.quadrature->encoderChanged())
		{
			displayTrimValue = systemConfig.quadrature->readEncoder();
			showTrimValue((int)displayTrimValue);
		}

		runMotors();
	} while (!systemConfig.encoderSwitch->Pressed());
	if (initialTrimValue != displayTrimValue)
	{
		Configuration::instance()->getConfiguration()->trimValue = displayTrimValue;
		Configuration::instance()->writeConfiguration();
	}
}