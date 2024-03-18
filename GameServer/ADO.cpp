#include "pch.h"
#include <sqlite3.h>
#include "DataBaseBase.h"
#include "ADO.h"


using namespace DataBase;
using namespace DataBase::MSSQL;

DataBaseCoInitialize gCoInit;

void ADO::Close()
{
	if (!m_pConnection) return;

	if (ADODB::adStateClosed != m_pConnection->GetState()) m_pConnection->Close();
	m_pConnection.Release();
	m_pConnection = nullptr;
}

bool ADO::Reopen()
{
	return Open(m_strConnection);
}

bool ADO::Open(const std::string& strConnection)
{
	Close();

	m_strConnection = strConnection;

	try
	{
		if (m_pConnection.CreateInstance("ADODB.Connection") != S_OK) return false;
		if (m_pConnection->Open(m_strConnection.c_str(), "", "", ADODB::adConnectUnspecified) != S_OK) return false;
		if (ADODB::adStateClosed == m_pConnection->GetState()) return false;
		m_pConnection->CursorLocation = ADODB::adUseClient;
	}
	catch (std::exception& ex)
	{
		ErrorLog("ADO Catch %s", ex.what());
		return false;
	}

	return true;
}

bool ADO::Open(const std::string& strDBHost, const std::string& strDBName, const std::string& strID, const std::string& strPassword)
{
	Close();

	try
	{
		char strConnection[512];
		sprintf_s(strConnection, sizeof(strConnection),
			"Provider=SQLOLEDB.1;Data Source=%s;Initial Catalog=%s;User ID=%s;Password=%s", strDBHost.c_str(), strDBName.c_str(), strID.c_str(), strPassword.c_str());
		m_strConnection = strConnection;

		if (m_pConnection.CreateInstance("ADODB.Connection") != S_OK)
		{
			ErrorLog("ADO CreateInstance failed");
			return false;
		}
		if (m_pConnection->Open(m_strConnection.c_str(), "", "", ADODB::adConnectUnspecified) != S_OK)
		{
			ErrorLog("ADO Open failed");
			return false;
		}
		if (ADODB::adStateClosed == m_pConnection->GetState())
		{
			ErrorLog("ADO State failed");
			return false;
		}
		m_pConnection->CursorLocation = ADODB::adUseClient;
	}
	catch (std::exception& ex)
	{
		ErrorLog("ADO Catch %s", ex.what());
		return false;
	}

	return true;
}

bool ADO::IsOpen() const
{
	return m_pConnection && ADODB::adStateClosed != m_pConnection->GetState();
}

long ADO::BeginTrans()
{
	if (!m_pConnection) return -1;

	return m_pConnection->BeginTrans();
}

bool ADO::CommitTrans()
{
	if (!m_pConnection) return false;

	return m_pConnection->CommitTrans() == S_OK;
}

bool ADO::RollbackTrans()
{
	if (!m_pConnection) return false;

	return m_pConnection->RollbackTrans() == S_OK;
}

SADORecordset::SADORecordset(ADODB::_RecordsetPtr pRecordset)
{
	Attach(pRecordset);
}

void SADORecordset::Close()
{
	for (auto&& it : m_RecordsetList)
	{
		if (ADODB::adStateClosed != it->GetState()) it->Close();
		it.Release();
	}
	m_RecordsetList.clear();
}

void SADORecordset::Attach(ADODB::_RecordsetPtr pRecordset)
{
	Close();

	for (ADODB::_RecordsetPtr i = pRecordset; i; i = pRecordset->NextRecordset(nullptr)) m_RecordsetList.push_back(i);
}

bool SADORecordset::Open(ADO* pADO, const char* strQuery, ...)
{
	Close();

	char strTemp[4096];
	va_list arg_ptr;
	va_start(arg_ptr, strQuery);
	vsprintf_s(strTemp, sizeof(strTemp), strQuery, arg_ptr);
	va_end(arg_ptr);

	ADODB::_RecordsetPtr pRecordset;
	if (pRecordset.CreateInstance("ADODB.Recordset") != S_OK) return false;
	if (pRecordset->Open(_variant_t(strTemp), _variant_t((IDispatch*)pADO->GetConnection()),
		ADODB::adOpenUnspecified, ADODB::adLockUnspecified, ADODB::adCmdUnspecified) != S_OK) return false;
	Attach(pRecordset);
	return true;
}

bool SADORecordset::Open(ADO* pADO, const wchar_t* strQuery, ...)
{
	Close();

	wchar_t strTemp[4096];
	va_list arg_ptr;
	va_start(arg_ptr, strQuery);
	vswprintf_s(strTemp, _countof(strTemp), strQuery, arg_ptr);
	va_end(arg_ptr);

	ADODB::_RecordsetPtr pRecordset;
	if (pRecordset.CreateInstance("ADODB.Recordset") != S_OK) return false;
	if (pRecordset->Open(_variant_t(strTemp), _variant_t((IDispatch*)pADO->GetConnection()),
		ADODB::adOpenUnspecified, ADODB::adLockUnspecified, ADODB::adCmdUnspecified) != S_OK) return false;

	Attach(pRecordset);
	return true;
}

bool SADORecordset::IsEOF() const
{
	if (IsBOF())
		return true;

	if (m_szRecordsetIndex < 0 || m_szRecordsetIndex >= m_RecordsetList.size()) return true;

	return m_RecordsetList[m_szRecordsetIndex]->adoEOF == VARIANT_TRUE;
}

bool SADORecordset::IsBOF() const
{
	if (m_szRecordsetIndex < 0 || m_szRecordsetIndex >= m_RecordsetList.size()) return true;

	return m_RecordsetList[m_szRecordsetIndex]->BOF == VARIANT_TRUE;
}

bool SADORecordset::MoveNext() const
{
	if (m_szRecordsetIndex < 0 || m_szRecordsetIndex >= m_RecordsetList.size()) return false;

	return m_RecordsetList[m_szRecordsetIndex]->MoveNext() == S_OK;
}

void ADOCommand::Close()
{
	if (!m_pCommand)
		return;

	if (ADODB::adStateExecuting == m_pCommand->GetState()) m_pCommand->Cancel();

	m_pCommand.Release();
	m_pCommand = nullptr;
}

bool ADOCommand::Create(ADO* pADO, bool HasReturnValue, bool NamedParameters)
{
	if (pADO == nullptr)
		return false;

	Close();

	pADO->Reopen();
	m_pOwner = pADO;

	if (m_pCommand.CreateInstance("ADODB.Command") != S_OK)
		return false;

	m_pCommand->ActiveConnection = pADO->GetConnection();
	if (NamedParameters)
		m_pCommand->NamedParameters = VARIANT_TRUE;

	if (!HasReturnValue)
		return true;

	return AppendParam("", ADODB::adInteger, ADODB::adParamReturnValue, sizeof(int), vtMissing);
}

ADODB::_RecordsetPtr ADOCommand::Execute(const char* strCommandText, ADODB::CommandTypeEnum eCommandType)
{
	if (!m_pCommand) return nullptr;

	m_pCommand->CommandType = eCommandType;
	m_pCommand->CommandText = strCommandText;

	ADODB::_RecordsetPtr pRecordSet = m_pCommand->Execute(nullptr, nullptr, 0);
	return pRecordSet;
}

bool ADOCommand::AppendParam(const char* strName, ADODB::DataTypeEnum eDataType, ADODB::ParameterDirectionEnum eParameterDirection, long lSize, const _variant_t& rValue)
{
	if (!m_pCommand) return false;

	if (lSize <= 0) lSize = 1;
	return m_pCommand->GetParameters()->Append(m_pCommand->CreateParameter(strName, eDataType, eParameterDirection, lSize, rValue)) == S_OK;
}