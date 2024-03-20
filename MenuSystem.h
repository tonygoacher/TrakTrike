#pragma once

#include <Arduino.h>

#include "System.h"

enum MenuResult
{
	NoAction,
	GoPressed,
	SetPressed,
	ExitPressed,
};

typedef  void (*MenuFunction)(void* param) ;

struct MenuItem
{
	const char* menuItemName;
	MenuFunction menuFunction;
	void* parameter;
};

#define MAX_MENU_ITEMS	5
struct Menu
{
	uint8_t	numberOfSelections;
	uint32_t	currentSelection;
	SystemConfig* system;
	const char* const topLine;
	MenuItem menuItems[MAX_MENU_ITEMS];
};

void MenuContinue(Menu* menu);

void MenuInit(Menu* menu);

MenuResult MenuPump(Menu* menu);
