#pragma once

class FileUtils
{
public:
	static std::vector<BYTE>		ReadFile(const wchar_t* path);
	static std::wstring			Convert(std::string str);
};


