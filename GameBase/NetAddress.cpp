#include "pch.h"
#include "NetAddress.h"

NetAddress::NetAddress(SOCKADDR_IN sockAddr) : m_sockAddr(sockAddr)
{
}

NetAddress::NetAddress(wstring ip, unsigned __int16 port)
{
	::memset(&m_sockAddr, 0, sizeof(m_sockAddr));
	m_sockAddr.sin_family = AF_INET;
	m_sockAddr.sin_addr = IpToAddress(ip.c_str());
	m_sockAddr.sin_port = ::htons(port);
}

wstring NetAddress::GetIpAddress()
{
	WCHAR m_buffer[100];
	//wide char : not 1 byte -> buf len is (sizeof(buffer) / sizeof(buffer[0]) 
	::InetNtopW(AF_INET, &m_sockAddr.sin_addr, m_buffer, (sizeof(m_buffer) / sizeof(m_buffer[0])));
	return wstring(m_buffer);
}

IN_ADDR NetAddress::IpToAddress(const WCHAR* ip)
{
	IN_ADDR _address;
	::InetPtonW(AF_INET, ip, &_address);
	return _address;
}
