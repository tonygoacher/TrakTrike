#include "MCP41XX.h"



MCP41XX::MCP41XX(SoftSPI* spi, int csPin)
{
	m_spi = spi;
	m_csPin = csPin;
}



void MCP41XX::Init()
{
	pinMode(m_csPin, OUTPUT);
	digitalWrite(m_csPin, HIGH);
	m_spi->setClockDivider(SPI_CLOCK_DIV32);
	m_spi->setDataMode(SPI_MODE1);
	m_spi->begin();
}

void MCP41XX::SetWiper(int wiperValue)
{
	digitalWrite(m_csPin, LOW);
	m_spi->transfer(WIPER_VOLATILE_ADDDRESS + WRITE_DATA + (wiperValue & 0x100 ? 1 : 0));
	m_spi->transfer(wiperValue & 0xff);
	digitalWrite(m_csPin, HIGH);

}

void MCP41XX::SetDefaultWiper(int wiperValue)
{
	digitalWrite(m_csPin, LOW);
	m_spi->transfer(WIPER_NONE_VOLATILE_ADDDRESS + WRITE_DATA + (wiperValue & 0x100 ? 1 : 0));
	m_spi->transfer(wiperValue & 0xff);
	digitalWrite(m_csPin, HIGH);

}