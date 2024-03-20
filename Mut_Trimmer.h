#pragma once

#include "Motors.h"



void mutTrimmer(struct Motors*, struct MotorOutput*);
void initTrimValue();
void setTrimValue(int newValue);
int getTrimValue();
