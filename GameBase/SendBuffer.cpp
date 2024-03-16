#include "pch.h"
#include "SendBuffer.h"

SendBuffer::SendBuffer(__int32 bufferSize)
{
	m_buffer.resize(bufferSize);
}

SendBuffer::~SendBuffer()
{

}

void SendBuffer::CopyData(void* dataPtr, __int32 len)
{
	VERIFY(GetCapacity() >= len);
	::memcpy(m_buffer.data(), dataPtr, len);
	m_writeSize = len;
}

void SendBuffer::Close(__int32 writeSize)
{
	m_writeSize = writeSize;
}