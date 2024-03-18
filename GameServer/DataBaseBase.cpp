#include "pch.h"
#include "DataBaseBase.h"

using namespace DataBase;

__int32 DB_Module_Interface::BinaryToText(const unsigned char* pbin, const unsigned long long bin_len, unsigned char* ptext, const unsigned long long text_len)
{
	const unsigned char* _vp;
	unsigned char* _rp;
	unsigned __int64 _len;
	unsigned __int64 _bslash_len = 1;

	_len = 1;
	_vp = pbin;

	for (unsigned __int64 i = bin_len; i > 0; i--, _vp++)
	{
		if (*_vp < 0x20 || *_vp > 0x7e)
			_len += _bslash_len + 3;
		else if (*_vp == '\'')
			_len += 2;
		else if (*_vp == '\\')
			_len += _bslash_len + _bslash_len;
		else
			_len++;
	}

	if (text_len < _len)
		return 0;

	_rp = ptext;
	_vp = pbin;

	for (size_t i = bin_len; i > 0; i--, _vp++)
	{
		if (*_vp < 0x20 || *_vp > 0x7e)
		{
			__int32 val = *_vp;

			*_rp++ = '\\';
			*_rp++ = static_cast<unsigned char>((val >> 6) + '0');
			*_rp++ = static_cast<unsigned char>(((val >> 3) & 07) + '0');
			*_rp++ = static_cast<unsigned char>((val & 07) + '0');
		}
		else if (*_vp == '\'')
		{
			*_rp++ = '\'';
			*_rp++ = '\'';
		}
		else if (*_vp == '\\')
		{
			*_rp++ = '\\';
			*_rp++ = '\\';
		}
		else
			*_rp++ = *_vp;
	}

	*_rp = '\0';

	return static_cast<__int32>(strlen((const char*)ptext));
}

__int32 DB_Module_Interface::TextToBinary(const unsigned char* ptext, const unsigned long long text_len, unsigned char* pbin, const unsigned long long bin_len)
{
	if (ptext == nullptr)
		return 0;

	unsigned char* _buffer = nullptr;
	unsigned __int64 _buflen = 0;

	_buffer = new unsigned char[text_len + 1];
	if (!_buffer)
		return 0;

	unsigned __int64 i = 0, j = 0;
	for (i = j = 0; i < text_len;)
	{
		switch (ptext[i])
		{
		case '\\':
			i++;
			if (ptext[i] == '\\')
				_buffer[j++] = ptext[i++];
			else
			{
				if ((ISFIRSTOCTDIGIT(ptext[i])) &&
					(ISOCTDIGIT(ptext[i + 1])) &&
					(ISOCTDIGIT(ptext[i + 2])))
				{
					__int32 _byte;

					_byte = OCTVAL(ptext[i++]);
					_byte = (_byte << 3) + OCTVAL(ptext[i++]);
					_byte = (_byte << 3) + OCTVAL(ptext[i++]);
					_buffer[j++] = static_cast<unsigned char>(_byte);
				}
			}
			break;

		default:
			_buffer[j++] = ptext[i++];
			break;
		}
	}
	_buflen = j;

	if (bin_len < _buflen)
	{
		memcpy(pbin, _buffer, bin_len);

		_buflen = 0;
	}
	else
		memcpy(pbin, _buffer, _buflen);

	SAFE_DELETE_ARRAY(_buffer);
	_buffer = nullptr;

	return static_cast<__int32>(_buflen);
}
