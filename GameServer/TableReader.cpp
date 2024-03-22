#include "pch.h"
#include "TableReader.h"
#include "StringUtil.h"

const size_t TableReader::GetRowCount()  const
{
	if (m_rows.empty() == true)
	{
		return 0;
	}

	return m_rows.size();
}
const vector<wstring> TableReader::GetColNameList()  const
{
	if (m_colunmNames.empty() == true)
	{
		return vector<wstring>();
	}

	return m_colunmNames;
}

bool TableReader::Load(const std::string& filePath)
{
	m_doc.open((filePath));

	if (m_doc.isOpen() == false)
	{
		ErrorLog("[%s] %s file open failed!", __FUNCTION__, filePath);

		return false;
	}

	XLWorksheet _sheet = m_doc.workbook().worksheet("main");

	if (_sheet.rowCount() == 0)
	{
		ErrorLog("[%s] %s file is empty", __FUNCTION__, filePath);
	}

	m_rowCount = _sheet.rowCount();
	m_colCount = _sheet.columnCount();

	for (XLRow& row : _sheet.rows())
	{
		std::vector<XLCellValue> readValues;
		readValues = row.values();

		if (readValues.empty() == true)
			continue;
		
		vector<wstring> _columns;
		for (const auto& cell : row.cells())
		{
			AddCel(cell, _columns);
		}

		if (m_isFirstRow == true)
		{
			m_colunmNames = _columns;
			m_isFirstRow.exchange(false);
		}
		else
		{
			m_rows.push_back(_columns);
		}		
	}	

	__int32 index = 0;
	for (auto&& val : m_colunmNames)
	{
		wstring _str = val;
		transform(_str.begin(), _str.end(), _str.begin(), tolower);
		m_columnIndexs.emplace(make_pair(_str, index++));
	}

	m_doc.close();

	return true;
}

void TableReader::AddCel(const XLCell& cell, OUT vector<wstring>& cells)
{
	switch (cell.value().type())
	{
	case XLValueType::Empty: EmptyToCells(cell.value(), cells);
		return;
	case XLValueType::Boolean: BooleanToCells(cell.value(), cells);
		return;
	case XLValueType::Integer: IntegerToCells(cell.value(), cells);
		return;
	case XLValueType::Float: FloatToCells(cell.value(), cells);
		return;
	case XLValueType::Error: ErrorToCells(cell.value(), cells);
		return;
	case XLValueType::String: StringToCells(cell.value(), cells);
		return;
	default:
		return;
	}
}

// 서드파티 OpenXLSX 에서 Cell 의 값을 string 이 아닌 std::variant 로 들고 있어서
//각 경우마다 추출해서 다시 String 으로 변환해야함.
//나중에 TableReader 도 std::variant 로 업그레이드 해볼 생각.
void TableReader::EmptyToCells(const XLCellValueProxy& value, OUT vector<wstring>& cells)
{
	cells.push_back(L"EMPTY");
}

void TableReader::BooleanToCells(const XLCellValueProxy& value, OUT vector<wstring>& cells)
{
	bool _temp = value.get<bool>();
	if (_temp == true)
		cells.push_back(L"TRUE");
	else
		cells.push_back(L"FALSE");
}

void TableReader::IntegerToCells(const XLCellValueProxy& value, OUT vector<wstring>& cells)
{
	__int64 _temp = value.get<__int64>();
	cells.push_back(StringUtil::IntToWide(value));
}

void TableReader::FloatToCells(const XLCellValueProxy& value, OUT vector<wstring>& cells)
{
	double _temp = value.get<double>();
	cells.push_back(StringUtil::DoubleToWide(value));
}

void TableReader::ErrorToCells(const XLCellValueProxy& value, OUT vector<wstring>& cells)
{
	cells.push_back(L"ERROR");
}

void TableReader::StringToCells(const XLCellValueProxy& value, OUT vector<wstring>& cells)
{
	string _temp = value.get<string>();
	//XLCell 의 기본 string 은 utf-8을 사용한다.
	cells.push_back(StringUtil::Utf8ToWide(_temp));
}

bool TableReader::GetValue(size_t row, const wstring& str, OUT string& strData, bool lower /*= true*/)
{
	wstring _columnName = str;
	transform(_columnName.begin(), _columnName.end(), _columnName.begin(), tolower);
	
	if (m_columnIndexs.find(_columnName) == m_columnIndexs.end())
		return false;

	if (row >= m_rows.size())
		return false;

	strData = StringUtil::ToAnsi(m_rows[row][m_columnIndexs[_columnName]]);
	
	if (lower == true)
		transform(strData.begin(), strData.end(), strData.begin(), tolower);

	return true;
}	

bool TableReader::GetValue(size_t row, const wstring& str, OUT wstring& strData, bool lower /*= true*/)
{
	wstring _columnName = str;
	transform(_columnName.begin(), _columnName.end(), _columnName.begin(), tolower);

	if (m_columnIndexs.find(_columnName) == m_columnIndexs.end())
		return false;

	if (row >= m_rows.size())
		return false;

	strData = m_rows[row][m_columnIndexs[_columnName]];

	if (lower == true)
		std::transform(strData.begin(), strData.end(), strData.begin(), tolower);

	return true;
}

bool TableReader::GetValue(size_t row, const wstring& str, OUT bool& bData, bool bDefault /*= false*/)
{
	bData = bDefault;

	wstring _columnName = str;
	transform(_columnName.begin(), _columnName.end(), _columnName.begin(), tolower);

	if (m_columnIndexs.find(_columnName) == m_columnIndexs.end())
		return false;

	if (row >= m_rows.size())
		return false;

	wstring _tempStr;
	_tempStr = m_rows[row][m_columnIndexs[_columnName]];

	if (_tempStr.compare(L"TRUE") == 0)
	{
		bData = true;
	}
	else if (_tempStr.compare(L"FALSE") == 0)
	{
		bData = false;
	}
	else if (_tempStr.empty())
	{
		bData = bDefault;
	}

	return true;
}
bool TableReader::MergeRow(const TableReader& Reader)
{
	if (m_columnIndexs.empty() == true)
		m_columnIndexs = Reader.GetColumnsIndex();
	if (m_colunmNames.empty() == true)
		m_colunmNames = Reader.GetColumnNames();

	m_rows.insert(m_rows.end(), Reader.GetRows().begin(), Reader.GetRows().end());

	return true;
}

