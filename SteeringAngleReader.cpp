#include <Arduino.h>

#include "SteeringAngleReader.h"




SteeringAngleReader::SteeringAngleReader(int port, int range)
{
	m_port = port;
	m_range = range;
	pinMode(port, INPUT);
	m_scalar = 360 / range;
}


float SteeringAngleReader::GetAngleDegrees()
{
	float currentAngle = (float)analogRead(m_port);
	return  currentAngle * m_scalar;
}
