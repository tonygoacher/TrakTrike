#pragma once

#define MAX_MUTATORS	5

// 1023 is 100% motor output



struct MotorOutput
{
	unsigned int m1Speed;
	unsigned int m2Speed;
};

typedef void (*motorSpeedMutator)(struct Motors*, struct MotorOutput*);

struct Motors
{
	motorSpeedMutator motorSpeedMutators[MAX_MUTATORS];
};

void initMotors();
void runMotors();

