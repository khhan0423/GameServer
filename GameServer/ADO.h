#pragma once
#include "ADOManager.h"
#include "StringUtil.h"
#include "objbase.h"

//https://learn.microsoft.com/ko-kr/sql/ado/guide/referencing-the-ado-libraries-in-a-visual-c-application?view=sql-server-ver16
//ADO 사용하기 위해 import
#pragma warning(disable:4146)
#import "c:\Program Files\Common Files\System\ADO\msADO15.dll" rename_namespace("ADODB") rename("EOF", "adoEOF")

__int32 busy_handler(void* pArg, __int32 nCallCount);

struct sqlite3;
struct sqlite3_stmt;

namespace DataBase
{
	//https://learn.microsoft.com/en-us/windows/win32/api/objbase/nf-objbase-coinitialize
	//com 객체 사용하기 위해서는 반드시 호출
	class DataBaseCoInitialize
	{
	public:
		DataBaseCoInitialize() { CoInitialize(nullptr); }
		virtual ~DataBaseCoInitialize() { ::CoUninitialize(); }
	};

	namespace SQLite3
	{
		class ADO
		{
		protected:
			ADODB::_ConnectionPtr	m_pConnection = nullptr;
			string				m_strConnection;

		public:
			ADODB::_ConnectionPtr GetConnection() { return m_pConnection; }

		public:
			void Close();
			bool Reopen();
			bool Open(const string& strConnection);
			bool Open(const string& strDBHost, const std::string& strDBName, const string& strID, const string& strPassword);
			bool IsOpen() const;
			long GetCommandTimeout() const { return m_pConnection ? m_pConnection->CommandTimeout : 0; }
			void SetCommandTimeout(long lSecond) { if (m_pConnection) m_pConnection->CommandTimeout = lSecond; }

			long GetConnectionTimeout() const { return m_pConnection ? m_pConnection->ConnectionTimeout : 0; }
			void SetConnectionTimeout(long lSecond) { if (m_pConnection) m_pConnection->ConnectionTimeout = lSecond; }

		public:
			long BeginTrans();
			bool CommitTrans();
			bool RollbackTrans();
		};

		class SADOTrans
		{
		private:
			ADO* m_pADO;
			bool	m_bCommit = false;

		public:
			SADOTrans(ADO* pADO) : m_pADO(pADO)
			{
				if (m_pADO) m_pADO->BeginTrans();
			}
			virtual ~SADOTrans()
			{
				if (m_pADO)
				{
					if (m_bCommit)	m_pADO->CommitTrans();
					else			m_pADO->RollbackTrans();
				}
			}
			void SetCommit() { m_bCommit = true; }
		};

		class SADORecordset
		{
		public:
			class SADOField
			{
			protected:
				ADODB::FieldPtr     m_pField = nullptr;

			public:
				SADOField() {}
				SADOField(ADODB::FieldPtr pField) : m_pField(pField) {}
				SADOField(SADOField& objADOField) : m_pField(objADOField.m_pField) {}
				virtual ~SADOField()
				{
					if (m_pField)
					{
						m_pField.Release();
						m_pField = nullptr;
					}
				}

			protected:
				void Close() { if (m_pField) m_pField.Detach(); }

			public:
				ADODB::FieldPtr GetField() { return m_pField; }
				void SetField(ADODB::FieldPtr pField) { m_pField = pField; }
				string GetFieldName() { return string(m_pField->GetName()); }

			public:
				void GetValue(bool& r) { if (m_pField->ActualSize > 0) r = m_pField->GetValue(); }
				void GetValue(char& r) { if (m_pField->ActualSize > 0) r = m_pField->GetValue(); }
				void GetValue(unsigned char& r) { if (m_pField->ActualSize > 0) r = m_pField->GetValue(); }
				void GetValue(short& r) { if (m_pField->ActualSize > 0) r = m_pField->GetValue(); }
				void GetValue(unsigned short& r) { if (m_pField->ActualSize > 0) r = m_pField->GetValue(); }
				void GetValue(int& r) { if (m_pField->ActualSize > 0) r = m_pField->GetValue(); }
				void GetValue(unsigned int& r) { if (m_pField->ActualSize > 0) r = m_pField->GetValue(); }
				void GetValue(long& r) { if (m_pField->ActualSize > 0) r = m_pField->GetValue(); }
				void GetValue(unsigned long& r) { if (m_pField->ActualSize > 0) r = m_pField->GetValue(); }
				void GetValue(long long& r) { if (m_pField->ActualSize > 0) r = m_pField->GetValue(); }
				void GetValue(unsigned long long& r) { if (m_pField->ActualSize > 0) r = m_pField->GetValue(); }
				void GetValue(float& r) { if (m_pField->ActualSize > 0) r = m_pField->GetValue(); }
				void GetValue(double& r) { if (m_pField->ActualSize > 0) r = m_pField->GetValue(); }
				void GetValue(string& r) { if (m_pField->ActualSize > 0) r = (_bstr_t)m_pField->GetValue(); StringUtil::Trim(r); }
				void GetValue(wstring& r) { if (m_pField->ActualSize > 0) r = (_bstr_t)m_pField->GetValue(); StringUtil::Trim(r); }
				void GetValue(SYSTEMTIME& r) { if (m_pField->ActualSize > 0) VariantTimeToSystemTime(m_pField->GetValue(), &r); }

			public:
				template <typename T> void operator=(T Value) { m_pField->Value = _variant_t(Value); }
			};

		protected:
			std::vector<ADODB::_RecordsetPtr>	m_RecordsetList;
			size_t								m_szRecordsetIndex = 0;

		public:
			SADORecordset() {}
			SADORecordset(ADODB::_RecordsetPtr pRecordset);
			virtual ~SADORecordset() { Close(); }

		public:
			void Close();
			void Attach(ADODB::_RecordsetPtr pRecordset);
			bool Open(ADO* pADO, const char* strQuery, ...);
			bool Open(ADO* pADO, const wchar_t* strQuery, ...);
			void NextRecordset() { m_szRecordsetIndex++; }
			bool IsEOF() const;
			bool IsBOF() const;
			bool MoveNext() const;

		public:
			template<typename T> bool GetValue(int iColumnIndex, T& rValue)
			{
				if (m_szRecordsetIndex < 0 || m_szRecordsetIndex >= m_RecordsetList.size()) return false;

				SADOField Val;

				Val.SetField(m_RecordsetList[m_szRecordsetIndex]->GetFields()->Item[_variant_t((long)iColumnIndex)]);
				Val.GetValue(rValue);
				return true;
			}
			template<typename T> bool GetValue(const char* strColumnName, T& rValue)
			{
				if (m_szRecordsetIndex < 0 || m_szRecordsetIndex >= m_RecordsetList.size()) return false;

				SADOField Val;

				Val.SetField(m_RecordsetList[m_szRecordsetIndex]->GetFields()->Item[_variant_t(strColumnName)]);
				Val.GetValue(rValue);
				return true;
			}
		};

		class SADOCommand
		{
		public:
			class SADOParameter
			{
			protected:
				ADODB::_ParameterPtr	m_pParameter = nullptr;

			public:
				SADOParameter() {}
				SADOParameter(ADODB::_ParameterPtr pParameter) : m_pParameter(pParameter) {}
				SADOParameter(SADOParameter& objADOParameter) : m_pParameter(objADOParameter.m_pParameter) {}
				virtual ~SADOParameter()
				{
					if (m_pParameter)
					{
						m_pParameter.Release();
						m_pParameter = nullptr;
					}
				}

			protected:
				void Close() { if (m_pParameter) m_pParameter.Detach(); }

			public:
				ADODB::_ParameterPtr GetParameter() { return m_pParameter; }
				void SetParameter(ADODB::_ParameterPtr pParameter) { m_pParameter = pParameter; }
				string GetFieldName() { return string(m_pParameter->GetName()); }

			public:
				void GetValue(bool& r) { r = m_pParameter->GetValue(); }
				void GetValue(char& r) { r = m_pParameter->GetValue(); }
				void GetValue(unsigned char& r) { r = m_pParameter->GetValue(); }
				void GetValue(short& r) { r = m_pParameter->GetValue(); }
				void GetValue(unsigned short& r) { r = m_pParameter->GetValue(); }
				void GetValue(int& r) { r = m_pParameter->GetValue(); }
				void GetValue(unsigned int& r) { r = m_pParameter->GetValue(); }
				void GetValue(long& r) { r = m_pParameter->GetValue(); }
				void GetValue(unsigned long& r) { r = m_pParameter->GetValue(); }
				void GetValue(long long& r) { r = m_pParameter->GetValue(); }
				void GetValue(unsigned long long& r) { r = m_pParameter->GetValue(); }
				void GetValue(float& r) { r = m_pParameter->GetValue(); }
				void GetValue(double& r) { r = m_pParameter->GetValue(); }
				void GetValue(string& r) { r = (_bstr_t)m_pParameter->GetValue(); StringUtil::Trim(r); }
				void GetValue(wstring& r) { r = (_bstr_t)m_pParameter->GetValue(); StringUtil::Trim(r); }
				void GetValue(SYSTEMTIME& r) { VariantTimeToSystemTime(m_pParameter->GetValue(), &r); }

			public:
				template <typename T> void operator=(T Value) { m_pParameter->Value = _variant_t(Value); }
			};

		protected:
			ADODB::_CommandPtr	m_pCommand = nullptr;
			ADO* m_pOwner = nullptr;

		public:
			virtual ~SADOCommand() { Close(); }

		public:
			void Close();
			bool Create(ADO* pADO, bool HasReturnValue = false, bool NamedParameters = true);
			ADODB::_RecordsetPtr Execute(const char* strCommandText, ADODB::CommandTypeEnum eCommandType = ADODB::adCmdStoredProc);
			long GetCommandTimeout() const { return m_pCommand ? m_pCommand->CommandTimeout : 0; }
			void SetCommandTimeout(long lSecond) { if (m_pCommand) m_pCommand->CommandTimeout = lSecond; }

		public:
			int GetResult()
			{
				int iResult;
				if (!GetParam(0, iResult)) return -1;
				return iResult;
			}
			ADODB::ParameterDirectionEnum GetParamDirection(bool bIn, bool bOut)
			{
				if (bIn && !bOut) return ADODB::adParamInput;
				else if (!bIn && bOut) return ADODB::adParamOutput;
				return ADODB::adParamInputOutput;
			}
			template<typename T> bool GetParam(int iParamIndex, T& rValue)
			{
				if (!m_pCommand) return false;

				SADOParameter Val;

				Val.SetParameter(m_pCommand->GetParameters()->Item[_variant_t((long)iParamIndex)]);
				Val.GetValue(rValue);
				return true;
			}
			template<typename T> bool GetParam(const char* strParamName, T& rValue)
			{
				if (!m_pCommand) return false;

				SADOParameter Val;

				Val.SetParameter(m_pCommand->GetParameters()->Item[_variant_t(strParamName)]);
				Val.GetValue(rValue);
				return true;
			}

		public:
			bool AppendParam(const char* strName, ADODB::DataTypeEnum eDataType,
				ADODB::ParameterDirectionEnum eParameterDirection, long lSize, const _variant_t& rValue);
			bool AppendParam(const char* strName, char cValue, bool bIn = true, bool bOut = false)
			{
				return AppendParam(strName, ADODB::adTinyInt, GetParamDirection(bIn, bOut), static_cast<long>(sizeof(cValue)), cValue);
			}
			bool AppendParam(const char* strName, unsigned char ucValue, bool bIn = true, bool bOut = false)
			{
				return AppendParam(strName, ADODB::adUnsignedTinyInt, GetParamDirection(bIn, bOut), static_cast<long>(sizeof(ucValue)), ucValue);
			}
			bool AppendParam(const char* strName, short sValue, bool bIn = true, bool bOut = false)
			{
				return AppendParam(strName, ADODB::adSmallInt, GetParamDirection(bIn, bOut), static_cast<long>(sizeof(sValue)), sValue);
			}
			bool AppendParam(const char* strName, unsigned short usValue, bool bIn = true, bool bOut = false)
			{
				return AppendParam(strName, ADODB::adUnsignedSmallInt, GetParamDirection(bIn, bOut), static_cast<long>(sizeof(usValue)), usValue);
			}
			bool AppendParam(const char* strName, int iValue, bool bIn = true, bool bOut = false)
			{
				return AppendParam(strName, ADODB::adInteger, GetParamDirection(bIn, bOut), static_cast<long>(sizeof(iValue)), iValue);
			}
			bool AppendParam(const char* strName, unsigned int uiValue, bool bIn = true, bool bOut = false)
			{
				return AppendParam(strName, ADODB::adUnsignedInt, GetParamDirection(bIn, bOut), static_cast<long>(sizeof(uiValue)), uiValue);
			}
			bool AppendParam(const char* strName, long lValue, bool bIn = true, bool bOut = false)
			{
				return AppendParam(strName, ADODB::adInteger, GetParamDirection(bIn, bOut), static_cast<long>(sizeof(lValue)), lValue);
			}
			bool AppendParam(const char* strName, unsigned long ulValue, bool bIn = true, bool bOut = false)
			{
				return AppendParam(strName, ADODB::adUnsignedInt, GetParamDirection(bIn, bOut), static_cast<long>(sizeof(ulValue)), ulValue);
			}
			bool AppendParam(const char* strName, long long i64Value, bool bIn = true, bool bOut = false)
			{
				return AppendParam(strName, ADODB::adBigInt, GetParamDirection(bIn, bOut), static_cast<long>(sizeof(i64Value)), i64Value);
			}
			bool AppendParam(const char* strName, unsigned long long ui64Value, bool bIn = true, bool bOut = false)
			{
				return AppendParam(strName, ADODB::adUnsignedBigInt, GetParamDirection(bIn, bOut), static_cast<long>(sizeof(ui64Value)), ui64Value);
			}
			bool AppendParam(const char* strName, float fValue, bool bIn = true, bool bOut = false)
			{
				return AppendParam(strName, ADODB::adSingle, GetParamDirection(bIn, bOut), static_cast<long>(sizeof(fValue)), fValue);
			}
			bool AppendParam(const char* strName, double dValue, bool bIn = true, bool bOut = false)
			{
				return AppendParam(strName, ADODB::adDouble, GetParamDirection(bIn, bOut), static_cast<long>(sizeof(dValue)), dValue);
			}
			bool AppendParam(const char* strName, const char* strValue, bool bIn = true, bool bOut = false)
			{
				long lSize = (bOut) ? 256 : static_cast<long>(strlen(strValue));
				return AppendParam(strName, ADODB::adVarChar, GetParamDirection(bIn, bOut), lSize, strValue);
			}
			bool AppendParam(const char* strName, const wchar_t* strValue, bool bIn = true, bool bOut = false)
			{
				long lSize = (bOut) ? 256 : static_cast<long>(wcslen(strValue));
				return AppendParam(strName, ADODB::adVarWChar, GetParamDirection(bIn, bOut), lSize, strValue);
			}
			bool AppendParam(const char* strName, const string& strValue, bool bIn = true, bool bOut = false)
			{
				long lSize = (bOut) ? 256 : static_cast<long>(strValue.size());
				return AppendParam(strName, ADODB::adVarChar, GetParamDirection(bIn, bOut), lSize, strValue.c_str());
			}
			bool AppendParam(const char* strName, const wstring& strValue, bool bIn = true, bool bOut = false)
			{
				long lSize = (bOut) ? 256 : static_cast<long>(strValue.size());
				return AppendParam(strName, ADODB::adVarWChar, GetParamDirection(bIn, bOut), lSize, strValue.c_str());
			}
		};
	};
};



