#include "pch.h"
#include "Service.h"
#include "Session.h"
#include "GameSession.h"
#include "SocketUtils.h"
#include "GameServerSystem.h"

int main()
{
	GameServer()->Init();

	while (true)
	{
		//�ܼ�ȯ�濡���� ���ѷ��� �ȵ��� main�� return �Ǹ鼭
		//���� Ŭ���� ��ü�� �Ҹ��ڸ� ȣ���ϴ±�...
		//��Main ȯ�濡���� ����¥�ٰ� ó�� �˾���.. ��..
		this_thread::yield();
	}
	return 0;
}