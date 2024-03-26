#include "pch.h"
#include "LogBase.h"
#include "GlobalGameBase.h"
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "SocketUtils.h"
#include "ServerPacketHandler.h"
#include "Protocol/ProtocolClientToServer.pb.h"

//OnConnected() -> ������ �÷��� ��
//ȭ����ȯ �α��� ȭ��
//�α��� ���p ������ ȭ�� ��ȯ
//�α��� ���Դϴ�.
//��� ������, ����� ���� ȭ�� ��ȯ �б�
// ĳ���� ����ȭ��
// �������� ȭ��


class ServerSession : public PacketSession
{
public:
	~ServerSession()
	{
		DebugLog("[%s]", __FUNCTION__);
	}

	virtual void OnConnected() override
	{
		DebugLog("[%s]", __FUNCTION__);
		//ProtocolServerToClient::ResultLogin -> server
		ProtocolClientToServer::RequestLogin _ReqLogin;
		_ReqLogin.set_m_accountid("khhan0423");
		auto _sendBuffer = ServerPacketHandler::MakeSendBuffer(_ReqLogin);
		Send(_sendBuffer);
	}

	virtual void OnRecvPacket(unsigned char* buffer, __int32 len) override
	{
		std::shared_ptr<PacketSession> _session = GetPacketSessionRef();
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

		DebugLog("[%s] len : ", __FUNCTION__, len);

		ServerPacketHandler::HandlePacket(_session, buffer, len);
	}

	virtual void OnSend(__int32 len) override
	{
		DebugLog("[%s] len : ", __FUNCTION__, len);
	}

	virtual void OnDisconnected() override
	{
		DebugLog("[%s]", __FUNCTION__);
	}
};

enum
{
	WORKER_TICK = 64
};

void DoWorkerJob(std::shared_ptr<ClientService>& service)
{
	while (true)
	{
		TLS_EndTickCount = ::GetTickCount64() + WORKER_TICK;

		service->GetIocpCore()->Dispatch(10);

		GThreadManager->Run();
	}
}


int main()
{
	ServerPacketHandler::Init();
	GetGlobalLog()->Init(GAMELOG_LEVEL_DEBUG, GAMELOG_OUTPUT_BOTH, "Client");

	std::this_thread::sleep_for(std::chrono::seconds(1));

	std::shared_ptr<ClientService> _service = std::make_shared<ClientService>(
		NetAddress(L"127.0.0.1", 7777),
		move(std::make_shared<IocpCore>()),
		move(std::make_shared<ServerSession>),
		1);

	VERIFY(_service->Start());

	for (__int32 i = 0; i < 1; i++)
	{
		GThreadManager->Launch([&_service]()
			{
				while (true)
				{
					DoWorkerJob(_service);
				}
			});
	}

	DoWorkerJob(_service);

	GThreadManager->Join();
}
