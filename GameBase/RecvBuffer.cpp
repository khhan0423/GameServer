#include "pch.h"
#include "RecvBuffer.h"

RecvBuffer::RecvBuffer(__int32 bufferSize) : m_bufferSize(bufferSize)
{
	//¡åm_readPos
	//[0][0][0][0][0][0][0][0][0][0][0][0][0]......
	//¡ãm_writePos

	m_capacity = bufferSize * BUFFER_COUNT;
	m_buffer.resize(m_capacity);
}

RecvBuffer::~RecvBuffer()
{
}

void RecvBuffer::Clean()
{
	__int32 _dataSize = GetDataSize();
	if (_dataSize == 0)
	{
		//Clean case 1
		//            
		//            ¡åm_readPos
		//[x][x][x][x][x][x][x][x][x][0][0][0][0]......
		//            ¡ãm_writePos
		m_readPos = m_writePos = 0;

	}
	else
	{
		if (GetFreeSize() < m_bufferSize)
		{
			//Clean case 2
			//            
			//            ¡åm_readPos
			//[x][x][0][0][0][x][x][d][x][x][x][x][x]
			//                     ¡ãm_writePos
			//            
			//¡åm_readPos
			//[0][x][x][d][0][x][x][d][x][x][x][x][x]
			//          ¡ãm_writePos

			::memcpy(&m_buffer[0], &m_buffer[m_readPos], _dataSize);
			m_readPos = 0;
			m_writePos = _dataSize;
		}
	}
}

bool RecvBuffer::OnRead(__int32 numOfBytes)
{
	//OnRead  : GetDataSize = m_writePos - m_readPos
	//        : GetFreeSize = m_capacity - m_writePos
	//         ¡åm_readPos
	//[x][x][x][x][x][x][x][x][x][x][x][0][0]......
	//               ¡ãm_writePos

	if (numOfBytes > GetDataSize())
		return false;

	m_readPos += numOfBytes;
	return true;
}

bool RecvBuffer::OnWrite(__int32 numOfBytes)
{
	//OnWrite : GetDataSize = m_writePos - m_readPos
	//        : GetFreeSize = m_capacity - m_writePos
	//¡åm_readPos
	//[x][x][x][x][x][x][x][x][x][x][x][x][x]......
	//            ¡ãm_writePos
	if (numOfBytes > GetFreeSize())
		return false;

	m_writePos += numOfBytes;
	return true;
}