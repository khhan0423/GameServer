#pragma once
#include <vector>


class SendBuffer : std::enable_shared_from_this<SendBuffer>
{
public:
	SendBuffer(__int32 bufferSize);
	~SendBuffer();

	BYTE*			GetBuffer() { return m_buffer.data(); }
	__int32			GetWriteSize() { return m_writeSize; }
	__int32			GetCapacity() { return static_cast<__int32>(m_buffer.size()); }

	void			CopyData(void* data, __int32 len);
	void			Close(__int32 writeSize);

private:
	std::vector<BYTE>	m_buffer;
	__int32			m_writeSize = 0;
};
