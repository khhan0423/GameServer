#include "pch.h"
#include "IOCPCore.h"
#include "IOCPEvent.h"

IocpCore::IocpCore()
{
	//CreateIoCompletionPort ó������ ������.
	_iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	ASSERT(_iocpHandle != INVALID_HANDLE_VALUE);
}

IocpCore::~IocpCore()
{
	::CloseHandle(_iocpHandle);
}

bool IocpCore::Register(shared_ptr<IocpObject> iocpObject)
{
	//������, CreateIoCompletionPort�� IocpCore �������̽��� ��ӹ���
	//CompletionPort�� ���� �������� ��ü���� �����.
	//_iocpHandle�� iocpObject->GetHandle()�� �����ϰڴٴ� �ǹ�.
	return ::CreateIoCompletionPort(iocpObject->GetHandle(), _iocpHandle, 0, 0);
}

bool IocpCore::Dispatch(unsigned __int32 timeout)
{
	DWORD numOfBytes = 0;
	ULONG_PTR key = 0;
	IocpEvent* iocpEvent = nullptr;

	if (::GetQueuedCompletionStatus(_iocpHandle, OUT & numOfBytes, OUT & key, OUT reinterpret_cast<LPOVERLAPPED*>(&iocpEvent), timeout))
	{
		shared_ptr<IocpObject> iocpObject = iocpEvent->owner;
		iocpObject->Dispatch(iocpEvent, numOfBytes);
	}
	else
	{
		__int32 errCode = ::WSAGetLastError();
		switch (errCode)
		{
		case WAIT_TIMEOUT:
			return false;
		default:

			shared_ptr<IocpObject> iocpObject = iocpEvent->owner;
			iocpObject->Dispatch(iocpEvent, numOfBytes);
			break;
		}
	}

	return true;
}
