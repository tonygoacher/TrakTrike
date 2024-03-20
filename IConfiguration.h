#pragma once


struct ConfigurationV1
{
	int	version;
	int trimValue;
	uint16_t csum;
};

struct ConfigurationV2
{
	int	version;
	int trimValue;
	int scalarValue;
	uint16_t csum;
};

class IConfiguration
{
public:

	virtual void init() = 0;
	
	virtual ConfigurationV2* getConfiguration() = 0;
};
