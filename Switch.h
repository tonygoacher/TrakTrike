#pragma once

class Switch
{
public:
	Switch();
	void Init(uint8_t port);
	bool Pressed();
private:
	unsigned long m_Timer;
	uint8_t m_Port;
	static const unsigned long sm_DebounceTime = 40;
	enum SwitchState
	{
		OFF,
		PRESSED,
		PRESSED_HOLD,
		OFF_HOLD,
	};

	SwitchState	m_SwitchState;

	unsigned long Elapsed();
	bool ReadPort();
	void SetTimer();

};