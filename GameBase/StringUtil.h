#pragma once
#include <atlbase.h>
#include <atlconv.h>
#include <string>

class StringUtil
{
	template<typename CharType>
	class StringConvBuffer
	{
	public:
		StringConvBuffer(size_t AllocSize) : m_convBuffer(nullptr), m_convBufferLength(AllocSize)
		{
			m_convBuffer = new CharType[m_convBufferLength];
			memset(m_convBuffer, 0x00, sizeof(CharType) * m_convBufferLength);
		};
		virtual ~StringConvBuffer() { SAFE_DELETE_ARRAY(m_convBuffer); m_convBufferLength = 0; }
	public:
		CharType* GetBuffer() { return m_convBuffer; }
		size_t GetBufferLen() { return m_convBufferLength; }

	private:
		CharType*	m_convBuffer;
		size_t		m_convBufferLength;
	};
public:
	static wstring ToWide(const char* str)
	{
		USES_CONVERSION;
		return A2CW(str);
	}
	static std::wstring ToWide(const string& str)
	{
		USES_CONVERSION;
		return A2CW(str.c_str());
	}
	static string ToAnsi(const wchar_t* str)
	{
		USES_CONVERSION;
		return W2CA(str);
	}
	static string ToAnsi(const wstring& str)
	{
		USES_CONVERSION;
		return W2CA(str.c_str());
	}
	static string WideToUtf8(const wstring& str)
	{
		StringConvBuffer<char> _ConvertBuffer(WideCharToMultiByte(CP_UTF8, 0, str.c_str(), static_cast<__int32>(str.length()), nullptr, 0, nullptr, nullptr));
		WideCharToMultiByte(CP_UTF8, 0, str.c_str(), static_cast<__int32>(str.length()), _ConvertBuffer.GetBuffer(), static_cast<__int32>(_ConvertBuffer.GetBufferLen()), nullptr, nullptr);

		return string(_ConvertBuffer.GetBuffer(), _ConvertBuffer.GetBufferLen());
	}
	static string WideToSLOG(const wstring& str)
	{
		return WideToUtf8(str);
	}
	static wstring Utf8ToWide(const std::string& str)
	{
		StringConvBuffer<wchar_t> _ConvertBuffer(MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<__int32>(str.length()), nullptr, 0));
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<__int32>(str.length()), _ConvertBuffer.GetBuffer(), static_cast<__int32>(_ConvertBuffer.GetBufferLen()));

		return wstring(_ConvertBuffer.GetBuffer(), _ConvertBuffer.GetBufferLen());
	}
	static string AnsiToUtf8(const string& str)
	{
		return WideToUtf8(ToWide(str));
	}
	static string AnsiToSLOG(const string& str)
	{
		return AnsiToUtf8(str);
	}
	static string Utf8ToAnsi(const string& str)
	{
		return ToAnsi(Utf8ToWide(str));
	}

	static bool ToLower(string& str)
	{
		transform(str.begin(), str.end(), str.begin(), tolower);
		return true;
	}
	static bool ToLower(wstring& str)
	{
		transform(str.begin(), str.end(), str.begin(), tolower);
		return true;
	}
	static bool ToUpper(string& str)
	{
		transform(str.begin(), str.end(), str.begin(), toupper);
		return true;
	}
	static bool ToUpper(wstring& str)
	{
		transform(str.begin(), str.end(), str.begin(), toupper);
		return true;
	}
	static bool IsNumber(const char* str)
	{
		if (!str) return false;
		size_t _len = strlen(str);
		if (!_len) return false;

		for (size_t i = 0; i < _len; ++i)
			if (str[i] != '.' && str[i] != '-' && !::isdigit(static_cast<unsigned char>(str[i]))) return false;
		return true;
	}
	static bool IsNumber(const wchar_t* wstr)
	{
		if (!wstr) return false;

		size_t _len = wcslen(wstr);
		if (!_len) return false;

		for (size_t i = 0; i < _len; ++i)
			if (wstr[i] != '.' && !::iswdigit(wstr[i])) return false;
		return true;
	}
	static void Trim(string& str)
	{
		size_t _npos = str.find_last_not_of(" \t\v\n") + 1;

		if (_npos != string::npos)
			str.replace(_npos, str.length() - _npos, "");
	}
	static void Trim(wstring& str)
	{
		size_t _npos = str.find_last_not_of(L" \t\v\n") + 1;
		if (_npos != wstring::npos)
			str.replace(_npos, str.length() - _npos, L"");
	}
};


