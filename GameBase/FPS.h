#pragma once
class FPS
{
public:
	FPS()
	{
		m_fPS = 0;
		m_count = 0;
		m_lastTime = GetTickCount64();
	}
	bool Update()
	{
		unsigned __int64 _curTime = GetTickCount64();
		if (_curTime - m_lastTime <= 1000)
		{
			m_count++;
			return false;
		}

		m_fPS = m_count;
		m_count = 0;
		m_lastTime = _curTime;

		return true;
	}
	int						GetFPS() const { return m_fPS; }

private:
	__int32					m_fPS;
	__int32					m_count;
	unsigned __int64		m_lastTime;
};

