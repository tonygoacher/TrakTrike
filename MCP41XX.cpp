#include "MCP41XX.h"



MCP41XX::MCP41XX(SoftSPI* spi, byte csPin, byte wiperAddress)
{
	m_spi = spi;
	m_csPin = csPin;
	m_wiperAddress = wiperAddress;
}


void MCP41XX::Init()
{
	pinMode(m_csPin, OUTPUT);
	digitalWrite(m_csPin, HIGH);
	m_spi->setClockDivider(SPI_CLOCK_DIV32);
	m_spi->setDataMode(SPI_MODE0);
	m_spi->begin();
}

void MCP41XX::SetWiper( int value1, int value2)
{
	if (value1 > m_maxValue)
	{
		value1 = m_maxValue;
	}

	if (value2 > m_maxValue)
	{
		value2 = m_maxValue;
	}

	digitalWrite(m_csPin, LOW);
	Serial.println(value2);
	m_spi->transfer(0b00000000 + WRITE_DATA + (value1 & 0x100 ? 1 : 0));
	m_spi->transfer(value1 & 0xff);

	m_spi->transfer(0b00010000 + WRITE_DATA + (value2 & 0x100 ? 1 : 0));
	m_spi->transfer(value2 & 0xff);





	digitalWrite(m_csPin, HIGH);

}

