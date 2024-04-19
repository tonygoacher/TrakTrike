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
	m_spi->setDataMode(SPI_MODE1);
	m_spi->begin();
}

void MCP41XX::SetWiper( int wiperValue)
{
	if (wiperValue > m_maxValue)
	{
		wiperValue = m_maxValue;
	}
	digitalWrite(m_csPin, LOW);
	m_spi->transfer((m_wiperAddress << 4) + WRITE_DATA + (wiperValue & 0x100 ? 1 : 0));
	m_spi->transfer(wiperValue & 0xff);
	digitalWrite(m_csPin, HIGH);

}

