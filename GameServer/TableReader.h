#pragma once

#include "TableBase.h"
#include <OpenXLSX.hpp>
#include <boost/nowide/iostream.hpp>
#include <boost/nowide/convert.hpp>

//Reader
//vector<CellData> : a row;
//vector<vector<CellData>> : rows;
//map<string, int> : cellName, index of in a row;
//GetValue(rowcnt, cellName, &type)
//GetValue(rowcnt, cellName, &type2)
//GetValue(rowcnt, cellName, &type3)

//테이블 Reader 클래스를 만들자.
//CELL 들의 데이터를 모두 string 으로 읽어서
//자료구조에 저장해 두고, 쓰는 쪽에서
//GetValue응 호출 할 때, 캐스팅해서 쓰는 방식

using namespace OpenXLSX;
class TableReader
{
public:
	using					Colunm = wstring;
	using					Row = vector<Colunm>;
	using					Rows = vector<Row>;
	using					ColumnIndex = std::unordered_map<std::wstring, int>;

private:	
	Rows					m_rows;
	ColumnIndex				m_columnIndexs;
	Row						m_colunmNames;

private:
	unsigned __int32		m_rowCount = 0;
	unsigned __int16		m_colCount = 0;

private:
	atomic<bool>			m_isFirstRow = true;
public:
	const size_t			GetRowCount()  const;
	const vector<wstring>	GetColNameList()  const;

	bool					Load(const std::string& filePath);

	void					AddCel(const XLCell& cell, OUT vector<wstring>& cells);
	void					EmptyToCells(const XLCellValueProxy& value, OUT vector<wstring>& cells);
	void					BooleanToCells(const XLCellValueProxy& value, OUT vector<wstring>& cells);
	void					IntegerToCells(const XLCellValueProxy& value, OUT vector<wstring>& cells);
	void					FloatToCells(const XLCellValueProxy& value, OUT vector<wstring>& cells);
	void					ErrorToCells(const XLCellValueProxy& value, OUT vector<wstring>& cells);
	void					StringToCells(const XLCellValueProxy& value, OUT vector<wstring>& cells);


	bool					GetValue(size_t row, const wstring& column, OUT string& strData, bool lower = true);
	bool					GetValue(size_t row, const wstring& column, OUT wstring& strData, bool lower = true);
	bool					GetValue(size_t row, const wstring& column, OUT bool& bData, bool bDefault = false);

							//나머지 number 타입들은 템플릿 처리
							template<typename T>
	bool					GetValue(size_t row, const std::wstring& column, OUT T& data, T defaultVal = 0)
							{
								data = defaultVal;

								string _temp;
								if ((GetValue(row, column, _temp) || !_temp.empty()) == false)
									return false;

								data = static_cast<T>(atof(_temp.c_str()));

								return true;
							}
public:
							//같은종류의 테이블이
							//주제에 따라서 조각 조각 따로 관리될 수 있기에
							//인게임에서는 그 테이블들을 1개로 관리해야 하는 이슈가 있다.
	bool					MergeRow(const TableReader& Reader);
	const					Rows& GetRows() const { return m_rows; }
	const					ColumnIndex& GetColumnsIndex()  const { return m_columnIndexs; }
	const					Row& GetColumnNames()  const { return m_colunmNames; }

protected:
	XLDocument				m_doc;
};
