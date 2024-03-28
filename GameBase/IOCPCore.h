#pragma once

//CompletionPort�� �������� ��ü�� �������̽�
//Dispatch �� ��ӹ��� ����ó ó��
class IocpObject : public std::enable_shared_from_this<IocpObject>
{
public:
	virtual HANDLE GetHandle() abstract;
	virtual void Dispatch(class IocpEvent* iocpEvent, __int32 numOfBytes = 0) abstract;
};

//CompletionPort�� �����ϰ�, IocpObject�� ��ӹ��� ��ü����
//Register�� IocpObject�� �Ѱ��ָ�, IocpCore �� CompletionPort ���� ��ü���� ����.
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
