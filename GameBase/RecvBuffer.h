#pragma once
#include <vector>
class RecvBuffer
{
	enum { BUFFER_COUNT = 10 };

public:
	RecvBuffer(__int32 bufferSize);
	~RecvBuffer();

	void				Clean();
	bool				OnRead(__int32 numOfBytes);
	bool				OnWrite(__int32 numOfBytes);

	BYTE*				GetReadPos() { return &m_buffer[m_readPos]; }
	BYTE*				GetWritePos() { return &m_buffer[m_writePos]; }
	__int32				GetDataSize() { return m_writePos - m_readPos; }
	__int32				GetFreeSize() { return m_capacity - m_writePos; }

private:
	__int32				m_capacity = 0;
	__int32				m_bufferSize = 0;
	__int32				m_readPos = 0;
	__int32				m_writePos = 0;
	vector<BYTE>		m_buffer;
};


