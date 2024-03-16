#include "pch.h"
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "SocketUtils.h"
#include "ServerPacketHandler.h"

class ServerSession : public PacketSession
{
public:
	~ServerSession()
	{
		cout << "ServerSession::~ServerSession()" << endl;
	}

	virtual void OnConnected() override
	{
		cout << "ServerSession::OnConnected()" << endl;
	}

	virtual void OnRecvPacket(unsigned char* buffer, __int32 len) override
	{
		shared_ptr<PacketSession> _session = GetPacketSessionRef();
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

		cout << "ServerSession::OnRecvPacket() Len = " << len << endl;

		ServerPacketHandler::HandlePacket(_session, buffer, len);
	}

	virtual void OnSend(__int32 len) override
	{
		cout << "ServerSession::OnSend() Len = " << len << endl;
	}

	virtual void OnDisconnected() override
	{
		cout << "ServerSession::OnDisconnected()" << endl;
	}
};


int main()
{
	ServerPacketHandler::Init();

	this_thread::sleep_for(1s);

	shared_ptr<ClientService> _service = make_shared<ClientService>(
		NetAddress(L"127.0.0.1", 7777),
		move(make_shared<IocpCore>()),
		move(make_shared<ServerSession>), // TODO : SessionManager µî
		1);

	ASSERT(_service->Start());

	for (__int32 i = 0; i < 2; i++)
	{
		GetThreadManager()->Launch([=]()
			{
				while (true)
				{
					_service->GetIocpCore()->Dispatch();
				}
			});
	}

	GetThreadManager()->Join();
}
