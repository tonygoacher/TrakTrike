
#include <Arduino.h>
#include "Quadrature.h"
#include "LiquidCrystal_I2C.h"
#include "System.h"
#include "MenuSystem.h"




#define QUAD_FILTER	200


static void ShowCurrentSelection(Menu* menu)
{
	menu->system->lcd->clear();
	if (menu->topLine != NULL)
	{
		menu->system->lcd->setCursor(0, 0);
		menu->system->lcd->print(menu->topLine);
	}
	menu->system->lcd->setCursor(0, 1);
	menu->system->lcd->print(menu->menuItems[menu->currentSelection].menuItemName);
}

void MenuContinue(Menu* menu)
{

	menu->system->quadrature->Init(&menu->currentSelection, 0, menu->numberOfSelections - 1, 1, Quadrature::Wrap);
	menu->system->quadrature->SetFilter(QUAD_FILTER);
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
	
	if (menu->system->quadrature->Update())
	{
		ShowCurrentSelection(menu);
	}
	
	return result;
}

