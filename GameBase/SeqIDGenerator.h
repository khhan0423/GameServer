#pragma once
#include <mutex>
#include "SingletonBase.h"

#define SessionGUIDGen() SeqIDGenerator::GetInstance()

class SeqIDGenerator : public TSingletonBase<SeqIDGenerator>
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