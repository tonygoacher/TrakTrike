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

struct ConfigurationV3
{
	int	version;
	int trimValue;
	int scalarValue;
	int minThrottle;
	int maxThrottle;
	uint16_t csum;
};

#define CONFIGURATION_TYPE	ConfigurationV3

class IConfiguration
{
public:

	virtual void init() = 0;
	
	virtual CONFIGURATION_TYPE* getConfiguration() = 0;
};
