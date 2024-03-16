#pragma once
#include <vector>


class SendBuffer : enable_shared_from_this<SendBuffer>
{
public:
	SendBuffer(__int32 bufferSize);
	~SendBuffer();

	BYTE*			Buffer() { return _buffer.data(); }
	__int32			WriteSize() { return _writeSize; }
	__int32			Capacity() { return static_cast<__int32>(_buffer.size()); }

	void			CopyData(void* data, __int32 len);

private:
	vector<BYTE>	_buffer;
	__int32			_writeSize = 0;
};
