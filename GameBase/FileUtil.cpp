#include "pch.h"
#include <fstream>
#include "FileUtil.h"

vector<BYTE> FileUtils::ReadFile(const wchar_t* path)
{
	vector<BYTE> ret;

	std::basic_ifstream<wchar_t> _stream(path, ios::binary);
	if (_stream)
	{
		_stream.unsetf(ios::skipws);

		_stream.seekg(0, ios::end);
		size_t size = static_cast<size_t>(_stream.tellg());
		_stream.seekg(0);

		_stream.read(reinterpret_cast<wchar_t*>(&ret[0]), size);
	}

	return ret;
}

wstring FileUtils::Convert(string str)
{
	const __int32 _srcLen = static_cast<__int32>(str.size());

	wstring ret;
	if (_srcLen == 0)
		return ret;

	const __int32 _retLen = ::MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<char*>(&str[0]), _srcLen, NULL, 0);
	ret.resize(_retLen);
	::MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<char*>(&str[0]), _srcLen, &ret[0], _retLen);

	return ret;
}