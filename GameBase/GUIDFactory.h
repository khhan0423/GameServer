#pragma once
#include <mutex>

class GUIDFacroty
{
private:
	atomic<unsigned long long> m_GUID = 0;
public:
	GUIDFacroty() {}
	unsigned __int64 Generate()
	{
		return m_GUID.fetch_add(1);
	}
};

