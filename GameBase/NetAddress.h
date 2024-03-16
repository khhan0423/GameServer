#pragma once

class NetAddress
{
public:
	NetAddress() = default;
	NetAddress(SOCKADDR_IN sockAddr);
	NetAddress(wstring ip, unsigned __int16 port);

	SOCKADDR_IN&			GetSockAddr() { return _sockAddr; }
	wstring					GetIpAddress();
	unsigned __int16		GetPort() { return ::ntohs(_sockAddr.sin_port); }

public:
	static IN_ADDR			Ip2Address(const WCHAR* ip);

private:
	SOCKADDR_IN		_sockAddr = {};
};



