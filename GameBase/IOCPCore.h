#pragma once

//CompletionPort로 관리받을 객체의 인터페이스
//Dispatch 는 상속받은 곳에처 처리
class IocpObject : public std::enable_shared_from_this<IocpObject>
{
public:
	virtual HANDLE GetHandle() abstract;
	virtual void Dispatch(class IocpEvent* iocpEvent, __int32 numOfBytes = 0) abstract;
};

//CompletionPort를 생성하고, IocpObject를 상속받은 객체들이
//Register로 IocpObject를 넘겨주면, IocpCore 의 CompletionPort 에서 객체들을 관리.
class IocpCore
{
public:
	IocpCore();
	~IocpCore();

	HANDLE		GetHandle() { return m_iocpHandle; }

	bool		Register(std::shared_ptr<IocpObject> iocpObjectShared);
	bool		Dispatch(unsigned __int32 timeout = INFINITE);

private:
	HANDLE		m_iocpHandle;
};
