#pragma once
#include <atlbase.h>
#include <atlconv.h>
#include <string>
#include <algorithm>

class StringUtil
{
	template<typename CharType>
	class StringConvBuffer
	{
	public:
		StringConvBuffer(size_t AllocSize) : m_ConvBuffer(nullptr), m_ConvBufferLength(AllocSize)
		{
			m_ConvBuffer = new CharType[m_ConvBufferLength];
			memset(m_ConvBuffer, 0x00, sizeof(CharType) * m_ConvBufferLength);
		};
		virtual ~StringConvBuffer() { if (m_ConvBuffer) delete[] m_ConvBuffer; m_ConvBufferLength = 0; }
	public:
		CharType* GetBuffer() { return m_ConvBuffer; }
		size_t GetBufferLen() { return m_ConvBufferLength; }

	private:
		CharType*	m_ConvBuffer;
		size_t		m_ConvBufferLength;
	};
public:
	////////////////////////////////////////////////////////////////////////
	// 언젠가는 대체해야 하는 부분 스택영역 사용이라 루프안에서 위험성 있음.
	////////////////////////////////////////////////////////////////////////
	static std::wstring ToWide(const char* str)
	{
		USES_CONVERSION;
		return A2CW(str);
	}
	static std::wstring ToWide(const std::string& str)
	{
		USES_CONVERSION;
		return A2CW(str.c_str());
	}
	static std::string ToAnsi(const wchar_t* str)
	{
		USES_CONVERSION;
		return W2CA(str);
	}
	static std::string ToAnsi(const std::wstring& str)
	{
		USES_CONVERSION;
		return W2CA(str.c_str());
	}
	////////////////////////////////////////////////////////////////////////
	static std::string WideToUtf8(const std::wstring& str)
	{
		StringConvBuffer<char> _ConvertBuffer(WideCharToMultiByte(CP_UTF8, 0, str.c_str(), static_cast<int>(str.length()), nullptr, 0, nullptr, nullptr));
		WideCharToMultiByte(CP_UTF8, 0, str.c_str(), static_cast<int>(str.length()), _ConvertBuffer.GetBuffer(), static_cast<int>(_ConvertBuffer.GetBufferLen()), nullptr, nullptr);

		return std::string(_ConvertBuffer.GetBuffer(), _ConvertBuffer.GetBufferLen());
	}
	static std::wstring Utf8ToWide(const std::string& str)
	{
		StringConvBuffer<wchar_t> _ConvertBuffer(MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.length()), nullptr, 0));
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.length()), _ConvertBuffer.GetBuffer(), static_cast<int>(_ConvertBuffer.GetBufferLen()));

		return std::wstring(_ConvertBuffer.GetBuffer(), _ConvertBuffer.GetBufferLen());
	}
	static std::string AnsiToUtf8(const std::string& str)
	{
		return WideToUtf8(ToWide(str));
	}
	static std::string Utf8ToAnsi(const std::string& str)
	{
		return ToAnsi(Utf8ToWide(str));
	}
	static std::string DoubleToAnsi(double value)
	{
		return to_string(value);
	}
	static std::wstring DoubleToWide(double value)
	{
		return to_wstring(value);
	}
	static std::string DoubleToUtf8(double value)
	{
		return WideToUtf8(to_wstring(value));
	}
	static std::string IntToAnsi(long long value)
	{
		return to_string(value);
	}
	static std::wstring IntToWide(long long value)
	{
		return to_wstring(value);
	}
	static std::string IntToUtf8(long long value)
	{
		return WideToUtf8(to_wstring(value));
	}
	static std::string FloatToAnsi(float value)
	{
		return to_string(value);
	}
	static std::wstring FloatToWide(float value)
	{
		return to_wstring(value);
	}
	static std::string FloatToUtf8(float value)
	{
		return WideToUtf8(to_wstring(value));
	}
	static std::string UIntToAnsi(unsigned long long value)
	{
		return to_string(value);
	}
	static std::wstring UIntToWide(unsigned long long value)
	{
		return to_wstring(value);
	}
	static std::string UIntToUtf8(unsigned long long value)
	{
		return WideToUtf8(to_wstring(value));
	}
	static bool ToLower(std::string& str)
	{
		std::transform(str.begin(), str.end(), str.begin(), tolower);
		return true;
	}
	static bool ToLower(std::wstring& str)
	{
		std::transform(str.begin(), str.end(), str.begin(), tolower);
		return true;
	}
	static bool ToUpper(std::string& str)
	{
		std::transform(str.begin(), str.end(), str.begin(), toupper);
		return true;
	}
	static bool ToUpper(std::wstring& str)
	{
		std::transform(str.begin(), str.end(), str.begin(), toupper);
		return true;
	}
	static bool IsNumber(const char* str)
	{
		if (!str) return false;
		size_t len = strlen(str);
		if (!len) return false;

		for (size_t i = 0; i < len; ++i)
			if (str[i] != '.' && str[i] != '-' && !::isdigit(static_cast<unsigned char>(str[i]))) return false;
		return true;
	}
	static bool IsNumber(const wchar_t* wstr)
	{
		if (!wstr) return false;

		size_t len = wcslen(wstr);
		if (!len) return false;

		for (size_t i = 0; i < len; ++i)
			if (wstr[i] != '.' && !::iswdigit(wstr[i])) return false;
		return true;
	}
	static void Trim(std::string& str)
	{
		size_t npos = str.find_last_not_of(" \t\v\n") + 1;

		if (npos != std::string::npos)
			str.replace(npos, str.length() - npos, "");
	}
	static void Trim(std::wstring& str)
	{
		size_t npos = str.find_last_not_of(L" \t\v\n") + 1;
		if (npos != std::wstring::npos)
			str.replace(npos, str.length() - npos, L"");
	}
};
