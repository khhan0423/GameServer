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

	BYTE*				ReadPos() { return &_buffer[_readPos]; }
	BYTE*				WritePos() { return &_buffer[_writePos]; }
	__int32				DataSize() { return _writePos - _readPos; }
	__int32				FreeSize() { return _capacity - _writePos; }

private:
	__int32				_capacity = 0;
	__int32				_bufferSize = 0;
	__int32				_readPos = 0;
	__int32				_writePos = 0;
	vector<BYTE>		_buffer;
};


