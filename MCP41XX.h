#pragma once

#include "IDigitalPot.h"
#include <SoftSPI.h>


class MCP41XX 
{
public:
	MCP41XX(SoftSPI* spi, byte csPin, byte wiperAddress);

	void Init() ;
	void SetWiper(int wiper1, int wiper2);

protected:
	SoftSPI* m_spi;
	byte m_csPin;
	byte m_wiperAddress;
	
	static const byte WRITE_DATA = 0b0000;

	static const int m_maxValue = 511;

};
