#pragma once
#include "Session.h"

class GameSession : public Session
{
public:
	~GameSession()
	{
		cout << "~GameSession" << endl;
	}

	virtual void		OnConnected() override;
	virtual void		OnDisconnected() override;
	virtual __int32		OnRecv(BYTE* buffer, __int32 len) override;
	virtual void		OnSend(__int32 len) override;
};

