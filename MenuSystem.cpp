
#include <Arduino.h>
#include <AiAvrRotaryEncoder.h>
#include "LiquidCrystal_I2C.h"
#include "System.h"
#include "MenuSystem.h"

/*
m_rotaryEncoder->begin();
m_rotaryEncoder->setEncoderValue(0);
m_rotaryEncoder->setup(encoderCallback);
m_rotaryEncoder->setBoundaries(-1000, 1000, false); //minValue, maxValue, circleValues true|false (when max go to min and vice versa)
m_rotaryEncoder->setAcceleration(100);
m_rotaryEncoder->enable();
*/


static void ShowCurrentSelection(Menu* menu)
{
	menu->system->lcd->clear();
	if (menu->topLine != NULL)
	{
		menu->system->lcd->setCursor(0, 0);
		menu->system->lcd->print(menu->topLine);
	}
	menu->system->lcd->setCursor(0, 1);
	menu->currentSelection = menu->system->quadrature->readEncoder();
	menu->system->lcd->print(menu->menuItems[menu->currentSelection].menuItemName);
}

void MenuContinue(Menu* menu)
{
	menu->system->quadrature->disable();
	menu->system->quadrature->setEncoderValue(menu->currentSelection);
	menu->system->quadrature->setBoundaries(0, menu->numberOfSelections - 1, true);
	menu->system->quadrature->setAcceleration(0);
	menu->system->quadrature->enable();

	ShowCurrentSelection(menu);
}

void MenuInit(Menu* menu)
{
	menu->currentSelection = 0;

	MenuContinue(menu);
}



MenuResult MenuPump(Menu* menu)
{
	MenuResult result = NoAction;

	if (menu->system->encoderSwitch->Pressed())
	{
		result = GoPressed;
	}
	
	if (menu->system->quadrature->encoderChanged())
	{
		ShowCurrentSelection(menu);
	}
	
	return result;
}

