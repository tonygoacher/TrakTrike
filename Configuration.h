#pragma once

#include "IConfiguration.h"

#define CONFIGURATION_STORE_SIZE	512
	

class Configuration : public  IConfiguration
{
public:
	static Configuration* instance();
	void init() override;
	CURRENT_CONFIGURATION* getConfiguration() override;
	void writeConfiguration();
private:
	Configuration();
	uint16_t getChecksum();
	bool isDataValid();
	void setChecksum();
	void getStoredData();
	CURRENT_CONFIGURATION m_theConfiguration;
};
