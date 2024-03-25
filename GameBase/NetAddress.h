#pragma once

class NetAddress
{
public:
	NetAddress() = default;
	NetAddress(SOCKADDR_IN sockAddr);
	NetAddress(wstring ip, unsigned __int16 port);

	SOCKADDR_IN&			GetSockAddr() { return m_sockAddr; }
	wstring					GetIpAddress();
	unsigned __int16		GetPort() { return ::ntohs(m_sockAddr.sin_port); }

public:
	static IN_ADDR			IpToAddress(const wchar_t* ip);

private:
	SOCKADDR_IN				m_sockAddr = {};
};



