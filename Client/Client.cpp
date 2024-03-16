#include "pch.h"
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "SocketUtils.h"


char sendData[] = "Hello World";

class ServerSession : public Session
{
public:
	~ServerSession()
	{
		cout << "~ServerSession" << endl;
	}

	virtual void OnConnected() override
	{
		cout << "Connected To Server" << endl;

		shared_ptr<SendBuffer> sendBuffer = make_shared<SendBuffer>(4096);
		sendBuffer->CopyData(sendData, sizeof(sendData));
		Send(sendBuffer);
	}

	virtual __int32 OnRecv(BYTE* buffer, __int32 len) override
	{
		cout << "OnRecv Len = " << len << endl;

		this_thread::sleep_for(1s);

		shared_ptr<SendBuffer> sendBuffer = make_shared<SendBuffer>(4096);
		sendBuffer->CopyData(sendData, sizeof(sendData));
		Send(sendBuffer);

		return len;
	}

	virtual void OnSend(__int32 len) override
	{
		cout << "OnSend Len = " << len << endl;
	}

	virtual void OnDisconnected() override
	{
		cout << "Disconnected" << endl;
	}
};


int main()
{
	SocketUtils::Init();
	this_thread::sleep_for(1s);

	shared_ptr<ClientService> service = make_shared<ClientService>(
		NetAddress(L"127.0.0.1", 7777),
		move(make_shared<IocpCore>()),
		move(make_shared<ServerSession>), // TODO : SessionManager µî
		1);

	ASSERT(service->Start());

	for (__int32 i = 0; i < 2; i++)
	{
		GetThreadManager()->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}

	GetThreadManager()->Join();
}
