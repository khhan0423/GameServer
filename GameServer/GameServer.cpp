#include "pch.h"
#include "Service.h"
#include "Session.h"
#include "GameSession.h"
#include "SocketUtils.h"
#include "ThreadManager.h"

int main()
{
	SocketUtils::Init();

	shared_ptr<ServerService> m_service = make_shared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		move(make_shared<IocpCore>())/*rValue move 로 포장해서 넘김*/,
		move(make_shared<GameSession>)/*rValue move 로 포장해서 넘김*/,
		3);

	ASSERT(m_service->Start());

	for (__int32 i = 0; i < 5; i++)
	{
		GetThreadManager()->Launch([=]()
			{
				while (true)
				{
					m_service->GetIocpCore()->Dispatch();
				}
			});
	}

	GetThreadManager()->Join();

	return 0;
}