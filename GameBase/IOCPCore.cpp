#include "pch.h"
#include "IOCPCore.h"
#include "IOCPEvent.h"

IocpCore::IocpCore()
{
	//CreateIoCompletionPort ó������ ������.
	m_iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	VERIFY(m_iocpHandle != INVALID_HANDLE_VALUE);
}

IocpCore::~IocpCore()
{
	::CloseHandle(m_iocpHandle);
}

bool IocpCore::Register(shared_ptr<IocpObject> iocpObject)
{
	//������, CreateIoCompletionPort�� IocpCore �������̽��� ��ӹ���
	//CompletionPort�� ���� �������� ��ü���� �����.
	//_iocpHandle�� _iocpObject->GetHandle()�� �����ϰڴٴ� �ǹ�.
	return ::CreateIoCompletionPort(iocpObject->GetHandle(), m_iocpHandle, 0, 0);
}

bool IocpCore::Dispatch(unsigned __int32 timeout)
{
	DWORD _numOfBytes = 0;
	ULONG_PTR _key = 0;
	IocpEvent* _iocpEvent = nullptr;	

	if (::GetQueuedCompletionStatus(m_iocpHandle, OUT & _numOfBytes, OUT & _key, OUT reinterpret_cast<LPOVERLAPPED*>(&_iocpEvent), timeout))
	{
		shared_ptr<IocpObject> _iocpObject = _iocpEvent->m_owner;
		_iocpObject->Dispatch(_iocpEvent, _numOfBytes);
	}
	else
	{
		__int32 _errCode = ::WSAGetLastError();
		switch (_errCode)
		{
		case WAIT_TIMEOUT:
			return false;
		default:

			shared_ptr<IocpObject> _iocpObject = _iocpEvent->m_owner;
			_iocpObject->Dispatch(_iocpEvent, _numOfBytes);
			break;
		}
	}

	return true;
}
