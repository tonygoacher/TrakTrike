#pragma once

#include "IConfiguration.h"

#define CONFIGURATION_STORE_SIZE	512
#define CURRENT_VERSION	2	



class Configuration : public  IConfiguration
{
public:
	static Configuration* instance();
	void init() override;
	CONFIGURATION_TYPE* getConfiguration() override;
	void writeConfiguration();
private:
	Configuration();
	uint16_t getChecksum();
	bool isDataValid();
	void setChecksum();
	void getStoredData();
	CONFIGURATION_TYPE m_theConfiguration;
};
