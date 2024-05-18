
#include "MenuSystem.h"
#include "System.h"
#include "MainMenu.h"
#include "Motors.h"
#include "SettingsMenu.h"
#include "TrimFunction.h"
#include "ScalarFunction.h"
#include "setThrottleRange.h"
#include "showValues.h"
#include "setMaxOutput.h"


extern SystemConfig systemConfig;


extern void MainMenu(Menu* menu);

Menu settingsMenuConfig =
{
	5
	,		// Number of menu items
	0,
	&systemConfig,
	false,				// Do not run motors during this menu
	" Settings Menu  ",
	{

		{"Trim         ",	(void(*)(void*))TrimFunction,NULL},
		{"Throttle Min ",	(void(*)(void*))setMinValue,NULL},
		{"Throttle Max ",	(void(*)(void*))setMaxValue,NULL},
		{"Set Max Outpt",   (void(*)(void*))setMaxOutput,NULL},
		{"Exit         ",NULL,NULL},
	//	{NULL,NULL,NULL}
	}
};

Menu mainMenuConfig =
{
	2,
	0,	// INitial menu index
	&systemConfig,
	true,				// Run motors during this menu
	"   Trak Trike   ",
	{	{"Settings        ",(void(*)(void*))MainMenu, (void*)&settingsMenuConfig},
		{"Show Values     ",(void(*)(void*))showValues, (void*)&settingsMenuConfig},
	//	{NULL,NULL,NULL},
	},
};






void MainMenu(Menu* menu)
{
	MenuInit(menu);

	while (systemConfig.encoderSwitch->Pressed())
	{
		runMotors(false);
	}
	while (1)
	{
	
		if (MenuPump(menu) == MenuResult::GoPressed)
		{
			if (menu->currentSelection < menu->numberOfSelections)
			{
				if (menu->menuItems[menu->currentSelection].menuFunction != NULL)
				{
					menu->menuItems[menu->currentSelection].menuFunction(menu->menuItems[menu->currentSelection].parameter);
					MenuContinue(menu);
					
				}
				else
				{ 
					return;
				}
			}
		}
		delay(50);
		if (menu->runMotors)
		{
			runMotors(false);
		}
        
	}
}


