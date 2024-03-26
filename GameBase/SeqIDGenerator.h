#pragma once
#include <mutex>

class SeqIDGenerator
{
private:
	std::atomic<unsigned long long> m_GUID = 0;
public:
	SeqIDGenerator() {}
	unsigned __int64 Generate()
	{
		return m_GUID.fetch_add(1);
	}
};