#pragma once

#include "IConfiguration.h"

#define CONFIGURATION_STORE_SIZE	512
#define CURRENT_VERSION	2	

class Configuration : public  IConfiguration
{
public:
	static Configuration* instance();
	void init() override;
	ConfigurationV2* getConfiguration() override;
	void writeConfiguration();
private:
	Configuration();
	uint16_t getChecksum();
	bool isDataValid();
	void setChecksum();
	void getStoredData();
	ConfigurationV2 m_theConfiguration;
};
