
#include <Arduino.h>

#include "Quadrature.h"

#include "Encoder.h"


Quadrature::Quadrature(Encoder* encoder)
{
	
	m_Encoder = encoder;
	m_TheValue = NULL;
	m_FilterValue = m_DefaultFilterValue;
	for (int i = 0; i < 2000; i++)
	{
		encoder->read();
	}
}

void Quadrature::SetFilter(uint8_t newFilter)
{
	m_FilterValue = newFilter;
}

void Quadrature::Init(uint32_t* value, int32_t min, int32_t max, uint16_t step, Quadrature::QuadMode mode)
{
	m_TheValue = value;
	m_InternalValue = *m_TheValue;
	m_Max = max;
	m_Min = min;
	m_Step = step;
	m_LastPos = 0;

	m_Filter = 0;
	m_Mode = mode;
	m_Filter = millis() + m_FilterValue;
}

bool Quadrature::Update()
{
	bool changed = false;
	if (m_TheValue == NULL)
	{
		return false;
	}



	long newPos = m_Encoder->read();

	if (m_Filter > millis())
	{
		m_LastPos = newPos;
		return false;
	}

	if (newPos != m_LastPos)
	{
		changed = true;
		long delta = newPos - m_LastPos;
		int change = m_Step;
		if (delta < 0)
		{
			change = -change;
		}
		if (m_InternalValue + change < m_Min)
		{
			if (m_InternalValue + change < m_Min && m_Mode == Quadrature::Wrap)
			{
				m_InternalValue = m_Max;
			}
			else
			{
				m_InternalValue = m_Min;
			}
		}
		else
		{
			if (m_InternalValue + change > m_Max)
			{
				if (m_InternalValue + change > m_Max && m_Mode == Quadrature::Wrap)
				{
					m_InternalValue = m_Min;
				}
				else
				{
					m_InternalValue = m_Max;
				}
			}
			else
			{
				m_InternalValue += change;
			}
		}
		if (m_InternalValue < m_Min)
		{
			m_InternalValue = m_Min;
		}

		if (m_InternalValue > m_Max)
		{
			m_InternalValue = m_Max;
		}
	
		*m_TheValue = (uint32_t)m_InternalValue;

		m_LastPos = newPos;
		changed = true;
		m_Filter = millis() + m_FilterValue;
	}
	return changed;
}

void Quadrature::Detach()
{
	m_TheValue = NULL;
}
