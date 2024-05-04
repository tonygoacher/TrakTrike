
#include "MenuSystem.h"
#include "System.h"
#include "MainMenu.h"
#include "Motors.h"
#include "SettingsMenu.h"
#include "TrimFunction.h"
#include "ScalarFunction.h"
#include "setThrottleRange.h"


extern SystemConfig systemConfig;


extern void MainMenu(Menu* menu);

Menu settingsMenuConfig =
{
	5,
	0,
	&systemConfig,
	" Settings Menu  ",
	{


		{"Throttle Min ",	(void(*)(void*))setMinValue,NULL},
		{"Throttle Max ",	(void(*)(void*))setMinValue,NULL},


		{"Exit         ",NULL,NULL},
	//	{NULL,NULL,NULL}
	}
};

Menu mainMenuConfig =
{
	2,
	0,	// INitial menu index
	&systemConfig,
	"   Trak Trike   ",
	{	{"Settings        ",(void(*)(void*))MainMenu, (void*)&settingsMenuConfig},
		{"Menui2          ",(void(*)(void*))MainMenu, (void*)&settingsMenuConfig},
	//	{NULL,NULL,NULL},
	},
};






void MainMenu(Menu* menu)
{
	MenuInit(menu);

	while (systemConfig.encoderSwitch->Pressed())
	{
		runMotors();
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
        runMotors();
	}
}


