#include "pch.h"
#include "RecvBuffer.h"

RecvBuffer::RecvBuffer(__int32 bufferSize) : _bufferSize(bufferSize)
{
	//��m_readPos
	//[0][0][0][0][0][0][0][0][0][0][0][0][0]......
	//��m_writePos

	_capacity = bufferSize * BUFFER_COUNT;
	_buffer.resize(_capacity);
}

RecvBuffer::~RecvBuffer()
{
}

void RecvBuffer::Clean()
{
	__int32 dataSize = DataSize();
	if (dataSize == 0)
	{
		//Clean case 1
		//            
		//            ��m_readPos
		//[x][x][x][x][x][x][x][x][x][0][0][0][0]......
		//            ��m_writePos
		_readPos = _writePos = 0;

	}
	else
	{
		if (FreeSize() < _bufferSize)
		{
			//Clean case 2
			//            
			//            ��m_readPos
			//[x][x][0][0][0][x][x][d][x][x][x][x][x]
			//                     ��m_writePos
			//            
			//��m_readPos
			//[0][x][x][d][0][x][x][d][x][x][x][x][x]
			//          ��m_writePos

			::memcpy(&_buffer[0], &_buffer[_readPos], dataSize);
			_readPos = 0;
			_writePos = dataSize;
		}
	}
}

bool RecvBuffer::OnRead(__int32 numOfBytes)
{
	//OnRead  : DataSize = m_writePos - m_readPos
	//        : FreeSize = m_capacity - m_writePos
	//         ��m_readPos
	//[x][x][x][x][x][x][x][x][x][x][x][0][0]......
	//               ��m_writePos

	if (numOfBytes > DataSize())
		return false;

	_readPos += numOfBytes;
	return true;
}

bool RecvBuffer::OnWrite(__int32 numOfBytes)
{
	//OnWrite : DataSize = m_writePos - m_readPos
	//        : FreeSize = m_capacity - m_writePos
	//��m_readPos
	//[x][x][x][x][x][x][x][x][x][x][x][x][x]......
	//            ��m_writePos
	if (numOfBytes > FreeSize())
		return false;

	_writePos += numOfBytes;
	return true;
}