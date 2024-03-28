#include "pch.h"
#include "SmallWorld.h"
#include "User.h"
#include "GameSession.h"

std::shared_ptr<SmallWorld> GRoom = std::make_shared<SmallWorld>();

void SmallWorld::Enter(std::shared_ptr<User> userShared)
{
	m_UserMap[userShared->m_UserId] = userShared;
	DebugLog("[%s]", __FUNCTION__);
}

void SmallWorld::Leave(std::shared_ptr<User> userShared)
{
	m_UserMap.erase(userShared->m_UserId);
	DebugLog("[%s]", __FUNCTION__);
}

void SmallWorld::Broadcast(std::shared_ptr<SendBuffer> sendBuffer)
{
	for (auto& player : m_UserMap)
	{
		DebugLog("[%s]", __FUNCTION__);
	}
}