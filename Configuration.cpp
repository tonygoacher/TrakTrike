
#include <EEPROM.h>
#include <Arduino.h>
#include "Configuration.h"


Configuration::Configuration()
{
	init();
 }


Configuration* Configuration::instance()
{
	static Configuration configuration;
	return &configuration;
}


uint16_t Configuration::getChecksum()
{
	uint16_t csum = 0;
	uint8_t* data = (uint8_t*)&m_theConfiguration;
	for (int i = 0; i < offsetof(ConfigurationV2, csum); i++)
	{
		csum += *data++;
	}

	return csum;
}

bool Configuration::isDataValid()
{
	uint16_t csum = getChecksum();
	return csum == m_theConfiguration.csum && m_theConfiguration.version == CURRENT_VERSION;
}

void Configuration::setChecksum()
{
	uint16_t	csum = 0;
	csum = getChecksum();
	m_theConfiguration.csum = csum;
}


void Configuration::init()
{

	getStoredData();
	if (isDataValid() == false)
	{
		memset(&m_theConfiguration, 0, sizeof(m_theConfiguration));
		m_theConfiguration.trimValue = 0;
		m_theConfiguration.scalarValue = 620;
		m_theConfiguration.version = CURRENT_VERSION;
		writeConfiguration();
	}
}

void Configuration::getStoredData()
{

	EEPROM.get(0, m_theConfiguration);
}

ConfigurationV2* Configuration::getConfiguration()
{
	return &m_theConfiguration;
}

void Configuration::writeConfiguration()
{
	setChecksum();
	EEPROM.put(0, m_theConfiguration);
}