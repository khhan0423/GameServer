#include "pch.h"
#include "SendBuffer.h"

SendBuffer::SendBuffer(__int32 bufferSize)
{
	_buffer.resize(bufferSize);
}

SendBuffer::~SendBuffer()
{

}

void SendBuffer::CopyData(void* data, __int32 len)
{
	ASSERT(Capacity() >= len);
	::memcpy(_buffer.data(), data, len);
	_writeSize = len;
}