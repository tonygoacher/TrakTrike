#pragma once


#include "ISteeringAngle.h"



class SteeringAngleReader : public ISteeringAngle
{
public:
	SteeringAngleReader(int port, int range);
	float GetAngleDegrees() override;


private:
	int m_port;
	int m_range;
	float m_scalar;

};