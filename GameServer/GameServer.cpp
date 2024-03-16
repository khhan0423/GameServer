#include "pch.h"
#include "Service.h"
#include "Session.h"
#include "GameSession.h"

int main()
{
	shared_ptr<ServerService> service = make_shared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		move(make_shared<IocpCore>())/*rValue move �� �����ؼ� �ѱ�*/,
		move(make_shared<GameSession>)/*rValue move �� �����ؼ� �ѱ�*/,
		100);

	return 0;
}