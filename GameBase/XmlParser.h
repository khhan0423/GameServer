#pragma once
#include "rapidxml.hpp"
using namespace rapidxml;

using XmlNodeType = xml_node<wchar_t>;
using XmlDocumentType = xml_document<wchar_t>;
using XmlAttributeType = xml_attribute<wchar_t>;

class XmlNode
{
public:
	XmlNode(XmlNodeType* node = nullptr) : _node(node) { }

	bool				IsValid() { return _node != nullptr; }

	bool				GetBoolAttr(const wchar_t* key, bool defaultValue = false);
	__int8				GetInt8Attr(const wchar_t* key, __int8 defaultValue = 0);
	__int16				GetInt16Attr(const wchar_t* key, __int16 defaultValue = 0);
	__int32				GetInt32Attr(const wchar_t* key, __int32 defaultValue = 0);
	__int64				GetInt64Attr(const wchar_t* key, __int64 defaultValue = 0);
	float				GetFloatAttr(const wchar_t* key, float defaultValue = 0.0f);
	double				GetDoubleAttr(const wchar_t* key, double defaultValue = 0.0);
	const wchar_t*		GetStringAttr(const wchar_t* key, const wchar_t* defaultValue = L"");

	bool				GetBoolValue(bool defaultValue = false);
	__int8				GetInt8Value(__int8 defaultValue = 0);
	__int16				GetInt16Value(__int16 defaultValue = 0);
	__int32				GetInt32Value(__int32 defaultValue = 0);
	__int64				GetInt64Value(__int64 defaultValue = 0);
	float				GetFloatValue(float defaultValue = 0.0f);
	double				GetDoubleValue(double defaultValue = 0.0);
	const wchar_t*		GetStringValue(const wchar_t* defaultValue = L"");

	XmlNode				FindChild(const wchar_t* key);
	vector<XmlNode>		FindChildren(const wchar_t* key);

private:
	XmlNodeType*		_node = nullptr;
};

/*---------------
	XmlParser
----------------*/

class XmlParser
{
public:
	bool ParseFromFile(const wchar_t* path, OUT XmlNode& root);

private:
	shared_ptr<XmlDocumentType>		m_document = nullptr;
	wstring							m_data;
};