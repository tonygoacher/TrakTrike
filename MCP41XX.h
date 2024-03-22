#pragma once

#include "INoneVolatilePot.h"
#include <SoftSPI.h>


class MCP41XX : public INoneVolatilePot
{
public:
	MCP41XX(SoftSPI* spi, int csPin);

	void Init() override;
	void SetWiper(int wiperValue) override;
	void SetDefaultWiper(int wiperValue) override;

protected:
	SoftSPI* m_spi;
	int m_csPin;
	
	static const byte WRITE_DATA = 0b0000;
	static const byte WIPER_VOLATILE_ADDDRESS = 0b00000000;
	static const byte WIPER_NONE_VOLATILE_ADDDRESS = 0b00000010;

	static const int m_maxValue = 511;

};
