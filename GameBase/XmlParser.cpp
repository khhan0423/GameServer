#include "pch.h"
#include <algorithm>
#include "FileUtil.h"
#include "XmlParser.h"

/*-------------
	XmlNode
--------------*/

_locale_t kr = _create_locale(LC_NUMERIC, "kor");

bool XmlNode::GetBoolAttr(const WCHAR* key, bool defaultValue)
{
	XmlAttributeType* attr = _node->first_attribute(key);
	if (attr)
		return ::_wcsicmp(attr->value(), L"true") == 0;

	return defaultValue;
}

__int8 XmlNode::GetInt8Attr(const WCHAR* key, __int8 defaultValue)
{
	XmlAttributeType* attr = _node->first_attribute(key);
	if (attr)
		return static_cast<__int8>(::_wtoi(attr->value()));

	return defaultValue;
}

__int16 XmlNode::GetInt16Attr(const WCHAR* key, __int16 defaultValue)
{
	XmlAttributeType* attr = _node->first_attribute(key);
	if (attr)
		return static_cast<__int16>(::_wtoi(attr->value()));

	return defaultValue;
}

__int32 XmlNode::GetInt32Attr(const WCHAR* key, __int32 defaultValue)
{
	XmlAttributeType* attr = _node->first_attribute(key);
	if (attr)
		return static_cast<__int32>(::_wtoi(attr->value()));

	return defaultValue;
}

__int64 XmlNode::GetInt64Attr(const WCHAR* key, __int64 defaultValue)
{
	xml_attribute<WCHAR>* attr = _node->first_attribute(key);
	if (attr)
		return ::_wtoi64(attr->value());

	return defaultValue;
}

float XmlNode::GetFloatAttr(const WCHAR* key, float defaultValue)
{
	XmlAttributeType* attr = _node->first_attribute(key);
	if (attr)
		return static_cast<float>(::_wtof(attr->value()));

	return defaultValue;
}

double XmlNode::GetDoubleAttr(const WCHAR* key, double defaultValue)
{
	XmlAttributeType* attr = _node->first_attribute(key);
	if (attr)
		return ::_wtof_l(attr->value(), kr);

	return defaultValue;
}

const WCHAR* XmlNode::GetStringAttr(const WCHAR* key, const WCHAR* defaultValue)
{
	XmlAttributeType* attr = _node->first_attribute(key);
	if (attr)
		return attr->value();

	return defaultValue;
}

bool XmlNode::GetBoolValue(bool defaultValue)
{
	WCHAR* val = _node->value();
	if (val)
		return ::_wcsicmp(val, L"true") == 0;

	return defaultValue;
}

__int8 XmlNode::GetInt8Value(__int8 defaultValue)
{
	WCHAR* val = _node->value();
	if (val)
		return static_cast<__int8>(::_wtoi(val));

	return defaultValue;
}

__int16 XmlNode::GetInt16Value(__int16 defaultValue)
{
	WCHAR* val = _node->value();
	if (val)
		return static_cast<__int16>(::_wtoi(val));
	return defaultValue;
}

__int32 XmlNode::GetInt32Value(__int32 defaultValue)
{
	WCHAR* val = _node->value();
	if (val)
		return static_cast<__int32>(::_wtoi(val));

	return defaultValue;
}

__int64 XmlNode::GetInt64Value(__int64 defaultValue)
{
	WCHAR* val = _node->value();
	if (val)
		return static_cast<__int64>(::_wtoi64(val));

	return defaultValue;
}

float XmlNode::GetFloatValue(float defaultValue)
{
	WCHAR* val = _node->value();
	if (val)
		return static_cast<float>(::_wtof(val));

	return defaultValue;
}

double XmlNode::GetDoubleValue(double defaultValue)
{
	WCHAR* val = _node->value();
	if (val)
		return ::_wtof_l(val, kr);

	return defaultValue;
}

const WCHAR* XmlNode::GetStringValue(const WCHAR* defaultValue)
{
	WCHAR* val = _node->first_node()->value();
	if (val)
		return val;

	return defaultValue;
}

XmlNode XmlNode::FindChild(const WCHAR* key)
{
	return XmlNode(_node->first_node(key));
}

vector<XmlNode> XmlNode::FindChildren(const WCHAR* key)
{
	vector<XmlNode> nodes;

	xml_node<WCHAR>* node = _node->first_node(key);
	while (node)
	{
		nodes.push_back(XmlNode(node));
		node = node->next_sibling(key);
	}

	return nodes;
}

bool XmlParser::ParseFromFile(const wchar_t* fileName, OUT XmlNode& root)
{
	vector<BYTE> bytes = FileUtils::ReadFile(fileName);
	m_data = FileUtils::Convert(string(bytes.begin(), bytes.end()));
	
	if (m_data.empty())
		return false;
	m_document = make_shared<XmlDocumentType>();
	m_document->parse<0>(reinterpret_cast<WCHAR*>(&m_data[0]));
	root = XmlNode(m_document->first_node());

	return true;
}