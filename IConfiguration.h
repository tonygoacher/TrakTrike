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

	int maxThrottle;
	int minThrottle;
	uint16_t csum;
};

#define CURRENT_VERSION	3
#define CURRENT_CONFIGURATION ConfigurationV3


class IConfiguration
{
public:

	virtual void init() = 0;
	
	virtual CURRENT_CONFIGURATION* getConfiguration() = 0;
};
