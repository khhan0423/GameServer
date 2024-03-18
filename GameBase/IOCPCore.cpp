#include "pch.h"
#include "IOCPCore.h"
#include "IOCPEvent.h"

IocpCore::IocpCore()
{
	//CreateIoCompletionPort 처음으로 생성함.
	m_iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	VERIFY(m_iocpHandle != INVALID_HANDLE_VALUE);
}

IocpCore::~IocpCore()
{
	::CloseHandle(m_iocpHandle);
}

bool IocpCore::Register(shared_ptr<IocpObject> iocpObject)
{
	//생성된, CreateIoCompletionPort에 IocpCore 인터페이스를 상속받은
	//CompletionPort에 의해 관리받을 객체들을 등록함.
	//_iocpHandle로 _iocpObject->GetHandle()도 관리하겠다는 의미.
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
