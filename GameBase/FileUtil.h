#pragma once

class FileUtils
{
public:
	static vector<BYTE>		ReadFile(const wchar_t* path);
	static wstring			Convert(string str);
};


