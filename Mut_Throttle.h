#pragma once
#include "Motors.h"

#define THROTTLE_PIN A1

#define THROTTLE_MIN 185

void mutThrottle(struct Motors*, struct MotorOutput*);