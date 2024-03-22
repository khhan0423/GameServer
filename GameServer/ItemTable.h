#pragma once
#include "TableBase.h"
#include "TableReader.h"

#define GetItemTable() ItemTable::GetInstance()

struct ItemTableRecord
{
	wstring		m_ID;
	wstring		m_Name;
	wstring		m_type;
	__int32		m_atkValue;
	wstring		m_Desc;
};

class ItemTable : public TableBaseSingleton<ItemTable>, TableRecordDatas<wstring, ItemTableRecord>
{
	virtual const char* GetFileName() override
	{
		return "./Tables/ItemTable.xlsx.";
	}
	virtual bool LoadXLSX(const char* XLSXfileName) override
	{
		TableReader _reader;
		if (_reader.Load(XLSXfileName) == false)
		{
			ErrorLog("[%s] %s file load failed!", __FUNCTION__, XLSXfileName);
		}

		for (size_t i = 0; i < static_cast<size_t>(_reader.GetRows().size()); i++)
		{
			ItemTableRecord* _tableRecordPtr = new ItemTableRecord();
			VERIFY_FAILED(_reader.GetValue(i, L"ID", _tableRecordPtr->m_ID, true))
			{
				SAFE_DELETE(_tableRecordPtr);
				return false;
			}
			VERIFY_FAILED(_reader.GetValue(i, L"NAME", _tableRecordPtr->m_Name, false))
			{
				SAFE_DELETE(_tableRecordPtr);
				return false;
			}
			VERIFY_FAILED(_reader.GetValue(i, L"TYPE", _tableRecordPtr->m_type))
			{
				SAFE_DELETE(_tableRecordPtr);
				return false;
			}
			VERIFY_FAILED(_reader.GetValue(i, L"ATK", _tableRecordPtr->m_atkValue))
			{
				SAFE_DELETE(_tableRecordPtr);
				return false;
			}
			VERIFY_FAILED(_reader.GetValue(i, L"DESC", _tableRecordPtr->m_Desc, false))
			{
				SAFE_DELETE(_tableRecordPtr);
				return false;
			}

			Insert(_tableRecordPtr->m_ID, _tableRecordPtr);
		}

		return true;
	}
	virtual bool LoadCompleted()	override
	{
		return true;
	}
};

