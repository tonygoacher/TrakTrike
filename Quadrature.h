#pragma once
#include <Arduino.h>
class Encoder;

class Quadrature
{
public:
	enum QuadMode
	{
		SimpleIncrement,
		Wrap,
	};

	Quadrature(Encoder* encoder);
	void Init(uint32_t* value, int32_t min, int32_t  max, uint16_t step, QuadMode mode);
	bool Update();
	void Detach();
	void SetFilter(uint8_t newFilter);
private:
	Encoder* m_Encoder;
	uint32_t* m_TheValue;
	int32_t	m_InternalValue;
	int32_t	m_Max;
	int32_t	m_Min;
	uint16_t	m_Step;
	long		m_LastPos;
	unsigned long		m_Filter;
	Quadrature::QuadMode	m_Mode;

	uint8_t m_FilterValue;
	static const uint32_t m_DefaultFilterValue = 10;
};
